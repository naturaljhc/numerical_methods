# Numerical Methods
Program to solve math problems using numerical methods in C++ and then plotting the solutions in Python.

## Differentiation
Single-Variable Differentiation: Accepts a function, $f(x)$, and calculates the derivative at any given point, $x_i$, in a given interval using step size $h$. 
```math
f'(x_i) =  \frac{f(x_i+h) - f(x_i)}{h}
```

## Integration
Single-Variable Integration: Accepts a function, $f(x)$, and calculates the integral using a cumulative sum. Calculates the integral at any given point, $x_i$, in a given interval using step size, $h$, and initial condition, $F(x_0) = F_0$. 
* Left Side Rule: 
```math
F(x_i) = F_0 + h \times \sum^{i-1}_{j=0} f(x_j) \quad \text{for } i \geq 1
```
* Right Side Rule: 
```math
F(x_i) = F_0 + h \times \sum^{i}_{j=1} f(x_{j}) \quad \text{for } i \geq 1
```
* Midpoint Rule:
```math
F(x_i) = F_0 + h \sum^{i}_{j=1} f \bigg( \frac{x_{j}+x_{j-1}}{2} \bigg) \quad \text{for } i \geq 1
```
* Trapezoidal Rule:
```math
F(x_i) = F_0 + h \sum^{i}_{j=1} \frac{f(x_{j})+f(x_{j-1})}{2} \quad \text{for } i \geq 1
```
* Simpson's 1/3 (Quadratic) Rule:
```math
F(x_i) = F_0 + h \sum^{i}_{j=1} \frac{h}{6}\bigg[f(x_{j-1})+4*f\bigg(x_{j} + \frac{h}{2}\bigg) + f(x_j)\bigg] \quad \text{for } i \geq 1 
```
## Ordinary Differential Equations
First Order Ordinary Differential Equations: Accepts a function $f(u(t), t)$ and numerically calculates $u(t)$ within a given interval using step size, $h$, and initial condition, $u(t_0)=u_0$.
* Euler Method:
```math
u(t_{i+1}) = u(t_i) + hf(u(t_i),t_i)
```
* Backward Euler Method: Not implemented yet due to needing a root finding method (such as Newton's Method) to solve $u_{i+1} - u_i - hf(u_{i+1}, t_{i+1})=0$.
```math
u(t_{i+1}) = u(t_i) + hf(u(t_{i+1}),t_i)
```
## Systems of Ordinary Differential Equations

## Partial Differential Equations

## Systems of Partial Differential Equations