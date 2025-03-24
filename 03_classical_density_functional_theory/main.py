import dft_lib as dft
import numpy as np
import pandas as pd

N = 100
Ls = [3, 10]
eta_0s = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]

threshold = 1e-12
max_steps = 100000
alpha = 0.1


for L in Ls:
    for eta_0 in eta_0s:
        rho = dft.rho_solver(N, L, eta_0, threshold, max_steps, alpha)