#ifndef FIRST_ORDER_ODE_H
#define FIRST_ORDER_ODE_H

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

vector<double> eulers_method(const RCP<const Basic> &f, vector<double> tvec, double initial_condition)
{
    RCP<const Basic> u = symbol("u");
    RCP<const Basic> t = symbol("t");
    vector<double> ut;
    double f_prev;
    
    double h = tvec[1] - tvec[0];

    ut.push_back(initial_condition);

    for (size_t i = 1; i < tvec.size(); i++)
    {
        f_prev = eval_double(
            *f->subs(
                    {{u, real_double(ut[i-1])}}
                )->subs(
                    {{t, real_double(tvec[i-1])}}
                )
            );
        ut.push_back(ut[i-1] + h * f_prev);
    }

    return ut;
}

#endif