import Ising_A3_lib as ising
from joblib import Parallel, delayed
import matplotlib.pyplot as plt


# Parameter
L = 128
h = 0
J = 1
betas = [0.1, 0.4, 0.7, 1]
N_try = 5
N_therm = 6000

def process_beta(beta):
    # Initialisiere Gitter
    print("started calculation for beta = ", beta)
    lattice = ising.init_random_lattice(L)
    energies, lattice = ising.thermalize(lattice, h, J, beta, N_try, N_therm, betas.index(beta))
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