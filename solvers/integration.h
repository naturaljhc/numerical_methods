#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <iostream>
#include <iomanip>
#include <symengine/real_double.h>
#include <symengine/eval_double.h>
#include <symengine/expression.h>
#include <symengine/symbol.h>
#include "linalg_functions.h"
#include "error_estimation.h"
#include <fstream>
#include <vector>
#include "json.hpp"

using namespace std;
using namespace SymEngine;
using json = nlohmann::json;

double riemann_left_side(const RCP<const Basic> &f, vector<double> xvec)
{
    RCP<const Basic> x = symbol("x");
    double riemann_sum = 0, f_left;
    
    double h = xvec[1] - xvec[0];

    for (size_t i = 1; i < xvec.size(); i++)
    {
        f_left = eval_double(*f->subs({{x, real_double(xvec[i-1])}}));
        riemann_sum += f_left * h;
    }

    return riemann_sum;
}

double riemann_right_side(const RCP<const Basic> &f, vector<double> xvec)
{
    RCP<const Basic> x = symbol("x");
    double riemann_sum = 0, f_right;
    
    double h = xvec[1] - xvec[0];

    for (size_t i = 1; i < xvec.size(); i++)
    {
        f_right = eval_double(*f->subs({{x, real_double(xvec[i])}}));
        riemann_sum += f_right * h;
    }

    return riemann_sum;
}

double riemann_midpoint(const RCP<const Basic> &f, vector<double> xvec)
{
    RCP<const Basic> x = symbol("x");
    double riemann_sum = 0, f_mid;
    
    double h = xvec[1] - xvec[0];

    for (size_t i = 1; i < xvec.size(); i++)
    {
        f_mid = eval_double(*f->subs({{x, real_double((xvec[i] + xvec[i-1])/2)}}));
        riemann_sum += f_mid * h;
    }

    return riemann_sum;
}

double riemann_trapezoidal(const RCP<const Basic> &f, vector<double> xvec)
{
    RCP<const Basic> x = symbol("x");
    double riemann_sum = 0, f_left, f_right;
    
    double h = xvec[1] - xvec[0];

    for (size_t i = 1; i < xvec.size(); i++)
    {
        f_left = eval_double(*f->subs({{x, real_double(xvec[i-1])}}));
        f_right = eval_double(*f->subs({{x, real_double(xvec[i])}}));
        riemann_sum += (f_left + f_right) / 2 * h;
    }

    return riemann_sum;
}

double simpsons_quadratic(const RCP<const Basic> &f, vector<double> xvec)
{
    RCP<const Basic> x = symbol("x");
    double riemann_sum = 0, f_left, f_middle, f_right;
    
    double h = xvec[1] - xvec[0];

    for (size_t i = 1; i < xvec.size(); i++)
    {
        f_left = eval_double(*f->subs({{x, real_double(xvec[i-1])}}));
        f_middle = eval_double(*f->subs({{x, real_double(xvec[i]-h/2)}}));
        f_right = eval_double(*f->subs({{x, real_double(xvec[i])}}));
        riemann_sum += h / 6 * (f_left + 4 * f_middle + f_right);
    }

    return riemann_sum;
}

#endif