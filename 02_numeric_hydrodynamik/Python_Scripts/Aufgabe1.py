import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
xmin = -1
xmax = 1
N = 40
x = np.arange(-1, 1, 0.001)
t_max = 4
a = 1 

def psi_0(x):
    return np.where(np.abs(x) <= 1/3, 1, 0)
def periodic_shift(x, t_max):
    shift = a * t_max
    L = xmax - xmin
    return xmin + np.mod(x - shift + xmax, L)

psi_analytic = psi_0(periodic_shift(x, t_max))
psi_t4_N40 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/psi_t4_N40.txt", delimiter= ";")
x_b = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/x_b.txt", delimiter= ";")

plt.figure("upwind_erweitert_t4s_N40", figsize=(10, 8))
plt.plot(x_b[2:42], psi_t4_N40[2:42], label="Upwind erweitert")
plt.plot(x, psi_analytic, label="Analytische Lösung")
plt.xlabel("x")
plt.ylabel(r"$\psi(x,t=4s)$")
plt.title("Vergleich der analytischen Lösung und der numerischen Lösung für 40 Gitterpunkte")
plt.grid()
plt.legend()
plt.show()
