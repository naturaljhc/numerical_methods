import streamlit as st
import numpy as np
import matplotlib.pyplot as plt
import subprocess
import time

def streamlit_io():
    global cpp_process
    prompt = cpp_process.stdout.readline().strip()
    var = st.text_input(prompt)
    if var != "":
        cpp_process.stdin.write(var + '\n')
        cpp_process.stdin.flush()
        return var

def differentiation():
    global cpp_process

    expr = streamlit_io()
    st.write(cpp_process.stdout.readline().strip())

    x0 = streamlit_io()
    xend = streamlit_io()
    n = streamlit_io()

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
    
def main():
    global cpp_process
    cpp_process = None
    
    st.title("Numerical Simulations")

    cpp_process = subprocess.Popen(["./main"], stdin = subprocess.PIPE, stdout = subprocess.PIPE, text = True)
    
    problem_types = (cpp_process.stdout.readline()[4:].strip(),
                     cpp_process.stdout.readline()[4:].strip(),
                     cpp_process.stdout.readline()[4:].strip())
    
    problem = st.selectbox(
        cpp_process.stdout.readline().strip(),
        problem_types
    )

    if (problem == "Differentiation"):
        cpp_process.stdin.write('a' + '\n')
        cpp_process.stdin.flush()
        differentiation()

if __name__== "__main__":
    main()