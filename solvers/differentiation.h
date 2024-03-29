#ifndef DIFFERENTIATION_H
#define DIFFERENTIATION_H

#include <iostream>
#include <iomanip>
#include <symengine/real_double.h>
#include <symengine/eval_double.h>
#include <symengine/expression.h>
#include <symengine/parser.h>
#include <symengine/symbol.h>
#include "linalg_functions.h"
#include <vector>
#include "io_functions.h"

using namespace std;
using namespace SymEngine;

void differentiate(const RCP<const Basic> &f, vector<double> xvec)
{
    RCP<const Basic> x = symbol("x");
    vector<double> dfdx;
    double f_curr, f_next;

    ofstream outFile;
    outFile.open("data/differentiation_output.txt");
    
    double h = xvec[1] - xvec[0];

    for (size_t i = 0; i < xvec.size(); i++)
    {
        f_curr = eval_double(*f->subs({{x, real_double(xvec[i])}}));
        f_next = eval_double(*f->subs({{x, real_double(xvec[i] + h)}}));
        outFile << setprecision(15) << (f_next - f_curr) / h << ' ';
        
    }
    outFile.close();
}

void differentiation()
{
    RCP<const Basic> expr;
    string user_input;
    cout << "Enter your function, f(x) = ";
    getline(cin, user_input);

    try {
        expr = parse(user_input);
        cout << "Parsed expression: " << expr->__str__() << endl;
    } catch (SymEngineException &e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    double n, x0, xend;
    cout << "Enter the starting point, x = ";
    cin >> x0;
    cout << "Enter the end point, x = ";
    cin >> xend;
    cout << "Enter number of points, n = ";
    cin >> n;

    vector<double> xvec;
    xvec = linspace(x0, xend, n);

    differentiate(expr, xvec);
}

#endif