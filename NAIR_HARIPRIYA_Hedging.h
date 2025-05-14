#ifndef _HEDGING_H
#define _HEDGING_H

#include <vector>
#include "NAIR_HARIPRIYA_Underlying.h"
#include "NAIR_HARIPRIYA_Option.h"

class Hedging {

    private:
     static const double r;
     static const double delta_t;

    public:
     std::vector<double> PNL_WITH_H;
     std::vector<double> Cash;
     Hedging();
     void calculate_hedging_error(Underlying S, Option C);
     void calculate_hedging_error(Underlying S, Option C, std::vector<double> r, double d_t);
     void PNL_with_hedge(std::vector<double> r);
     double operator()(int i) const;

};

#endif