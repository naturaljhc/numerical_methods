#ifndef FIRST_ORDER_ODE_H
#define FIRST_ORDER_ODE_H

#include <iostream>
#include <iomanip>
#include <symengine/real_double.h>
#include <symengine/eval_double.h>
#include <symengine/expression.h>
#include <symengine/symbol.h>
#include <symengine/derivative.h>
#include "linalg_functions.h"
#include <fstream>
#include <vector>
#include "json.hpp"
#include "root_finding.h"

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

    for (size_t i = 0; i < tvec.size() - 1; i++)
    {
        f_prev = eval_double(
            *f->subs(
                    {{u, real_double(ut[i])}, {t, real_double(tvec[i])}}
                )
            );
        ut.push_back(ut[i] + h * f_prev);
    }

    return ut;
}

vector<double> backward_eulers_method(const RCP<const Basic> &f, vector<double> tvec, double initial_condition)
{
    RCP<const Symbol> u = symbol("u");
    RCP<const Symbol> t = symbol("t");
    RCP<const Symbol> x = symbol("x");
    RCP<const Basic> root_funct, dfdx;
    vector<double> ut;
    double h;

    h = tvec[1] - tvec[0];

    ut.push_back(initial_condition);

    for (size_t i = 0; i < tvec.size() - 1; i++)
    {   
        root_funct = sub(
            sub(
                x, 
                real_double(ut[i])
            ), 
            mul(
                real_double(h), 
                f->subs({{u, x}, {t, real_double(tvec[i+1])}})
            )
        );

        dfdx = diff(root_funct, x);
        ut.push_back(newtons_method(root_funct, dfdx, ut[i]));
    }

    return ut;
}

vector<double> two_step_midpoint_method(const RCP<const Basic> &f, vector<double> tvec, double initial_condition)
{
    RCP<const Basic> u = symbol("u");
    RCP<const Basic> t = symbol("t");
    vector<double> ut;
    double h, unext;

    h = tvec[1] - tvec[0];

    ut.push_back(initial_condition);

    // Initialize the midpoint method:
    // Euler's method to find u_1
    unext = ut[0] + h * eval_double(
            *f->subs(
                    {{u, real_double(ut[0])}, {t, real_double(tvec[0])}}
                )
            );
    ut.push_back(unext);

    for (size_t i = 1; i < tvec.size() - 1; i++)
    {
        unext = ut[i-1] + h * eval_double(
            *f->subs(
                    {{u, real_double(ut[i])}, {t, real_double(tvec[i])}}
                )
            );
        ut.push_back(unext);
    }

    return ut;
}

vector<double> trapezoidal_method(const RCP<const Basic> &f, vector<double> tvec, double initial_condition)
{
    RCP<const Symbol> u = symbol("u");
    RCP<const Symbol> t = symbol("t");
    RCP<const Symbol> x = symbol("x");
    RCP<const Basic> root_funct, dfdx;
    vector<double> ut;
    double h;

    h = tvec[1] - tvec[0];

    ut.push_back(initial_condition);

    for (size_t i = 0; i < tvec.size() - 1; i++)
    {   
        root_funct = sub(
            sub(
                x, 
                real_double(ut[i])
            ), 
            mul(
                real_double(h/2), 
                add(
                    f->subs({{u, real_double(ut[i])}, {t, real_double(tvec[i])}}),
                    f->subs({{u, x}, {t, real_double(tvec[i+1])}})
                )
            )
        );
        dfdx = diff(root_funct, x);

        ut.push_back(newtons_method(root_funct, dfdx, ut[i]));
    }

    return ut;
}

vector<double> rk2(const RCP<const Basic> &f, vector<double> tvec, double initial_condition)
{
    RCP<const Basic> u = symbol("u");
    RCP<const Basic> t = symbol("t");
    vector<double> ut;
    double h, umid, unext;

    h = tvec[1] - tvec[0];

    ut.push_back(initial_condition);

    for (size_t i = 0; i < tvec.size() - 1; i++)
    {
        umid = ut[i] + h / 2 * eval_double(
            *f->subs(
                {{u, real_double(ut[i])}, {t, real_double(tvec[i])}}
            )
        );
        unext = ut[i] + h * eval_double(
            *f->subs(
                {{u, real_double(umid)}, {t, real_double(tvec[i] + h/2)}}
            )
        );
        ut.push_back(unext);
    }

    return ut;
}
#endif