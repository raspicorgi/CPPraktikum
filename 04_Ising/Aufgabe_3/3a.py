import Ising_A3_lib as ising
from joblib import Parallel, delayed
from timeit import default_timer as timer
import matplotlib.pyplot as plt
import numpy as np
import os.path


# Parameter
L = 128
h = 0
J = 1
betas = np.linspace(0, 1, 100)

# start timer
start = timer()

# Function to run simulation for a given beta
def run_simulation(beta, index):
    res = ising.simulate_metropolis(h, J, beta, 100, L)
    print(f"Finished simulation #{index + 1} for beta = {beta}")
    return beta, res

# Run simulations in parallel
results = Parallel(n_jobs=-1)(delayed(run_simulation)(beta, i) for i, beta in enumerate(betas))

# stop timer
end = timer()
print(f"Simulation took {end - start} seconds")
# Plot results in separate plots and save them to files

script_dir = os.path.dirname(os.path.abspath(__file__))
plot_dir = os.path.join(script_dir, 'plots3a')
if not os.path.exists(plot_dir):
    os.makedirs(plot_dir)

# Energie plot
plt.figure()
plt.title('Energie')
betas = [beta for beta, result in results]
energies = [result[0] for beta, result in results]
plt.plot(betas, energies, '-o')
plt.xlabel('Beta')
plt.ylabel('Energie')
plt.savefig(os.path.join(plot_dir, 'energie_plot.png'))

# Magnetisierung plot
plt.figure()
plt.title('Magnetisierung')
magnetizations = [result[1] for beta, result in results]
plt.plot(betas, magnetizations, '-o')
plt.xlabel('Beta')
plt.ylabel('Magnetisierung')
plt.savefig(os.path.join(plot_dir, 'magnetisierung_plot.png'))

# Spezifische Wärme plot
plt.figure()
plt.title('Spezifische Wärme')
specific_heats = [result[2] for beta, result in results]
plt.plot(betas, specific_heats, '-o')
plt.xlabel('Beta')
plt.ylabel('Spezifische Wärme')
plt.savefig(os.path.join(plot_dir, 'spezifische_waerme_plot.png'))


