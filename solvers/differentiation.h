#ifndef DIFFERENTIATION_H
#define DIFFERENTIATION_H

#include <iostream>
#include <iomanip>
#include <symengine/real_double.h>
#include <symengine/eval_double.h>
#include <symengine/expression.h>
#include <symengine/symbol.h>
#include "linalg_functions.h"
#include <fstream>
#include <vector>
#include "json.hpp"

using namespace std;
using namespace SymEngine;
using json = nlohmann::json;

vector<double> differentiate(const RCP<const Basic> &f, vector<double> xvec)
{
    RCP<const Basic> x = symbol("x");
    vector<double> dfdx;
    double f_curr, f_next;
    
    double h = xvec[1] - xvec[0];

    for (size_t i = 0; i < xvec.size() - 1; i++)
    {
        f_curr = eval_double(*f->subs({{x, real_double(xvec[i])}}));
        f_next = eval_double(*f->subs({{x, real_double(xvec[i+1])}}));
        dfdx.push_back((f_next - f_curr)/h);
    }

    return dfdx;
}

#endif