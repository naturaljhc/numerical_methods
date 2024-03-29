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
#include <fstream>
#include <vector>
#include "io_functions.h"
#include "json.hpp"

using namespace std;
using namespace SymEngine;
using json = nlohmann::json;

void differentiate(const RCP<const Basic> &f, vector<double> xvec)
{
    RCP<const Basic> x = symbol("x");
    vector<double> dfdx;
    double f_curr, f_next;
    
    double h = xvec[1] - xvec[0];

    for (size_t i = 0; i < xvec.size(); i++)
    {
        f_curr = eval_double(*f->subs({{x, real_double(xvec[i])}}));
        f_next = eval_double(*f->subs({{x, real_double(xvec[i]+h)}}));
        dfdx.push_back((f_next - f_curr)/h);
    }

    write_data_to_json(dfdx, "data", "data/differentiation_output.json");
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
    
    int n;
    double x0, xend;
    cout << "Enter the starting point, x = ";
    cin >> x0;
    cout << "Enter the end point, x = ";
    cin >> xend;
    cout << "Enter number of points, n = ";
    cin >> n;

    // Save [x0, xend] and n to json
    json inputData;
    inputData["x0"] = x0;
    inputData["xend"] = xend;
    inputData["n"] = n;

    ofstream outFile;
    outFile.open("data/differentiation_output.json");

    if(!outFile) {
        cerr << "Error: Unable to open file " << "test" << endl;
        return;
    }

    outFile << inputData.dump(4) << endl;
    outFile.close();

    vector<double> xvec;
    xvec = linspace(x0, xend, n);

    differentiate(expr, xvec);
}

#endif