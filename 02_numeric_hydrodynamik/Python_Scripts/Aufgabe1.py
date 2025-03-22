import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
xmin = -1
xmax = 1
x = np.arange(-1, 1, 0.001)
a = 1 

def psi_0(x):
    return np.where(np.abs(x) <= 1/3, 1, 0)
def periodic_shift(x, t_max):
    shift = a * t_max
    L = xmax - xmin
    return xmin + np.mod(x - shift + xmax, L)

psi_analytic_t4 = psi_0(periodic_shift(x, 4.0))
psi_analytic_t400 = psi_0(periodic_shift(x, 400.0))
psi_t4_N40_sigma08 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/psi_t4.0s_N40.0_sigma0.8.txt", delimiter= ";")
xb_t4_N40_simga08 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/xb_t4.0_N40.0_sigma0.8.txt", delimiter= ";")
psi_t400_N400_sigma08 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/psi_t400.0s_N400.0_sigma0.8.txt", delimiter= ";")
xb_t400_N400_simga08 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/xb_t400.0_N400.0_sigma0.8.txt", delimiter= ";")
psi_t4_N40_sigma11 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/psi_t4.0s_N40.0_sigma1.1.txt", delimiter= ";")
xb_t4_N40_simga11 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/xb_t4.0_N40.0_sigma1.1.txt", delimiter= ";")
psi_t4_N40_sigma1 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/psi_t4.0s_N40.0_sigma1.0.txt", delimiter= ";")
xb_t4_N40_simga1 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/xb_t4.0_N40.0_sigma1.0.txt", delimiter= ";")
psi_t400_N400_sigma1 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/psi_t400.0s_N400.0_sigma1.0.txt", delimiter= ";")
xb_t400_N400_simga1 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/xb_t400.0_N400.0_sigma1.0.txt", delimiter= ";")
psi_t400_N400_sigma09 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/psi_t400.0s_N400.0_sigma0.9.txt", delimiter= ";")
xb_t400_N400_simga09 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/xb_t400.0_N400.0_sigma0.9.txt", delimiter= ";")
psi_t4_N40_sigma09 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/psi_t4.0s_N40.0_sigma0.9.txt", delimiter= ";")
xb_t4_N40_simga09 = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/02_numeric_hydrodynamik/output/xb_t4.0_N40.0_sigma0.9.txt", delimiter= ";")


# plt.figure("upwind_erweitert_t4s_N40", figsize=(10, 8))
# plt.plot(xb_t4_N40_simga08[2:42], psi_t4_N40_sigma08[2:42], label="Upwind erweitert")
# plt.plot(x, psi_analytic_t4, label="Analytische Lösung")
# plt.xlabel("x")
# plt.ylabel(r"$\psi(x,t=4s)$")
# plt.title("Vergleich der analytischen Lösung und der numerischen Lösung für 40 Gitterpunkte")
# plt.grid()
# plt.legend()
# plt.show()

# plt.figure("upwind_erweitert_t400s_N400", figsize=(10, 8))
# plt.plot(xb_t400_N400_simga08[2:402], psi_t400_N400_sigma08[2:402], label="Upwind erweitert")
# plt.plot(x, psi_analytic_t400, label="Analytische Lösung")
# plt.xlabel("x")
# plt.ylabel(r"$\psi(x,t=400s)$")
# plt.title("Vergleich der analytischen Lösung und der numerischen Lösung für 400 Gitterpunkte")
# plt.grid()
# plt.legend()
# plt.show()

# plt.figure("upwind_erweitert_t4s_N40_s11", figsize=(10, 8))
# plt.plot(xb_t4_N40_simga11[2:42], psi_t4_N40_sigma11[2:42], label="Upwind erweitert")
# plt.plot(x, psi_analytic_t4, label="Analytische Lösung")
# plt.xlabel("x")
# plt.ylabel(r"$\psi(x,t=4s)$")
# plt.title(r"$\sigma = 1.1$, Instabilität, 40 Gitterpunkte")
# plt.grid()
# plt.legend()
# plt.show()

# plt.figure("upwind_erweitert_t4s_N40_s1", figsize=(10, 8))
# plt.plot(xb_t4_N40_simga1[2:42], psi_t4_N40_sigma1[2:42], label="Upwind erweitert")
# #plt.plot(x, psi_analytic_t400, label="Analytische Lösung")
# plt.xlabel("x")
# plt.ylabel(r"$\psi(x,t=4s)$")
# plt.title(r"Vergleich der analytischen Lösung und der numerischen Lösung für 40 Gitterpunkte bei $\sigma = 1$")
# plt.grid()
# plt.legend()
# plt.show()

# plt.figure("upwind_erweitert_t400s_N400_s09", figsize=(10, 8))
# plt.plot(xb_t400_N400_simga09[2:402], psi_t400_N400_sigma09[2:402], label="Upwind erweitert")
# plt.plot(x, psi_analytic_t400, label="Analytische Lösung")
# plt.xlabel("x")
# plt.ylabel(r"$\psi(x,t=400s)$")
# plt.title(r"Vergleich der analytischen Lösung und der numerischen Lösung für 400 Gitterpunkte bei $\sigma = 0.9$")
# plt.grid()
# plt.legend()
# plt.show()


plt.figure("upwind_erweitert_t4s_N40_s09", figsize=(10, 8))
plt.plot(xb_t4_N40_simga09[2:42], psi_t4_N40_sigma09[2:42], label="Upwind erweitert")
plt.plot(x, psi_analytic_t4, label="Analytische Lösung")
plt.xlabel("x")
plt.ylabel(r"$\psi(x,t=4s)$")
plt.title(r"Vergleich der analytischen Lösung und der numerischen Lösung für 40 Gitterpunkte bei $\sigma = 0.9$")
plt.grid()
plt.legend()
plt.show()