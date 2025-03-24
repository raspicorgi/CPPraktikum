import numpy as np
import pandas as pd
from typing import Union
from tqdm import tqdm



def phi_prime(x):
    # Ableitung von phi
    return -np.log(1-x)


def n1(s, L, rho):
    return np.sum(rho[s-L+1:s+1])

def n0(s, L, rho):
    return np.sum(rho[s-L+1:s])


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

def rho_initial(M, L, eta_0):
    # Rho zum Starten der Simulation
    rho = np.full(M, eta_0 / L)
    rho[:L] = 0
    rho[-L:] = 0
    return rho

def exp_pot_ext(M, L):
    # Externes Potential nach Anwendung der Exponentialfunktion (spart Aufrufe an np.exp)
    # M: Anzahl der Gitterpunkte
    # L: Länge der Stäbchen
    V = np.zeros(M)
    V[L:M-L] = 1
    return V

def mu_ex_homog(rho, L, beta = 1.0):
    # Überschüssiges chem. Potential
    return 1/beta * (-L*np.log(1-L*rho) + (L-1)*np.log(1-(L-1)*rho))


def rho_solver(N: int, L: int, eta: float,  thresh: float, max_steps: int, alpha: float, beta: float = 1.0):
    # Löse das DFT-Problem
    rho = rho_initial(N, L, eta)
    V = exp_pot_ext(N, L)
    mu = mu_ex_homog(rho, L, beta)

    ran_steps = 0
    for i in tqdm(range(max_steps), desc=f"eta={eta}, L={L}"):
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



    