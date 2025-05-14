#ifndef _OPTION_H
#define _OPTION_H

#include <vector>
#include "NAIR_HARIPRIYA_Underlying.h"

class Option{

    private:
    static const double K;
    static const double T;
    static const double sigma;
    static const double r;
    static const double delta_t;
    double calculate_vega(double s, double r, double sig, double tau, double K);
    double calculate_implied_volatility(double guess, double C_m, double s, double N, double r, int i, double tau, double K);
    double calculate_option_price(double s, int i);
    double calculate_option_price(double S, int i, double sig, double N, double d_t);
    double calculate_d1(double s, double K, double r, double sig, double tau);
    
    public:
    std::vector<double> PNL;
    std::vector<double> delta;
    std::vector<double> wealth;
    std::vector<double> implied_volatility;
    Option(Underlying S);
    Option(std::vector<double> F);
    double operator()(int i) const;
    void calculate_PNL(int n);
    void calculate_Wealth(int n, std::vector<double> rate);
    void calculate_delta(Underlying S, double n, double K, std::vector<double> rate, std::vector<double> tau);
    
};
#endif