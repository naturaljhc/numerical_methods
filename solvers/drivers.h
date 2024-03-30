#ifndef DRIVERS_H
#define DRIVERS_H

#include <iostream>
#include "json.hpp"
#include "differentiation.h"
#include "integration.h"
#include <symengine/expression.h>
#include <symengine/parser.h>
#include <vector>

using namespace std;
using namespace SymEngine;
using json = nlohmann::json;

void write_data_to_json(vector<double> data, string key_name, string filename) {
    json jsonData;
    
    ifstream inFile;
    inFile.open(filename);
    inFile >> jsonData;
    inFile.close();
    
    ofstream outFile;
    outFile.open(filename);
    
    if(!outFile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    jsonData[key_name] = data;

    outFile << jsonData.dump(4) << endl;

    outFile.close();
}

RCP<const Basic> function_parser()
{
    /*
    Prompts the user to input a function, parses it,
    and prints it.
    */
    RCP<const Basic> expr;
    string user_input;
    cout << "Enter your function, f(x) = ";
    getline(cin, user_input);

    try {
        expr = parse(user_input);
        cout << "Parsed expression: " << expr->__str__() << endl;
    } catch (SymEngineException &e) {
        cerr << "Error: " << e.what() << endl;
        exit(0);
    }

    return expr;
}

void a_solver_menu()
{
    /*
    There is no menu for 
    (a) Differentiation
    because the only method used here is
    f'(x) = (f(x+h) - f(x)) / h
    */

    RCP<const Basic> expr;
    vector<double> data;
    expr = function_parser();

    /*
    Request required information from user:
    x0: Starting Point
    xend: End Point
    n: Number of points - the slope will be calculated for each of these points
    */

    int n;
    double x0, xend;
    string problem = "Single-Variable Differentiation";
    cout << "Enter the starting point, x = ";
    cin >> x0;
    cout << "Enter the end point, x = ";
    cin >> xend;
    cout << "Enter number of points, n = ";
    cin >> n;

    // Save information to json
    json inputData;
    inputData["equation"] = expr->__str__();
    inputData["problem"] = problem;
    inputData["x0"] = x0;
    inputData["xend"] = xend;
    inputData["n"] = n;

    ofstream outFile;
    outFile.open("data/differentiation_output.json");

    if(!outFile) {
        cerr << "Error: Unable to open file " << endl;
        exit(0);
    }

    outFile << inputData.dump(4) << endl;
    outFile.close();

    vector<double> xvec;
    xvec = linspace(x0, xend + (xend-x0)/(n-1), n+1);

    data = differentiate(expr, xvec);
    write_data_to_json(data, "data", "data/differentiation_output.json");
}

void b_solver_menu()
{
    /*
    Outputs a list of solvers when 
    (b) Single-Variable Integration
    is selected in the problem menu
    */

    char user_input;

    cout << "(a) Left Side Rule" << endl;
    cout << "(b) Right Side Rule" << endl;
    cout << "(c) Midpoint Rule" << endl;
    cout << "(d) Trapezoidal Rule" << endl;
    cout << "(e) Simpson's 1/3 Rule" << endl; 

    cout << "Enter your selection: ";
    cin >> user_input;
    cin.ignore(255, '\n');

    RCP<const Basic> expr;
    vector<double> data;
    expr = function_parser();

    /*
    Request required information from user:
    x0: Starting Point
    xend: End Point
    n: Number of points - the slope will be calculated for each of these points
    initial_condition: Initial condition f(x0) = y0
    */

    int n;
    double x0, xend, initial_condition;
    string problem = "Single-Variable Integration";
    cout << "Enter the starting point, x = ";
    cin >> x0;
    cout << "Enter the end point, x = ";
    cin >> xend;
    cout << "Enter number of points, n = ";
    cin >> n;
    cout << "Enter the initial condition, f(x0) = ";
    cin >> initial_condition;

    // Save information to json
    json inputData;
    inputData["problem"] = problem;
    inputData["x0"] = x0;
    inputData["xend"] = xend;
    inputData["n"] = n;

    ofstream outFile;
    outFile.open("data/integration_output.json");

    if(!outFile) {
        cerr << "Error: Unable to open file " << endl;
        exit(0);
    }

    outFile << inputData.dump(4) << endl;
    outFile.close();

    vector<double> xvec;
    xvec = linspace(x0, xend, n);

    switch (user_input)
    {
        case 'a':
            data = riemann_left_side(expr, xvec, initial_condition);
            break;
        case 'b':
            data = riemann_right_side(expr, xvec, initial_condition);
            break;
        case 'c':
            data = riemann_midpoint(expr, xvec, initial_condition);
            break;
        case 'd':
            data = riemann_trapezoidal(expr, xvec, initial_condition);
            break;
        case 'e':
            data = simpsons_quadratic(expr, xvec, initial_condition);
            break;
    }
    write_data_to_json(data, "data", "data/integration_output.json");
}

#endif