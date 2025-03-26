import dft_lib as dft
import numpy as np
import pandas as pd
import os.path
import matplotlib.pyplot as plt

N = 1000
Ls = [3, 10]
eta_0s = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]

threshold = 1e-12
max_steps = 100000
alpha = 0.001


df = pd.DataFrame(columns=["L", "eta_0", "rho"])
outputs = pd.DataFrame(columns=["L", "eta_0", "ST_num", "ST_analytic", "ST_diff", "exc_abs"])
fig, axes = plt.subplots(1, 2, figsize=(12, 6))

for i, L in enumerate(Ls):
    ax = axes[i]
    for eta_0 in eta_0s:
        rho = dft.rho_solver(N, L, eta_0, threshold, max_steps, alpha)
        df.loc[len(df)] = [L, eta_0, rho]
        ax.plot(range(L-1, N//50 + L-1), rho[(L-1):(N//50 + L-1)], label=rf"$\eta$={eta_0}")
    ax.set_title(f"L = {L}")
    ax.set_xlabel("s")
    ax.set_ylabel("rho")
    ax.legend()

print("start calculating surface tensions")
for i, row in df.iterrows():
    L = row["L"]
    eta_0 = row["eta_0"]
    rho = row["rho"]
    ST_num = dft.surface_tension_numerical(rho, L)
    ST_analytic = dft.surface_tension_analytical(rho, L)
    exc_abs = dft.excess_adsorption(rho, L)
    outputs.loc[len(outputs)] = [L, eta_0, ST_num, ST_analytic, ST_num - ST_analytic, exc_abs]

plt.tight_layout()
plt.savefig(os.path.join(os.path.dirname(__file__), "outputs", "rho_plots.png"))

df.astype({"L": int, "eta_0": float})
print(outputs)
print(outputs.to_latex(index=False, float_format=r"\num{%.3e}"))

output_path = os.path.join(os.path.dirname(__file__), "outputs",  "rho_data.csv")
df.to_csv(output_path, index=False)