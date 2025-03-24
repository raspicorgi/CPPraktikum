import numpy as np
from scipy.optimize import minimize
import matplotlib.pyplot as plt

# Define the function
def N(t,N0,N1,N2,l1,l2):
    return N0 + N1*np.exp(-l1*t) + N2*np.exp(-l2*t)

def chi_squared(x):
    num = (((data[:,1] - N(data[:,0],*x))**2)/sigma**2)
    return np.sum(num)

data = np.loadtxt(r"/home/sasch/Studium/CPPraktikum/05_algorithms_monte_carlo/Aufgbae_4/Agdecay.dat")
sigma = np.sqrt(data[:,1])
t_fit = np.linspace(0,120,200)

x0 = [0, 800, 100, 0.1, 0.01]

popt_DS = minimize(chi_squared,x0,method = 'Nelder-Mead')
N_fit_DS = N(t_fit,*popt_DS.x)

popt_CG = minimize(chi_squared,x0,method = 'CG')
N_fit_CG = N(t_fit,*popt_CG.x)

plt.figure("Aufgabe4", figsize=(10,8))
plt.plot(data[:,0], data[:,1], "x", label="Data", color="b")
plt.plot(t_fit, N_fit_DS, label=fr'Downhill Simplex, $\chi^2$ = {chi_squared(popt_DS.x):.2f}',color = (0.301, 0.886, 0.0),lw=2)
plt.plot(t_fit, N_fit_CG, label=fr'Conjugate Gradient $\chi^2$ = {chi_squared(popt_CG.x):.2f}', c = 'r',lw=2)
plt.xlabel("Zeit [s]")
plt.ylabel("Counts")
plt.title("Zerfall von Ag, Downhill Simplex vs. Conjugate Gradient")
plt.legend()
plt.grid()

with open(r'/home/sasch/Studium/CPPraktikum/05_algorithms_monte_carlo/Aufgbae_4/params.txt',"w") as file:
    file.write('Downhill Simplex:\n')
    file.write(f'N0: {popt_DS.x[0]}\n')
    file.write(f'N1: {popt_DS.x[1]}\n')
    file.write(f'N2: {popt_DS.x[2]}\n')
    file.write(f'l1: {popt_DS.x[3]}\n')
    file.write(f'l2: {popt_DS.x[4]}')
    file.write('\n\n')
    file.write('Conjugate Gradient:\n')
    file.write(f'N0: {popt_CG.x[0]}\n')
    file.write(f'N1: {popt_CG.x[1]}\n')
    file.write(f'N2: {popt_CG.x[2]}\n')
    file.write(f'l1: {popt_CG.x[3]}\n')
    file.write(f'l2: {popt_CG.x[4]}')
    file.close()