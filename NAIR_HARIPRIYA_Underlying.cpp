#include "NAIR_HARIPRIYA_Underlying.h"
#include <math.h>
#include <vector>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include <iostream>
using namespace std;

const double Underlying::u = 0.05;
const double Underlying::sigma = 0.24;
const double Underlying::delta_t = 0.004;

std::vector<double> S;

Underlying::Underlying(){
    S.push_back(100.00);
    boost::mt19937 rng;
    boost::normal_distribution<> nd(0.0, 1.0);
    boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > var_nor(rng, nd);
    double z = 0.0;
    double temp = 0.0;
    for(int i=0; i<100; i++){
        z = var_nor();
        temp = S[i] + u*S[i]*delta_t + sigma*S[i]*sqrt(delta_t)*z;
        S.push_back(temp);
    }
}

Underlying::Underlying(std::vector<double> P){
    S.insert(S.begin(), P.begin(), P.end());
}

double Underlying::operator()(int i) const {
    return S[i];
}