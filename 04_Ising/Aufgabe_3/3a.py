import Ising_A3_lib as ising
from joblib import Parallel, delayed
import matplotlib.pyplot as plt
import numpy as np


# Parameter
L = 128
h = 0
J = 1
betas = np.linspace(0, 1, 10)

# Function to run simulation for a given beta
def run_simulation(beta):
    return beta, ising.simulate_metropolis(h, J, beta, 10)

# Run simulations in parallel
results = Parallel(n_jobs=-1)(delayed(run_simulation)(beta) for beta in betas)

# Plot results in separate plots and save them to files

# Energie plot
plt.figure()
plt.title('Energie')
for beta, result in results:
    plt.plot(beta, result[0], 'o')
    print(f"beta = {beta}, Energie: {result[0]}")
plt.xlabel('Beta')
plt.ylabel('Energie')
plt.savefig('energie_plot.png')

# Magnetisierung plot
plt.figure()
plt.title('Magnetisierung')
for beta, result in results:
    plt.plot(beta, result[1], 'x')
plt.xlabel('Beta')
plt.ylabel('Magnetisierung')
plt.savefig('magnetisierung_plot.png')

# Spezifische Wärme plot
plt.figure()
plt.title('Spezifische Wärme')
for beta, result in results:
    plt.plot(beta, result[2], 's')
plt.xlabel('Beta')
plt.ylabel('Spezifische Wärme')
plt.savefig('spezifische_waerme_plot.png')


