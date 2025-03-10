import numpy as np
from itertools import product

def energy(config, L):
    """Berechnet die Energie einer gegebenen Konfiguration."""
    E = 0
    for i in range(L):
        for j in range(L):
            S = config[i, j]
            neighbors = config[(i+1) % L, j] + config[i, (j+1) % L] + config[(i-1) % L, j] + config[i, (j-1) % L]
            E += -S * neighbors
    return E / 2  # Doppelte Zählung vermeiden

def magnetization(config):
    """Berechnet die Magnetisierung einer Konfiguration."""
    return np.sum(config)

def ising_exact(L, beta_values):
    """Berechnet die mittlere Energie und Magnetisierung durch vollständige Summation."""
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
    
    return results

# Parameter
grid_sizes = [2, 3, 4]
beta_values = np.linspace(0, 1, 10)  # Inverse Temperaturwerte

# Berechnung
data = {L: ising_exact(L, beta_values) for L in grid_sizes}

# Ergebnisse ausgeben
for L, results in data.items():
    print(f"\nGittergröße L = {L}")
    for beta, values in results.items():
        print(f"Beta: {beta:.2f}, E: {values['E']:.4f}, M: {values['M']:.4f}, |M|: {values['|M|']:.4f}")
