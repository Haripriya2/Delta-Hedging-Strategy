#ifndef _UNDERLYING_H
#define _UNDERLYING_H

#include <vector>

class Underlying {

    private:
     static const double u;
     static const double sigma;
     static const double delta_t;

    public:
     Underlying();
     Underlying(std::vector<double> P);
     double operator()(int i) const;

};

#endif