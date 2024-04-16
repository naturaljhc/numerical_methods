# Numerical Methods
Program to solve math problems using numerical methods in C++ and then plotting the solutions in Python.

## Differentiation
Single-Variable Differentiation: Accepts a function, $f(x)$, and calculates the derivative at any given point, $x_i$, in a given interval using step size $h$. 
```math
f'(x_i) =  \frac{f(x_i+h) - f(x_i)}{h}
```

## Integration
Single-Variable Integration: Accepts a function, $f(x)$, and calculates the integral in a given interval, $[x_0, x_N]$, using step size, $h$. 
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
## First Order Ordinary Differential Equations
First Order Ordinary Differential Equations: Accepts a function $f(u(t), t)$ and numerically calculates $u(t)$ within a given interval using step size, $h$, and initial condition, $u(t_0)=u_0$.
* Euler's Method:
```math
u_{i+1} = u_i + hf(u_i,t_i)
```
* Backward Euler's Method: Uses Newton's Method to solve $u_{i+1} - u_i - hf(u_{i+1}, t_{i+1})=0$.
```math
u_{i+1} = u_i + hf(u_{i+1},t_{i+1})
```
* Trapezoidal Method: Uses Newton's Method to solve $u_{i+1} - u_i - \frac{h}{2}(f(u_i, t_i) + f(u_{i+1}, t_{i+1})) = 0$
```math
u_{i+1} = u_i + \frac{h}{2}(f(u_i, t_i) + f(u_{i+1}, t_{i+1}))
```
* Second Order Runge-Kutta (RK2 - Midpoint Method)
```math
\begin{align*}
k_1 &= h f(u_i, t_i) \\
k_2 &= h f\Big(u_i + \frac{k_1}{2}, t_i + \frac{h}{2}\Big) \\
u_{i+1} &= u_i + k_2
\end{align*}
```
* Third Order Runge-Kutta (RK3 - Midpoint Method)
```math
\begin{align*}
k_1 &= h f(u_i, t_i) \\
k_2 &= h f\Big(u_i + \frac{k_1}{2}, t_i + \frac{h}{2}\Big) \\
k_3 &= h f(u_i - k_1 + 2k_2, t_i + h) \\
u_{i+1} &= u_i + \frac{1}{6}k_1 + \frac{2}{3}k_2 + \frac{1}{6}k_3
\end{align*}
```
* Fourth Order Runge-Kutta (RK4)
```math
\begin{align*}
k_1 &= h f(u_i, t_i) \\
k_2 &= h f\Big(u_i + \frac{k_1}{2}, t_i + \frac{h}{2}\Big) \\
k_3 &= h f\Big(u_i + \frac{k_2}{2}, t_i + \frac{h}{2}\Big) \\
k_4 &= h f(u_i + k_3, t_i + h) \\
u_{i+1} &= u_i + \frac{1}{6}k_1 + \frac{1}{3}k_2 + \frac{1}{3}k_3 + \frac{1}{6}k_4
\end{align*}
```

## Appendix
* Newton's Method: Approximates the roots of a real-valued function, $f(x)$. Note that the derivative is approximated using central finite differences
```math
\begin{align*}
x_{i+1} &= x_i - \frac{f(x_i)}{f'(x_i)}
\end{align*}
```
* Error Estimation: Errors of each method can be approximated when the order, $p$, is known. Two simulations are performed, one with step size, $h$, and another with step size, $\frac{h}{2}$
```math
\begin{align*}
E(h) &= \frac{2^p}{2^p-1}\Bigg(T(h) - T\bigg(\frac{h}{2}\bigg)\Bigg)
\end{align*} 
```