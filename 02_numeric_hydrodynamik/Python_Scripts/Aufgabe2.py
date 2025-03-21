import numpy as np
import matplotlib.pyplot as plt

rho = np.loadtxt("/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output_a2/rho_t0.228s_N100.000_dt0.001.txt",delimiter = ";")
u = np.loadtxt("/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output_a2/u_t0.228s_N100.000_dt0.001.txt",delimiter = ";")
p = np.loadtxt("/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output_a2/p_t0.228s_N100.000_dt0.001.txt",delimiter = ";")
epsilon = np.loadtxt("/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output_a2/epsilon_t0.228s_N100.000_dt0.001.txt",delimiter = ";")
T = np.loadtxt("/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output_a2/T_t0.228s_N100.000_dt0.001.txt",delimiter = ";")
xb = np.loadtxt("/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output_a2/xb_t0.228s_N100.000_dt0.001.txt",delimiter = ";")

plt.figure("Aufgabe2_rho", figsize=(10,8))
plt.plot(xb[2:102], rho[2:102], label="Upwind erweitert")
plt.xlabel("x")
plt.ylabel(r"$\rho(x,t=0.228s)$")
plt.title("Dichte bei t = 0.228s")
plt.grid()
plt.legend()
plt.show()

plt.figure("Aufgbae2_u", figsize=(10,8))
plt.plot(xb[2:102], u[2:102], label="Upwind erweitert")
plt.xlabel("x")
plt.ylabel(r"$u(x,t=0.228s)$")
plt.title("Geschwindigkeit bei t = 0.228s")
plt.grid()
plt.legend()
plt.show()