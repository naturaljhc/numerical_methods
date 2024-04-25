import streamlit as st
import numpy as np
import matplotlib.pyplot as plt
import subprocess
import time

def pipe_input(var):
    global cpp_process
    cpp_process.stdin.write(var + '\n')
    cpp_process.stdin.flush()
    return

def differentiation():
    global cpp_process

    expr = st.text_input("Enter your function, f(x) = ")
    x0 = st.text_input("Enter the starting point, x = ")
    xend = st.text_input("Enter the end point, x = ")
    n = st.text_input("Enter number of sub-intervals, n = ")

    if st.button("Run"):
        pipe_input('a')
        pipe_input(expr)
        pipe_input(x0)
        pipe_input(xend)
        pipe_input(n)
    
        while (cpp_process.poll() is None):
            time.sleep(0.5)
        
        import json

        with open("data/differentiation_output.json", 'r') as file:
            data = json.load(file)

        x0 = data["x0"]
        xend = data["xend"]
        n = data["n"]

        x = np.linspace(x0, xend, n+1)
        y = np.array(data["data"])

        fig, ax = plt.subplots()
        ax.plot(x[:-1], y)
        ax.grid(True)
        ax.set_title(rf"Derivative of ${expr}$")
        st.pyplot(fig)

def single_value_integration():
    global cpp_process

    solvers = {"Left Side Rule": "a",
               "Right Side Rule": "b",
               "Midpoint Rule": "c",
               "Trapezoidal Rule": "d",
               "Simpson's 1/3 Rule": "e"}

    solver = st.selectbox(
        "Select a solver: ", solvers.keys()
    ) 
    solver = solvers[solver]

    expr = st.text_input("Enter your function, f(x) = ")
    x0 = st.text_input("Enter the starting point, x = ")
    xend = st.text_input("Enter the end point, x = ")
    n = st.text_input("Enter number of sub-intervals, n = ")

    if st.button("Run"):
        pipe_input('b')
        pipe_input(solver)
        pipe_input(expr)
        pipe_input(x0)
        pipe_input(xend)
        pipe_input(n)
    
        while (cpp_process.poll() is None):
            time.sleep(0.5)
        
        import json

        with open("data/integration_output.json", 'r') as file:
            data = json.load(file)

        st.write(f"{data['data']}")

def first_order_ode():
    global cpp_process

    solvers = {"Euler's Method": "a",
               "Backward Euler Method": "b",
               "Trapezoidal Method": "c",
               "RK2": "d",
               "RK3": "e",
               "RK4": "f"}

    solver = st.selectbox(
        "Select a solver: ", solvers.keys()
    ) 
    solver = solvers[solver]

    expr = st.text_input("Enter your function, f(u,t) = ")
    x0 = st.text_input("Enter the starting point, t = ")
    xend = st.text_input("Enter the end point, t = ")
    n = st.text_input("Enter number of sub-intervals, n = ")
    u0 = st.text_input("Enter the initial condition, u(t0) = ")

    if st.button("Run"):
        pipe_input('c')
        pipe_input(solver)
        pipe_input(expr)
        pipe_input(x0)
        pipe_input(xend)
        pipe_input(n)
        pipe_input(u0)
    
        while (cpp_process.poll() is None):
            time.sleep(0.5)
        
        import json

        with open("data/first_order_ODE_output.json", 'r') as file:
            data = json.load(file)

        t0 = data["t0"]
        tend = data["tend"]
        n = data["n"]

        t = np.linspace(t0, tend, n+1)
        u = np.array(data["data"])

        fig, ax = plt.subplots()
        ax.plot(t, u)
        ax.grid(True)
        ax.set_xlabel("t")
        ax.set_ylabel("u")
        ax.set_title(rf"u(t)")
        st.pyplot(fig)

def main():
    global cpp_process
    cpp_process = None
    
    st.title("Numerical Simulations")

    problem_types = ("Differentiation",
                     "Single-Variable Integration",
                     "First Order ODE")

    problem = st.selectbox(
        "Select the problem type: ",
        problem_types
    )

    cpp_process = subprocess.Popen(["./main"], stdin = subprocess.PIPE, stdout = subprocess.PIPE, text = True)
    if (problem == "Differentiation"):
        differentiation()
    if (problem == "Single-Variable Integration"):
        single_value_integration()
    if(problem == "First Order ODE"):
        first_order_ode()

if __name__== "__main__":
    main()