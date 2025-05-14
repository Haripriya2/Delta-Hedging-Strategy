#include "NAIR_HARIPRIYA_Option.h"
#include "NAIR_HARIPRIYA_Underlying.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <boost/math/distributions.hpp>

const double Option::K = 105; 
const double Option::T=0.4;
const double Option::sigma=0.24; 
const double Option::r=0.025;
const double Option::delta_t=0.004;

std::vector<double> C;

Option::Option(Underlying S){
    for(int i=0; i<100; i++){
        C.push_back(calculate_option_price(S(i),i)); 
    }
}

Option::Option(std::vector<double> F){
    C.insert(C.begin(), F.begin(), F.end());
}

double Option::operator()(int i) const {
    return C[i];
}

double Option::calculate_d1(double s, double K, double r, double sig, double tau){
    double d1 = (log(s/K) + (r+0.5*pow(sig,2))*tau)/(sig*sqrt(tau));
    return d1;
}

double Option::calculate_option_price(double s, int i){
    boost::math::normal_distribution <> nd(0.0,1.0);
    double tau = T-i*delta_t;
    double d1 = calculate_d1(s,K,r,sigma,tau);
    Option::delta.push_back(cdf(nd,d1));
    double d2 = d1 - sigma*sqrt(tau);
    double call = s*cdf(nd, d1) - K*exp(-r*tau)*cdf(nd, d2);
    return call;
}

double Option::calculate_option_price(double s, int i, double sig, double N, double tau){
    boost::math::normal_distribution <> nd(0.0,1.0);
    double d1 = calculate_d1(s,K,r,sig,tau);
    Option::delta.push_back(cdf(nd,d1));
    double d2 = d1 - sig*sqrt(tau);
    double call = s*cdf(nd, d1) - K*exp(-r*tau)*cdf(nd, d2);
    return call;
}

void Option::calculate_Wealth(int n, std::vector<double> rate){
    double temp = 500 + C[0];
    wealth.push_back(temp);
    for(int i=1; i<n; i++){
        calculate_PNL(i);
        temp = wealth[0]*exp(rate[i]*i*1/252) + PNL[i];
        wealth.push_back(temp);
    }
}

void Option::calculate_PNL(int n){
        Option::PNL.push_back(C[0] - C[n]);
}

// Calculating Implied Volatility using Newton-Raphson method

double Option::calculate_vega(double s, double r, double sig, double tau, double K){
    boost::math::normal_distribution <> nd(0.0,1.0);
    
    double d1 = calculate_d1(s,K,r,sig,tau);
    double vega = s*sqrt(tau)*cdf(nd,d1);
    return vega;
}

double Option::calculate_implied_volatility(double guess, double C_m, double s, double N, double r, int i, double tau, double K){
    double x = guess, precision = 0.01, call_value, vega;
    double prev;
    do{
        call_value = calculate_option_price(s,i,x,N,tau);
        vega = calculate_vega(s,r,x,tau,K);
        x = x + (C_m - call_value)/vega;
           
    }while(abs(C_m-call_value) <= precision || abs(x) >= 1);
    return abs(x);
}

void Option::calculate_delta(Underlying S, double n, double K, std::vector<double> rate, std::vector<double> t_maturity){
    double volatility, d1, tau;
    boost::math::normal_distribution <> nd(0.0,1.0);
    for(int i=0; i<n; i++){
        tau = t_maturity[i];
        volatility = calculate_implied_volatility(sigma, C[i], S(i), n, rate[i], i, tau, K);
        Option::implied_volatility.push_back(volatility);
        d1 = calculate_d1(S(i),K,rate[i],volatility,tau);;
        Option::delta.push_back(cdf(nd,d1));
    }
}





