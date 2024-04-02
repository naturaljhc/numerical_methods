#ifndef ROOT_FINDING_H
#define ROOT_FINDING_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <random>
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

double newtons_method(const RCP<const Basic> &f, const RCP<const Basic> &dfdx, double x0, int iter = 1000, double tol = 1e-10)
{
    RCP<const Symbol> x = symbol("x");
    double root = 0;

    for (int i = 0; i < iter; i++) {
        root = x0 - (eval_double(*f->subs({{x, real_double(x0)}}))) /
                    (eval_double(*dfdx->subs({{x, real_double(x0)}})));
        
        if (abs(root - x0) <= tol)
        {
            return root;
        }

        x0 = root;
    }

    return root;
}

double finite_differences_newtons_method(const RCP<const Basic> &f, double h, double x0, int iter = 1000, double tol = 1e-10)
{
    // If the derivative of f is either unknown or hard to calculate,
    // this function will use finite differences to determine an approximation
    // of the derivative at x

    RCP<const Symbol> x = symbol("x");
    double root = 0, dfdx;

    for (int i = 0; i < iter; i++) {
        dfdx = (eval_double(*f->subs({{x, real_double(x0+h)}})) - eval_double(*f->subs({{x, real_double(x0)}}))) / h;

        root = x0 - (eval_double(*f->subs({{x, real_double(x0)}}))) /
                    (dfdx);
        
        if (abs(root - x0) <= tol)
        {
            return root;
        }

        x0 = root;
    }

    return root;

}

#endif