#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "NAIR_HARIPRIYA_Underlying.h"
#include "NAIR_HARIPRIYA_Option.h"
#include "NAIR_HARIPRIYA_Hedging.h"
#include <boost/date_time.hpp>

using namespace std;
using namespace boost::gregorian;

double dateDifference(string start_date, string end_date )
{
    //Taken from canvas
    date _start_date(from_simple_string(start_date));
    date _end_date(from_simple_string(end_date));
 
    // counter for weekdays
    double cnt=0;
    for(day_iterator iter = _start_date; iter!=_end_date; ++iter)
    {
        // increment counter if it's no saturday and no sunday
        if(    iter->day_of_week() !=  boost::date_time::Saturday
            && iter->day_of_week() !=  boost::date_time::Sunday)
            ++cnt;
    }
    return cnt;
}

void part1(){
    //Part 1 Reporting Hedging Errors - Prints on terminal
    Underlying P;
    Option C(P);
    Hedging H;
    H.calculate_hedging_error(P,C);
    cout << "Reporting Hedging Errors: "<< endl;
    for(int i=1; i< 100; i++){
        cout << "Stock: "<< P(i) << " Option: "<< C(i) << " Hedging Error: " << H(i) << endl;
    }
} 

void part2(string startdate, string enddate, string expirydate, double K){
    string d, value, exdate, cp_flag, strike_price, best_bid, best_offer;
    vector<string> date;
    vector<double> S, r, C, time_to_maturity;

    //read in data corresponding to test case parameters

    //Stock prices
    ifstream stockprice("./sec_GOOG.csv");
    while(getline(stockprice,d,',')){
        getline(stockprice,value,'\n');
        if(d >= startdate && d <= enddate){
            S.push_back(atof(value.c_str()));
            date.push_back(d);
        }
    }
    //Interest rates
    ifstream interest("./interest.csv");
    while(getline(interest,d,',')){
        getline(interest,value,'\n');
        if(d >= startdate && d <= enddate){
            r.push_back(atof(value.c_str())/100);
        }
    }
    //Option prices
    ifstream option("./op_GOOG.csv");
    while(getline(option,d,',')){
        getline(option,exdate,',');
        getline(option,cp_flag,',');
        getline(option,strike_price,',');
        getline(option,best_bid,',');
        getline(option,best_offer,'\n');
        if(d >= startdate && d <= enddate && exdate == expirydate && atof(strike_price.c_str()) == K && cp_flag == "C"){
            double avg = (atof(best_bid.c_str()) + atof(best_offer.c_str()))/2;
            C.push_back(avg);
            double maturity = dateDifference(d, expirydate)/252;
            time_to_maturity.push_back(maturity);
        }
    }

    //part 2a - Calculate total wealth if a call is sold without hedging
    Underlying Stock(S);
    double NoOfTradingDays = S.size();
    Option Market_Options(C);
    Market_Options.calculate_Wealth(NoOfTradingDays,r);
    cout << "Part 2a: Total Wealth if we sell a call without putting on any hedge " << endl;
    cout << "Sno. "<< "Date " << "Option Price " << "Total Wealth (No Hedge)" << endl; 
    for(int i=0; i< NoOfTradingDays; i++)
       cout << i << " " << date[i] << " " << Market_Options(i) << " " << Market_Options.wealth[i] << endl;
    
    //part 2b - output a file “result.csv” containing stock price, option price, implied volatility, delta, 
    //          hedging error, PNL, PNL with hedge.

    cout << "Part 2b: Result.csv"<< endl;
    Market_Options.calculate_delta(Stock, NoOfTradingDays, K, r, time_to_maturity);
    
    Hedging H;
    H.calculate_hedging_error(Stock,Market_Options, r, 1/252);
    H.PNL_with_hedge(r);
    
    ofstream myfile;
    myfile.open("result.csv");
    myfile << "Date, Stock Price, Option Price, Implied Volatility, Delta, Hedging Error, PNL, PNL (with hedge)\n";

    for (int i=0; i < NoOfTradingDays; i++){
        myfile << date[i] << "," << Stock(i) << "," << Market_Options(i) << "," <<
        Market_Options.implied_volatility[i] << "," << Market_Options.delta[i] << "," << H(i) << "," << Market_Options.PNL[i] << "," <<
        H.PNL_WITH_H[i] << "\n";
    }
    myfile.close();
    cout << "Result.csv generated. Project Completed" <<endl;
    
}

int main()
{
    cout << "Mid Term Project - Submitted by Haripriya Nair" << endl;

    //Part 1
    part1();

    //Part 2
    part2("2011-03-24","2011-08-31","2012-01-21",500);
    //test_case("2011-07-01","2011-07-08","2013-01-19",240);
    

    return 0;
}
