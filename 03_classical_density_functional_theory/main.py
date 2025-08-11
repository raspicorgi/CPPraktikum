import dft_lib as dft
import numpy as np
import pandas as pd
import os.path
import matplotlib.pyplot as plt

# Simulation parameters
N = 1000
Ls = [3, 10]
eta_0s = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]
threshold = 1e-12
max_steps = 100000
alpha = 0.001

# DataFrames to store intermediate density profiles and final outputs
df = pd.DataFrame(columns=["L", "eta_0", "rho"])
outputs = pd.DataFrame(columns=["L", "eta_0", "mu", "ST_num", "ST_analytic", "ST_diff", "exc_abs", "Gamma_from_dgamma"])

fig, axes = plt.subplots(1, 2, figsize=(12, 6))

# Loop over rod lengths and packing fractions
for i, L in enumerate(Ls):
    ax = axes[i]
    for eta_0 in eta_0s:
        rho = dft.rho_solver(N, L, eta_0, threshold, max_steps, alpha)
        df.loc[len(df)] = [L, eta_0, rho]
        # only plot left wall
        if L == 3:
            ax.plot(range(L-1, N//50 + L-1), rho[(L-1):(N//50 + L-1)], label=f"eta0={eta_0}")
        else:
            ax.plot(range(L-1, N//10 + L-1), rho[(L-1):(N//10 + L-1)], label=f"eta0={eta_0}")
    ax.set_title(f"L = {L}")
    ax.set_xlabel("s")
    ax.set_ylabel("rho")
    ax.legend()

print("Start calculating surface tensions and chemical potentials")
# For each simulation run, compute quantities of interest
for i, row in df.iterrows():
    L = row["L"]
    eta_0 = row["eta_0"]
    rho = row["rho"]
    rho0 = eta_0 / L
    mu_bulk = np.log(rho0) + dft.mu_ex_homog(rho0, L)
    ST_num = dft.surface_tension_numerical(rho, L)
    ST_analytic = dft.surface_tension_analytical(rho, L)
    exc_abs = dft.excess_adsorption(rho, L)
    outputs.loc[len(outputs)] = [L, eta_0, mu_bulk, ST_num, ST_analytic, ST_num - ST_analytic, exc_abs, np.nan]

# For each rod length L, compute the numerical derivative -d(ST_num)/d(mu) as Gamma from Gibbs’ adsorption equation.
for L in Ls:
    mask = outputs["L"] == L
    group = outputs[mask].sort_values("mu")
    mu_group = group["mu"].values
    ST_group = group["ST_num"].values
    # Compute the derivative d(ST_num)/d(mu)
    dST_dmu = np.gradient(ST_group, mu_group)
    Gamma_from_dgamma = -dST_dmu
    outputs.loc[mask, "Gamma_from_dgamma"] = Gamma_from_dgamma

plt.tight_layout()
plot_path = os.path.join(os.path.dirname(__file__), "outputs", "rho_plots.png")
plt.savefig(plot_path)

# Create a new DataFrame for "exc_abs" and "Gamma_from_dgamma"
adsorption_data = outputs[["L", "eta_0", "exc_abs", "Gamma_from_dgamma"]].copy()

# Save the new DataFrame to a CSV file (if desired)
adsorption_output_path = os.path.join(os.path.dirname(__file__), "outputs", "adsorption_data.csv")
adsorption_data.to_csv(adsorption_output_path, index=False)

print("=========== Adsorption data:")
print(adsorption_data)
print(adsorption_data.to_latex(index=False, float_format=r"\num{%.3e}"))

fig, axes = plt.subplots(1, 2, figsize=(12, 6))

for i, L in enumerate(Ls):
    ax = axes[i]
    mask = outputs["L"] == L
    group = outputs[mask]
    ax.plot(group["eta_0"], group["exc_abs"], label="aus Gleichung (2.23)")
    ax.plot(group["eta_0"], group["Gamma_from_dgamma"], label="aus Gradienten")
    ax.legend()
    ax.set_xlabel(r"$\eta_0$")
    ax.set_ylabel(r"$\Gamma$")
    ax.set_title(f"L = {L}")

plt.tight_layout()
plt.savefig(os.path.join(os.path.dirname(__file__), "outputs", "adsorption_plot.png"))

# remove the "mu", "exc_abs" and "Gamma_from_dgamma" columns from the outputs for nice presentation
outputs = outputs.drop(columns=["mu", "exc_abs", "Gamma_from_dgamma"])

print("=========== Final outputs:")
print(outputs)
print(outputs.to_latex(index=False, float_format=r"\num{%.3e}"))

# Save the density profile data (if desired)
output_path = os.path.join(os.path.dirname(__file__), "outputs", "rho_data.csv")
df.to_csv(output_path, index=False)
