#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "solvers/differentiation.h"

using namespace std;

char problem_menu()
{   
    char user_input;

    cout << "(a) Differentiation" << endl;
    // cout << "(b) Single-Variable Integration" << endl;
    // cout << "(d) Multi-variable integration" << endl;
    // cout << "(c) First Order ODE"; 
    cin >> user_input;
    cin.ignore(255, '\n');
    return user_input;
}

void solver_menu();

void file_reader();

int main() 
{
    char problem_choice;
    problem_choice = problem_menu();
    
    switch (problem_choice)
    {
        case 'a':
            differentiation();
            break;
    }
    return 0;
}