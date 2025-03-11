import numpy as np
from tqdm import tqdm

def init_random_lattice(L: int) -> np.ndarray:
    """Erstelle ein zufälliges Gitter mit Spins -1 oder 1. Form: (L, L)"""
    return np.random.choice(np.array([-1, 1]), size=(L, L))

def energy(h: float, J: float, lattice: np.ndarray) -> float:
    """Berechne die Energie des Gitters."""
    L = lattice.shape[0]
    E = 0
    for i in range(L):
        for j in range(L):
            E += -J * lattice[i, j] * (lattice[(i+1)%L, j] + lattice[i, (j+1)%L] + lattice[(i-1)%L, j] + lattice[i, (j-1)%L]) / 2 # Doppelzählung vermeiden
    # == Mögliche Alternative für nested for loop:
    # E += -J * np.sum(lattice * (np.roll(lattice, 1, axis=0) + np.roll(lattice, -1, axis=0) + np.roll(lattice, 1, axis=1) + np.roll(lattice, -1, axis=1))) / 2
    
    E -= h * np.sum(lattice)
    return E

def sweep_metropolis(lattice: np.ndarray, h: float, J: float, beta: float, N_try: int) -> np.ndarray:
    """Führe einen Sweep mit dem Metropolis-Algorithmus durch."""
    L = lattice.shape[0]
    for _ in range(L**2):
        i, j = np.random.randint(0, L, size=2)
        s1 = np.random.choice([-1, 1])
        dE = 2 * J * s1 * (lattice[(i+1)%L, j] + lattice[i, (j+1)%L] + lattice[(i-1)%L, j] + lattice[i, (j-1)%L]) + 2 * h * s1
        for _ in range(N_try):
            if (dE < 0) or np.random.uniform() < np.exp(-beta * dE):
                lattice[i, j] = s1

    return lattice

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
    for i in tqdm(range(N_therm), desc=f"Thermalisierung, beta = {beta:.2f}", position=worker_index):
        lattice = sweep_metropolis(lattice, h, J, beta, N_try)
        energies[i] = energy(h, J, lattice)

    return energies, lattice