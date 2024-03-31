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

vector<double> riemann_left_side(const RCP<const Basic> &f, vector<double> xvec, double initial_condition)
{
    RCP<const Basic> x = symbol("x");
    vector<double> F;
    double riemann_sum = initial_condition, f_left;
    
    double h = xvec[1] - xvec[0];

    F.push_back(riemann_sum);

    for (size_t i = 1; i < xvec.size(); i++)
    {
        f_left = eval_double(*f->subs({{x, real_double(xvec[i-1])}}));
        riemann_sum += f_left * h;
        F.push_back(riemann_sum);
    }

    return F;
}

vector<double> riemann_right_side(const RCP<const Basic> &f, vector<double> xvec, double initial_condition)
{
    RCP<const Basic> x = symbol("x");
    vector<double> F;
    double riemann_sum = initial_condition, f_right;
    
    double h = xvec[1] - xvec[0];

    F.push_back(riemann_sum);

    for (size_t i = 1; i < xvec.size(); i++)
    {
        f_right = eval_double(*f->subs({{x, real_double(xvec[i])}}));
        riemann_sum += f_right * h;
        F.push_back(riemann_sum);
    }

    return F;
}

vector<double> riemann_midpoint(const RCP<const Basic> &f, vector<double> xvec, double initial_condition)
{
    RCP<const Basic> x = symbol("x");
    vector<double> F;
    double riemann_sum = initial_condition, f_mid;
    
    double h = xvec[1] - xvec[0];

    F.push_back(riemann_sum);

    for (size_t i = 1; i < xvec.size(); i++)
    {
        f_mid = eval_double(*f->subs({{x, real_double((xvec[i] + xvec[i-1])/2)}}));
        riemann_sum += f_mid * h;
        F.push_back(riemann_sum);
    }

    return F;
}

vector<double> riemann_trapezoidal(const RCP<const Basic> &f, vector<double> xvec, double initial_condition)
{
    RCP<const Basic> x = symbol("x");
    vector<double> F;
    double riemann_sum = initial_condition, f_left, f_right;
    
    double h = xvec[1] - xvec[0];

    F.push_back(riemann_sum);

    for (size_t i = 1; i < xvec.size(); i++)
    {
        f_left = eval_double(*f->subs({{x, real_double(xvec[i-1])}}));
        f_right = eval_double(*f->subs({{x, real_double(xvec[i])}}));
        riemann_sum += (f_left + f_right) / 2 * h;
        F.push_back(riemann_sum);
    }

    return F;
}

vector<double> simpsons_quadratic(const RCP<const Basic> &f, vector<double> xvec, double initial_condition)
{
    RCP<const Basic> x = symbol("x");
    vector<double> F;
    double riemann_sum = initial_condition, f_left, f_middle, f_right;
    
    double h = xvec[1] - xvec[0];

    F.push_back(riemann_sum);

    for (size_t i = 1; i < xvec.size(); i++)
    {
        f_left = eval_double(*f->subs({{x, real_double(xvec[i-1])}}));
        f_middle = eval_double(*f->subs({{x, real_double(xvec[i]-h/2)}}));
        f_right = eval_double(*f->subs({{x, real_double(xvec[i])}}));
        riemann_sum += h / 6 * (f_left + 4 * f_middle + f_right);
        F.push_back(riemann_sum);
    }

    return F;
}

#endif