# Numerical Methods
Program to solve math problems using numerical methods in C++ and then plotting the solutions in Python.

## Differentiation
Single-Variable Differentiation: Accepts a function, $f(x)$, and calculates the derivative at any given point, $x_i$, in a given interval using step size $h$. 

$$ f'(x_i) =  \frac{f(x_i+h) - f(x_i)}{h} $$

## Integration
Single-Variable Integration: Accepts a function, $f(x)$, and calculates the integral using a cumulative sum. Calculates the integral at any given point, $x_i$, in a given interval using step size, $h$, and initial condition.
* Left Side Rule: 

$$ F(x_i) = F_0 + h * \sum^{i}_{j=0} f(x_j) $$

* Right Side Rule: 


$$ F(x_i) = F_0 + h * \sum^{i}_{j=0} f(x_{j+1}) $$


## Ordinary Differential Equations

## Systems of Ordinary Differential Equations

## Partial Differential Equations

## Systems of Partial Differential Equations
