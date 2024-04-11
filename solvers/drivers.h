#ifndef DRIVERS_H
#define DRIVERS_H

#include <iostream>
#include "json.hpp"
#include "differentiation.h"
#include "integration.h"
#include "first_order_ode.h"
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
    getline(cin, user_input);

    try {
        expr = parse(user_input);
    } catch (SymEngineException &e) {
        cerr << "Error: " << e.what() << endl;
        exit(0);
    }

    return expr;
}

RCP<const Basic> ode_parser()
{
    /*
    Prompts the user to input a function, parses it,
    and prints it.
    */
    RCP<const Basic> expr;
    string user_input;
    cout << "Enter your function, f(u,t) = ";
    getline(cin, user_input);

    try {
        expr = parse(user_input);
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
    cout << "Enter your function, f(x) = ";
    expr = function_parser();
    cout << "Parsed expression: " << expr->__str__() << endl;

    /*
    Request required information from user:
    x0: Starting Point
    xend: End Point
    n: Number of sub-intervals - the slope will be the left point of each subinterval
    NOTE: The slope at xend wll not be calculated since xend + h would be needed for the calculation
    */

    int n;
    double x0, xend;
    string problem = "Single-Variable Differentiation";
    cout << "Enter the starting point, x = ";
    x0 = eval_double(*function_parser());
    cout << "Enter the end point, x = ";
    xend = eval_double(*function_parser());
    cout << "Enter number of sub-intervals, n = ";
    n = static_cast<int> (eval_double(*function_parser()));

    // Save information to json
    json inputData;
    inputData["equation"] = expr->__str__();
    inputData["problem"] = problem;
    inputData["x0"] = x0;
    inputData["xend"] = xend;
    inputData["n"] = n;

    string file_path = "data/differentiation_output.json";
    ofstream outFile;
    outFile.open(file_path);

    if(!outFile) {
        cerr << "Error: Unable to open file " << endl;
        exit(0);
    }

    outFile << inputData.dump(4) << endl;
    outFile.close();

    vector<double> xvec;
    xvec = linspace(x0, xend, n+1);

    data = differentiate(expr, xvec);
    write_data_to_json(data, "data", file_path);
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
    cout << "Parsed expression: " << expr->__str__() << endl;

    /*
    Request required information from user:
    x0: Starting Point
    xend: End Point
    n: Number of sub-intervals - the area of each subinterval will be used to calculate the antiderivative at each point
    initial_condition: Initial condition F(x0) = F0
    */

    int n;
    double x0, xend, initial_condition;
    string problem = "Single-Variable Integration";
    cout << "Enter the starting point, x = ";
    x0 = eval_double(*function_parser());
    cout << "Enter the end point, x = ";
    xend = eval_double(*function_parser());
    cout << "Enter number of sub-intervals, n = ";
    n = static_cast<int> (eval_double(*function_parser()));
    cout << "Enter the initial condition, F(x0) = ";
    initial_condition = eval_double(*function_parser());

    // Save information to json
    json inputData;
    inputData["problem"] = problem;
    inputData["x0"] = x0;
    inputData["xend"] = xend;
    inputData["n"] = n;

    string file_path = "data/integration_output.json";
    ofstream outFile;
    outFile.open(file_path);

    if(!outFile) {
        cerr << "Error: Unable to open file " << endl;
        exit(0);
    }

    outFile << inputData.dump(4) << endl;
    outFile.close();

    vector<double> xvec;
    xvec = linspace(x0, xend, n+1);

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
    write_data_to_json(data, "data", file_path);
}

void c_solver_menu()
{
    /*
    Outputs a list of solvers when 
    (c) First Order ODE
    is selected in the problem menu
    */

    char user_input;

    cout << "(a) Euler's Method" << endl;
    cout << "(b) Backward Euler Method" << endl;
    cout << "(c) Midpoint Method" << endl;
    cout << "(d) Trapezoidal Method" << endl;
    cout << "(e) RK2" << endl;
    cout << "(f) RK3" << endl;
    cout << "(g) RK4" << endl;

    cout << "Enter your selection: ";
    cin >> user_input;
    cin.ignore(255, '\n');

    RCP<const Basic> expr;
    vector<double> data;
    expr = ode_parser();
    cout << "Parsed expression: " << expr->__str__() << endl;

    /*
    Request required information from user:
    t0: Starting Point
    tend: End Point
    n: Number of sub-intervals
    initial_condition: Initial condition u(t0) = u0
    */

    int n;
    double t0, tend, initial_condition;
    string problem = "First Order ODE";
    cout << "Enter the starting point, t = ";
    t0 = eval_double(*function_parser());
    cout << "Enter the end point, t = ";
    tend = eval_double(*function_parser());
    cout << "Enter number of sub-intervals, n = ";
    n = static_cast<int> (eval_double(*function_parser()));
    cout << "Enter the initial condition, u(t0) = ";
    initial_condition = eval_double(*function_parser());

    // Save information to json
    json inputData;
    inputData["problem"] = problem;
    inputData["t0"] = t0;
    inputData["tend"] = tend;
    inputData["n"] = n;

    string file_path = "data/first_order_ODE_output.json";
    ofstream outFile;
    outFile.open(file_path);

    if(!outFile) {
        cerr << "Error: Unable to open file " << endl;
        exit(0);
    }

    outFile << inputData.dump(4) << endl;
    outFile.close();

    vector<double> tvec;
    tvec = linspace(t0, tend, n+1);

    switch (user_input)
    {
        case 'a':
            data = eulers_method(expr, tvec, initial_condition);
            break;
        case 'b':
            data = backward_eulers_method(expr, tvec, initial_condition);
            break;
        case 'c':
            data = two_step_midpoint_method(expr, tvec, initial_condition);
            break;
        case 'd':
            data = trapezoidal_method(expr, tvec, initial_condition);
            break;
        case 'e':
            data = rk2(expr, tvec, initial_condition);
            break;
        case 'f':
            data = rk3(expr, tvec, initial_condition);
            break;
        case 'g':
            data = rk4(expr, tvec, initial_condition);
            break;
    }
    write_data_to_json(data, "data", file_path);
}

#endif