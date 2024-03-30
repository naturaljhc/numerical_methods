#ifndef INTEGRATION_H
#define INTEGRATION_H

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

vector<double> riemann_left_hand(const RCP<const Basic> &f, vector<double> xvec, double initial_condition)
{
    RCP<const Basic> x = symbol("x");
    vector<double> dfdx;
    double riemann_sum = initial_condition, f_left;
    
    double h = xvec[1] - xvec[0];

    for (size_t i = 0; i < xvec.size() - 1; i++)
    {
        f_left = eval_double(*f->subs({{x, real_double(xvec[i])}}));
        riemann_sum += f_left * h;
        dfdx.push_back(riemann_sum);
    }

    return dfdx;
}

vector<double> riemann_right_hand(const RCP<const Basic> &f, vector<double> xvec, double initial_condition)
{
    RCP<const Basic> x = symbol("x");
    vector<double> dfdx;
    double riemann_sum = initial_condition, f_left;
    
    double h = xvec[1] - xvec[0];

    for (size_t i = 1; i < xvec.size(); i++)
    {
        f_left = eval_double(*f->subs({{x, real_double(xvec[i])}}));
        riemann_sum += f_left * h;
        dfdx.push_back(riemann_sum);
    }

    return dfdx;
}

#endif