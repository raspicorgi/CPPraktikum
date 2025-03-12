import numpy as np
from numba import njit, prange
from tqdm import tqdm

def init_random_lattice(L: int) -> np.ndarray:
    """Erstelle ein zufälliges Gitter mit Spins -1 oder 1. Form: (L, L)"""
    return 2 * np.random.randint(0, 2, size=(L, L)) - 1 ## hotfix because random.choice not available in numba

@njit
def energy(h: float, J: float, lattice: np.ndarray) -> float:
    """Berechne die Energie des Gitters."""
    L = lattice.shape[0]
    E = 0
    for i in prange(L):
        for j in prange(L):
            E += -J * lattice[i, j] * (lattice[(i+1)%L, j] + lattice[i, (j+1)%L] + lattice[(i-1)%L, j] + lattice[i, (j-1)%L]) / 2 # Doppelzählung vermeiden
    # == Mögliche Alternative für nested for loop:
    # E += -J * np.sum(lattice * (np.roll(lattice, 1, axis=0) + np.roll(lattice, -1, axis=0) + np.roll(lattice, 1, axis=1) + np.roll(lattice, -1, axis=1))) / 2
    
    E -= h * np.sum(lattice)
    return E

@njit(parallel=True)
def sweep_metropolis(lattice: np.ndarray, h: float, J: float, beta: float, N_try: int) -> np.ndarray:
    """Führe einen Sweep mit dem Metropolis-Algorithmus durch."""
    L = lattice.shape[0]
    for i in prange(L):
        for j in prange(L):
            s1 = 2 * np.random.randint(0, 2) - 1  # Generate a single spin value
            dE = 2 * -J * s1 * (lattice[(i+1)%L, j] + lattice[i, (j+1)%L] + lattice[(i-1)%L, j] + lattice[i, (j-1)%L]) + 2 * h * s1
            for _ in range(N_try):
                if (dE < 0) or np.random.uniform() < np.exp(-beta * dE):
                    lattice[i, j] = s1

    return lattice

@njit
def thermalize(lattice: np.ndarray, h: float, J: float, beta: float, N_try: int, N_therm: int, worker_index: int) -> np.ndarray:
    """
    Thermalisiere das Gitter.
    Parameters:
    lattice (np.ndarray): Das anfängliche Gitter.
    h (float): Externes Magnetfeld.
    J (float): Wechselwirkungsstärke.
    beta (float): Inverse Temperatur (1/kT).
    N_try (int): Anzahl der Versuche pro Sweep.
    N_therm (int): Anzahl der Thermalisierungsschritte.
    Returns:
    tuple: Ein Tupel bestehend aus:
        - energies (np.ndarray): Array der Energien nach jedem Thermalisierungsschritt.
        - lattice (np.ndarray): Das thermalisierte Gitter.
    """
    """Thermalisiere das Gitter."""
    energies = np.zeros(N_therm)
    L = lattice.shape[0]
    for i in range(N_therm): # tqdm(range(N_therm), desc=f"Thermalisierung, beta = "+ beta, position=worker_index):
        lattice = sweep_metropolis(lattice, h, J, beta, N_try)
        energies[i] = energy(h, J, lattice)

    return energies, lattice