#include "NAIR_HARIPRIYA_Hedging.h"
#include "NAIR_HARIPRIYA_Underlying.h"
#include "NAIR_HARIPRIYA_Option.h"
#include <math.h>
#include <vector>
#include <iostream>

const double Hedging::r=0.025;
const double Hedging::delta_t=0.004;

std::vector<double> HE;

Hedging::Hedging(){
}

double Hedging::operator()(int i) const{
    return HE[i];
}

void Hedging::calculate_hedging_error(Underlying S, Option C){
    std::vector<double> B;
    double temp = C(0)-C.delta[0]*S(0);
    B.push_back(temp);
    for(int i=1; i< 100; i++){
        temp = C.delta[i-1]*S(i) + B[i-1]*exp(r*delta_t) - C.delta[i]*S(i);
        B.push_back(temp);
        temp = C.delta[i-1]*S(i) + B[i-1]*exp(r*delta_t) - C(i);
        HE.push_back(temp);
    }
}

void Hedging::calculate_hedging_error(Underlying S, Option C, std::vector<double> r, double d_t){
    std::vector<double> B;
    double temp = C(0)-C.delta[0]*S(0);
    B.push_back(temp);
    for(int i=1; i< 100; i++){
        temp = C.delta[i-1]*S(i) + B[i-1]*exp(r[i]*d_t) - C.delta[i]*S(i);
        B.push_back(temp);
        temp = C.delta[i-1]*S(i) + B[i-1]*exp(r[i]*d_t) - C(i);
        HE.push_back(temp);

    }
}

void Hedging::PNL_with_hedge(std::vector<double> r){
    double sum = 0.0, delta = 1/252;
    for(int i =0; i< r.size(); i++){
        sum = sum*exp(r[i]*delta) + HE[i];
        Hedging::PNL_WITH_H.push_back(sum);
    }
}

