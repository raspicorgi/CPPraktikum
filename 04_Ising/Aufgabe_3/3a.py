import Ising_A3_lib as ising
import matplotlib.pyplot as plt


# Parameter
N = 100
L = 20
h = 0
J = 1
betas = [0.1, 0.5, 1]
N_try = 100
N_therm = 1000

for beta in betas:
    # Initialisiere Gitter
    lattice = ising.init_random_lattice(L)
    energies, lattice = ising.thermalize(lattice, h, J, beta, N_try, N_therm)

    # Plotte Energie
    plt.plot(energies, label=f"beta = {beta}")
plt.xlabel("Thermalisierungsschritt")
plt.ylabel("Energie")
plt.title("Energie des Gitters nach Thermalisierung")
plt.legend()
plt.show()