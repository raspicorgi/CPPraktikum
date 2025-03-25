import dft_lib as dft
import numpy as np
import pandas as pd
import os.path
import matplotlib.pyplot as plt

N = 100
Ls = [3, 10]
eta_0s = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]

threshold = 1e-12
max_steps = 100000
alpha = 0.001


df = pd.DataFrame(columns=["L", "eta_0", "rho"])
fig, axes = plt.subplots(1, 2, figsize=(12, 6))

for i, L in enumerate(Ls):
    ax = axes[i]
    for eta_0 in eta_0s:
        rho = dft.rho_solver(N, L, eta_0, threshold, max_steps, alpha)
        df.loc[len(df)] = [L, eta_0, rho]
        ax.plot(range(L-1, N//5 + L-1), rho[(L-1):(N//5 + L-1)], label=f"$\eta$={eta_0}")
    ax.set_title(f"L = {L}")
    ax.set_xlabel("s")
    ax.set_ylabel("rho")
    ax.legend()

plt.tight_layout()
plt.show()


output_path = os.path.join(os.path.dirname(__file__), "rho_data.csv")
df.to_csv(output_path, index=False)