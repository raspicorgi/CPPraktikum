import Ising_A3_lib as ising
from joblib import Parallel, delayed
import matplotlib.pyplot as plt


# Parameter
N = 100
L = 20
h = 0
J = 1
betas = [0.1, 0.5, 1]
N_try = 100
N_therm = 1000

def process_beta(beta):
    # Initialisiere Gitter
    lattice = ising.init_random_lattice(L)
    energies, lattice = ising.thermalize(lattice, h, J, beta, N_try, N_therm, betas.index(beta))
    energies = energies / (L * L) # Energie pro Spin
    return beta, energies

results = Parallel(n_jobs=-1)(delayed(process_beta)(beta) for beta in betas)

for beta, energies in results:
    # Plotte Energie
    plt.plot(energies, label=f"beta = {beta}")
plt.xlabel("Thermalisierungsschritt")
plt.ylabel("Energie")
plt.title("Energie des Gitters nach Thermalisierung")
plt.legend()
plt.show()