import numpy as np
from numba import njit, prange
from tqdm import tqdm

@njit
def init_random_lattice(L: int) -> np.ndarray:
    """Erstelle ein zufälliges Gitter mit Spins -1 oder 1. Form: (L, L)"""
    return 2 * np.random.randint(0, 2, size=(L, L)) - 1 ## hotfix because random.choice not available in numba

@njit
def init_thermalized_lattice(L: int) -> np.ndarray:
    """Erstelle ein thermalisiertes Gitter mit Spins -1 oder 1. Form: (L, L)"""
    lattice = init_random_lattice(L)
    for i in range(4000):
        lattice = sweep_heat_bath(lattice, 1, 0, 1, 5)
    return lattice

@njit
def energy_density(h: float, J: float, lattice: np.ndarray) -> float:
    """Berechne die Energie des Gitters."""
    L = lattice.shape[0]
    E = 0
    for i in prange(L):
        for j in prange(L):
            E += -J * lattice[i, j] * (lattice[(i+1)%L, j] + lattice[i, (j+1)%L] + lattice[(i-1)%L, j] + lattice[i, (j-1)%L]) / 2 # Doppelzählung vermeiden
    # == Mögliche Alternative für nested for loop:
    # E += -J * np.sum(lattice * (np.roll(lattice, 1, axis=0) + np.roll(lattice, -1, axis=0) + np.roll(lattice, 1, axis=1) + np.roll(lattice, -1, axis=1))) / 2
    
    E -= h * np.sum(lattice)
    return E / L**2

@njit
def magnetization(lattice: np.ndarray) -> float:
    return np.sum(lattice) / lattice.size

@njit
def draw(lattice: np.ndarray, h: float, J: float, beta: float, N_try: int, N_draw: int) -> np.ndarray:
    for i in range(N_draw):
        lattice = sweep_heat_bath(lattice, beta, h, J, N_try)
    return lattice

@njit
def simulate_metropolis(h: float, J: float, beta: float, sweeps: int, L: int) -> tuple:
    lattice = init_thermalized_lattice(L)

    energies = np.empty(sweeps)
    magnetizations = np.empty(sweeps)
    energies_sq = np.empty(sweeps)
    magnetizations_sq = np.empty(sweeps)

    for i in range(sweeps):
        lattice = sweep_heat_bath(lattice, beta, h, J, 1)
        energies[i] = energy_density(h, J, lattice)
        magnetizations[i] = np.abs(magnetization(lattice))
        energies_sq[i] = energies[i]**2
        magnetizations_sq[i] = magnetizations[i]**2

    mean_energy = np.mean(energies)
    mean_magnetization = np.mean(magnetizations)
    mean_energy_sq = np.mean(energies_sq)
    mean_magnetization_sq = np.mean(magnetizations_sq)

    specific_heat = beta**2 * (mean_energy_sq - mean_energy**2)

    return mean_energy, mean_magnetization, specific_heat, mean_magnetization_sq

@njit(parallel=True)
def sweep_heat_bath(lattice: np.ndarray, beta: float, h: float = 0.0, J: float = 1.0,  N_try: int = 5) -> np.ndarray:
    """Führe einen Sweep mit dem Wärmebad-Algorithmus durch."""
    # TODO Implementieren
    L = lattice.shape[0]
    for i in prange(L):
        for j in prange(L):
            delta = lattice[(i+1)%L, j] + lattice[i, (j+1)%L] + lattice[(i-1)%L, j] + lattice[i, (j-1)%L]
            k = beta * (J * delta + h)
            z = 2 * np.cosh(k)
            q = np.exp(k) / z
            r = np.random.uniform(0, 1)
            if (r < q):
                lattice[i, j] = 1
            else:
                lattice[i, j] = -1
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
        lattice = sweep_heat_bath(lattice, beta, h, J, N_try)
        energies[i] = energy_density(h, J, lattice)

    return energies, lattice