#ifndef LINALG_FUNCTIONS_H
#define LINALG_FUNCTIONS_H

#include <iostream>
#include <vector>

using namespace std;

vector<double> linspace(double x0, double xend, int n)
{
    vector<double> x;
    double h = (xend - x0) / (n - 1);

    for (int i = 0; i < n; ++i)
    {
        x.push_back(x0 + i * h);
    }

    return x;
}

#endif