#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "solvers/drivers.h"
#include <symengine/expression.h>
#include <vector>

using namespace std;
using namespace SymEngine;

// Requesting user inputs and expressions should happen in here
// Solvers should only contain the solver itself and return the data
// Then save the data through a function in here

void problem_menu()
{   
    /*
    Outputs a list of different problems that this program can solve
    */
    char user_input;

    cout << "(a) Differentiation" << endl;
    cout << "(b) Single-Variable Integration" << endl;
    cout << "(c) First Order ODE" << endl; 

    cout << "Select the type of problem: " << endl;
    cin >> user_input;
    cin.ignore(255, '\n');

    RCP<const Basic> expr;
    vector<double> data;
    switch (user_input)
    {
        case 'a':
            a_solver_menu();
            break;
        case 'b':
            b_solver_menu();
            break;
        case 'c':
            c_solver_menu();
            break;
    }
}

int main() 
{
    problem_menu();
    return 0;
}