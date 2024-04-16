#ifndef ORDER_ESTIMATION_H
#define ORDER_ESTIMATION_H

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
#include <cmath>

using namespace std;
using namespace SymEngine;

// Approximates the error of a p-order method using
// a derivation of Richardson Extrapolation
double estimate_error(double uh, double uh2, int p)
{
    double error;
    error = pow(2, p)/(pow(2, p) - 1) * (uh - uh2);

    return error;
}

#endif