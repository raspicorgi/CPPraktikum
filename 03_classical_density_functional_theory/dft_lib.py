import numpy as np
import pandas as pd
from numba import jit

# --- benötigt für Aufgabe 3 ---

@jit(nopython=True)
def phi_prime(x):
    # Ableitung von phi
    return -np.log(1-x)

@jit(nopython=True)
def n1(s, L, rho):
    return np.sum(rho[s-L+1:s+1])

@jit(nopython=True)
def n0(s, L, rho):
    return np.sum(rho[s-L+1:s])

@jit(nopython=True)
def mu_ex(rho, L, beta=1.0):
    res = np.zeros_like(rho)
    for s in range(rho.size):
        first_term = 0
        second_term = 0
        for s_prime in range(s, s+L):
            first_term += phi_prime(n1(s_prime, L, rho))
        for s_prime in range(s+1, s+L):
            second_term += phi_prime(n0(s_prime, L, rho))
        res[s] = first_term - second_term
    return 1/beta * res

@jit(nopython=True)
def rho_initial(M, L, eta_0):
    # Rho zum Starten der Simulation
    rho = np.full(M, eta_0 / L)
    rho[:L] = 0
    rho[-L:] = 0
    return rho

@jit(nopython=True)
def exp_pot_ext(M, L):
    # Externes Potential nach Anwendung der Exponentialfunktion (spart Aufrufe an np.exp)
    # M: Anzahl der Gitterpunkte
    # L: Länge der Stäbchen
    V = np.zeros(M)
    V[L:M-L] = 1
    return V

@jit(nopython=True)
def mu_ex_homog(rho, L, beta = 1.0):
    # Überschüssiges chem. Potential für homogene Systeme
    return 1/beta * (-L*np.log(1-L*rho) + (L-1)*np.log(1-(L-1)*rho))

@jit(nopython=True)
def mu_total(rho, L, beta=1.0):
    # Gesamtes chemisches Potential: ideal + exzess
    return np.log(rho) + mu_ex_homog(rho, L, beta)

# # Helper function: Given bulk packing fraction eta_0 and rod length L, compute mu_total using rho0 = eta_0/L
# def mu_total_homog(eta_0, L, beta=1.0):
#     rho0 = eta_0 / L
#     return np.log(rho0) + mu_ex_homog(rho0, L, beta)

@jit(nopython=True)
def rho_solver(N: int, L: int, eta: float,  thresh: float, max_steps: int, alpha: float, beta: float = 1.0):
    # Löse das DFT-Problem
    rho = rho_initial(N, L, eta)
    V = exp_pot_ext(N, L)
    mu = mu_ex_homog(rho, L, beta)

    ran_steps = 0
    for i in range(max_steps):
        rho_new = eta/L * np.exp(beta * (mu - mu_ex(rho, L, beta))) * V
        diff = np.sum(np.square(rho_new - rho))
        if diff < thresh:
            ran_steps = i
            print("Converged after", ran_steps, "steps")
            break
        rho = (1-alpha) * rho + alpha * rho_new # mixing new and old density
        if i == max_steps - 1:
            print("Did not converge after", max_steps, "steps")
    return rho

# --- benötigt für Aufgabe 5 ---
@jit(nopython=True)
def phi(x):
    return x + (1-x) * np.log(1-x)

@jit(nopython=True)
def surface_tension_analytical(rho: np.ndarray, L: int, beta: float = 1.0):
    rho_0 = rho[rho.shape[0]//2]
    return 1/(2*beta) * ((L-1)*np.log(1-L*rho_0) - L*np.log(1-(L-1)*rho_0))

@jit(nopython=True)
def mu_total_profile(rho, L, beta=1.0):
    return  np.log(rho) + mu_ex_homog(rho, L, beta)

@jit(nopython=True)
def free_energy(rho: np.ndarray, L: int, beta: float=1.0):
    N = len(rho)
    rho_middle = rho[L:N-L]
    F_ex = 0
    for s in range(N):
        F_ex += phi(n1(s, L, rho)) - phi(n0(s, L, rho))
    return 1/beta * (np.sum(rho_middle * (np.log(rho_middle)-1)) + F_ex) # first summand is F_id

@jit(nopython=True)
def GC_pot(rho: np.ndarray, L: int, beta: float=1.0):
    N  = len(rho)
    rho_center = rho[N//2]
    mu = mu_total_profile(rho_center, L, beta)
    F = free_energy(rho, L, beta)
    return F - np.sum(mu * rho)

@jit(nopython=True)
def pressure(rho_0: float, L: int, beta: float=1.0):
    return 1/beta * (np.log(1-(L-1)*rho_0) - np.log(1-L*rho_0))

@jit(nopython=True)
def surface_tension_numerical(rho:np.ndarray, L: int, beta: float = 1.0):
    N = len(rho)
    rho_0 = rho[N//2]
    GC_pot_homog = -pressure(rho_0, L, beta) * ((N-L)-L) 
    return 0.5 * (GC_pot(rho, L, beta) - GC_pot_homog)

@jit(nopython=True)
def excess_adsorption(rho: np.ndarray, L: int):
    N = len(rho)
    rho_0 = rho[N//2]
    rho_middle = rho[L:N-L]
    return 0.5*np.sum(rho_middle - rho_0)
