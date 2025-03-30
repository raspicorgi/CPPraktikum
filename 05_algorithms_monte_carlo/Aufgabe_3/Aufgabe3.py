import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import scipy as sp
import math as m

def polynomial(x,*coeff):
    y = 0
    for i, a in enumerate(coeff):
        y += a * x**i
    return y
def legendre_poly(x,*coeff):
    y = 0
    i = 0
    for i,a in enumerate(coeff):
        y += a * n_legendre_poly(x,i)
        
    return y
def n_legendre_poly(x,n):
    y = 0
    for i in range(0,m.floor(n/2)+1):
        y += ((-1)**i)*((m.factorial(2*n-2*i))/(m.factorial(n-i) * m.factorial(n-2*i) * m.factorial(i) * 2**n)) * x **(n-2*i)
    return y
def n_polynomial(x,n):
    return x**n
def chi_squared_poly(x,y,coeff,sigma,func):
    num = (((y - func(x,*coeff))**2)/sigma**2)
    return np.sum(num) / (np.size(x) - len(coeff))
    
def solve_poly_fit(x,y,sigma,func,deg):
    N = len(x)
    # Design-Matrix A berechnen
    A = np.zeros((N, deg))
    for j in range(deg):
        A[:, j] = func(x,j)
    
    # Gewichtungsmatrix W
    W = np.diag(1 / sigma**2)
    
    # Normale Gleichungen: (A^T W A) a = A^T W y
    ATA = A.T @ W @ A
    ATy = A.T @ W @ y
    
    # Lösung des linearen Gleichungssystems durch Inversion von ATA
    a = np.linalg.inv(ATA) @ ATy
    
    return a

data = np.array([[-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9],
                [81,50,35,27,26,60,106,189,318,520]])
sigma = np.sqrt(data[1, :])
x_fit = np.linspace(-1,1,100)
deg = 9

plt.figure("Aufgabe3_poly_fit", figsize=(10,8))
plt.plot(data[0,:],data[1,:],'x',label='Messwerte')
for i in range(0,deg):
    popt,pcov = curve_fit(polynomial,data[0,:],data[1,:],p0=np.ones(i+1))
    plt.plot(x_fit,polynomial(x_fit,*popt),label=fr'Polynom {i} Ordnung, $\chi^2_{{red.}}$ = {chi_squared_poly(data[0,:],data[1,:],popt,sigma,polynomial):.2f}')
plt.xlabel(r'$cos(\theta)$')
plt.ylabel(r'$\frac{d\sigma}{d\Omega}$')
plt.legend()
plt.grid()
plt.title('Polynomiale Anpassung mit curve_fit')

plt.figure("Aufgabe3_legendre_fit", figsize=(10,8))
plt.plot(data[0,:],data[1,:],'x',label='Messwerte')
for i in range(1,deg):
    popt,pcov = curve_fit(legendre_poly,data[0,:],data[1,:],p0=np.ones(i))
    plt.plot(x_fit,legendre_poly(x_fit,*popt),label=fr'Legendre Polynom {i} Ordnung, $\chi^2_{{red.}}$ = {chi_squared_poly(data[0,:],data[1,:],popt,sigma,legendre_poly):.2f}')
plt.xlabel(r'$cos(\theta)$')
plt.ylabel(r'$\frac{d\sigma}{d\Omega}$')
plt.legend()
plt.grid()
plt.title('Legendre Polynom Anpassung mit curve_fit')

plt.figure("Aufgabe3_poly_fit_inv_matrix", figsize=(10,8))
plt.plot(data[0,:],data[1,:],'x',label='Messwerte')
for i in range(1,deg):
    popt = solve_poly_fit(data[0,:],data[1,:],sigma,n_polynomial,i)
    plt.plot(x_fit,polynomial(x_fit,*popt),label=fr'Polynom {i} Ordnung, $\chi^2_{{red.}}$ = {chi_squared_poly(data[0,:],data[1,:],popt,sigma,polynomial):.2f}')
plt.xlabel(r'$cos(\theta)$')
plt.ylabel(r'$\frac{d\sigma}{d\Omega}$')
plt.legend()
plt.grid()
plt.title('Polynomiale Anpassung mit inverser Matrix')

plt.figure("Aufgabe3_legendre_fit_inv_matrix", figsize=(10,8))
plt.plot(data[0,:],data[1,:],'x',label='Messwerte')
for i in range(1,deg):
    popt = solve_poly_fit(data[0,:],data[1,:],sigma,n_legendre_poly,i)
    plt.plot(x_fit,legendre_poly(x_fit,*popt),label=fr'Polynom {i} Ordnung, $\chi^2_{{red.}}$ = {chi_squared_poly(data[0,:],data[1,:],popt,sigma,legendre_poly):.2f}')
plt.xlabel(r'$cos(\theta)$')
plt.ylabel(r'$\frac{d\sigma}{d\Omega}$')
plt.legend()
plt.grid()
plt.title('Polynomiale Anpassung mit inverser Matrix')

plt.show()


