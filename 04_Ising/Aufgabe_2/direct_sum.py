import numpy as np
import math

def ising_2d_energy(spin_config):
    """Berechnet die Energie einer gegebenen 2D-Ising-Modell-Spinkonfiguration."""
    energy = 0
    rows, cols = spin_config.shape
    for i in range(rows):
        for j in range(cols):
            spin = spin_config[i, j]
            # Periodische Randbedingungen
            neighbors = spin_config[(i+1)%rows, j] + spin_config[i, (j+1)%cols] + \
                        spin_config[(i-1)%rows, j] + spin_config[i, (j-1)%cols]
            energy += -spin * neighbors
    return energy / 2  # Jede Interaktion wurde doppelt gezählt

def ising_2d_magnetization(spin_config):
    """Berechnet die Magnetisierung einer gegebenen 2D-Ising-Modell-Spinkonfiguration."""
    return np.sum(spin_config)

def generate_spin_configs(L):
    """Generiert alle möglichen Spinkonfigurationen für ein L x L Gitter."""
    total_configs = 2**(L*L)
    spin_configs = np.zeros((total_configs, L, L), dtype=int)
    for i in range(total_configs):
        binary = bin(i)[2:].zfill(L*L)
        spin_configs[i] = np.array([1 if bit == '1' else -1 for bit in binary]).reshape(L, L)
    return spin_configs

def calculate_observables(L, betas):
    """Berechnet die innere Energiedichte, Magnetisierung und spezifische Wärme für gegebene Betas."""
    spin_configs = generate_spin_configs(L)
    num_configs = len(spin_configs)
    
    energy_densities = []
    magnetizations = []
    abs_magnetizations = []
    specific_heat = []

    for beta in betas:
        avg_energy = 0
        avg_magnetization = 0
        avg_sq_magnetization = 0
        avg_energy_sq = 0

        for config in spin_configs:
            energy = ising_2d_energy(config)
            magnetization = ising_2d_magnetization(config)

            avg_energy += energy
            avg_magnetization += magnetization
            avg_sq_magnetization += magnetization**2
            avg_energy_sq += energy**2

        avg_energy /= num_configs
        avg_magnetization /= num_configs
        avg_sq_magnetization /= num_configs
        avg_energy_sq /= num_configs

        energy_densities.append(avg_energy / (L*L))
        magnetizations.append(avg_magnetization / (L*L))
        abs_magnetizations.append(abs(avg_magnetization) / (L*L))
        specific_heat.append((avg_energy_sq - avg_energy**2) * beta**2 / (L*L))

    return energy_densities, magnetizations, abs_magnetizations, specific_heat

# Parameter
L_values = [2, 3, 4]
betas = np.linspace(0, 1, 20)

# Berechnung und Ausgabe
for L in L_values:
    energy_densities, magnetizations, abs_magnetizations, specific_heat = calculate_observables(L, betas)
    
    print(f"Ergebnisse für L = {L}:")
    for i, beta in enumerate(betas):
        print(f"  beta = {beta:.2f}, Energie = {energy_densities[i]:.4f}, |Magnetisierung| = {abs_magnetizations[i]:.4f}, Spezifische Wärme = {specific_heat[i]:.4f}")
    print("\n")