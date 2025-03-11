import numpy as np
from itertools import product
import scipy.integrate as integrate
import os
import matplotlib.pyplot as plt

def energy(config, L):
    E = 0
    for i in range(L):
        for j in range(L):
            spin = config[i, j]
            neighbors = config[(i+1) % L, j] + config[i, (j+1) % L] + config[(i-1) % L, j] + config[i, (j-1) % L]
            E += -spin * neighbors
    return E / 2  # Doppelte Zählung vermeiden

def magnetization(config):
    return np.sum(config)

def ising_exact(L, beta_values):
    num_spins = L * L
    states = list(product([-1, 1], repeat=num_spins))
    
    results = {beta: {'E': 0, 'M': 0, '|M|': 0, 'Z': 0} for beta in beta_values}
    
    for state in states:
        config = np.array(state).reshape((L, L))
        E = energy(config, L)
        M = magnetization(config)
        
        for beta in beta_values:
            weight = np.exp(-beta * E)
            results[beta]['E'] += E * weight
            results[beta]['M'] += M * weight
            results[beta]['|M|'] += abs(M) * weight
            results[beta]['Z'] += weight
    
    for beta in beta_values:
        results[beta]['E'] /= results[beta]['Z']
        results[beta]['M'] /= results[beta]['Z']
        results[beta]['|M|'] /= results[beta]['Z']
        
        results[beta]['E'] /= (L * L)
        results[beta]['M'] /= (L * L)
        results[beta]['|M|'] /= (L * L)
    
    return results

def analytical_energy(beta):
    tanh_beta = np.tanh(2 * beta)
    cosh_beta = np.cosh(2 * beta)
    xi = 2 * tanh_beta / cosh_beta
    
    def integrand(theta, xi):
        return 1 / np.sqrt(1 - xi**2 * np.sin(theta)**2)
    
    K_xi, _ = integrate.quad(integrand, 0, np.pi/2, args=(xi,))
    
    energy_density = - (1 / tanh_beta) * (1 + (2 * tanh_beta**2 - 1) * 2 / np.pi * K_xi)
    return energy_density

def analytical_magnetization(beta):
    return (1 - np.sinh(2 * beta)**-4) ** (1 / 8)

# Parameter
grid_sizes = [2, 3, 4]
beta_values = np.linspace(0, 1, 200)

# Berechnung
print("Numerische Werte...")
data = {L: ising_exact(L, beta_values) for L in grid_sizes}

print("Analytische Werte...")
data_analytical = {'E': np.array([analytical_energy(beta) for beta in beta_values]),
                   'M': np.array([analytical_magnetization(beta) for beta in beta_values])}

# Ergebnisse ausgeben
for L, results in data.items():
    print(f"\nGittergröße L = {L}")
    for beta, values in results.items():
        print(f"Beta: {beta:.2f}, E: {values['E']:.4f}, M: {values['M']:.4f}, |M|: {values['|M|']:.4f}")
        

# Ergebnisse plotten
colors = ['r', 'g', 'b']
plt.figure(figsize=(12, 8))

for idx, (L, results) in enumerate(data.items()):
    betas = list(results.keys())
    energies = [results[beta]['E'] for beta in betas]
    magnetizations = [results[beta]['M'] for beta in betas]
    abs_magnetizations = [results[beta]['|M|'] for beta in betas]

    plt.subplot(2, 1, 1)
    plt.plot(betas, energies, marker='o', color=colors[idx], label=f'L = {L}')
    plt.ylabel('Energiedichte')

    plt.subplot(2, 1, 2)
    plt.plot(betas, abs_magnetizations, marker='o', color=colors[idx], label=f'L = {L}')
    plt.xlabel('Beta')
    plt.ylabel('|Magnetisierung|')

plt.subplot(2, 1, 1)
plt.plot(beta_values, data_analytical['E'], color='black', linestyle='dashed', label='Analytisch')
plt.title('Energiedichte')

plt.subplot(2, 1, 2)
plt.plot(beta_values, data_analytical['M'], color='black', linestyle='dashed', label='Analytisch')
plt.title('Magnetisierung')

for i in range(2):
    plt.subplot(2, 1, i+1)
    plt.legend()

plt.tight_layout()
script_dir = os.path.dirname(os.path.abspath(__file__))
plot_dir = os.path.join(script_dir, 'plots')
if not os.path.exists(plot_dir):
    os.makedirs(plot_dir)
plot_path = os.path.join(script_dir, 'plots', 'combined_plot.png')
plt.savefig(plot_path)
plt.close()