import Ising_A4_lib as ising
from joblib import Parallel, delayed
from timeit import default_timer as timer
import matplotlib.pyplot as plt
import numpy as np
from pprint import pprint
import os.path


# Parameter
Ls = np.array([4, 8, 32])
h = 0
J = 1
beta = 0.4406868

# start timer
start = timer()

# Function to run simulation for a given beta
def run_simulation(L, index):
    res = ising.simulate_heatbath(h, J, beta, sweeps=200000, L=L)
    print(f"Finished simulation #{index + 1} for L = {L}")
    return L, res

# Run simulations in parallel
results = Parallel(n_jobs=-1)(delayed(run_simulation)(L, i) for i, L in enumerate(Ls))

# stop timer
end = timer()
print(f"Simulation took {end - start} seconds")
# Plot results in separate plots and save them to files

script_dir = os.path.dirname(os.path.abspath(__file__))
plot_dir = os.path.join(script_dir, 'plots3b')
if not os.path.exists(plot_dir):
    os.makedirs(plot_dir)

# # Energie plot
# plt.figure()
# plt.title('Energie')
# betas = [beta for beta, result in results]
# energies = [result[0] for beta, result in results]
# plt.plot(betas, energies, '-o')
# plt.xlabel('Beta')
# plt.ylabel('Energie')
# plt.savefig(os.path.join(plot_dir, 'energie_plot.png'))

# # Magnetisierung plot
# plt.figure()
# plt.title('Magnetisierung')
# magnetizations = [result[1] for beta, result in results]
# plt.plot(betas, magnetizations, '-o')
# plt.xlabel('Beta')
# plt.ylabel('$\\langle M \\rangle$')
# plt.savefig(os.path.join(plot_dir, 'magnetisierung_plot.png'))

# # Spezifische Wärme plot
# plt.figure()
# plt.title('Quadrat der Magnetisierung')
# magnetizations_sq = [result[3] for beta, result in results]
# plt.plot(betas, magnetizations_sq, '-o')
# plt.xlabel('Beta')
# plt.ylabel('$\\langle M^2 \\rangle$')
# plt.savefig(os.path.join(plot_dir, 'magnetisierung_quadrat_plot.png'))



print("Ergebnisse:")
print("Energien:")
pprint({f"L = {L}\n\t": result[0] for L, result in results})
print("Magnetisierungen:")
pprint({f"L = {L}\n\t": result[1] for L, result in results})
print("Magnetisierungen²:")
pprint({f"L = {L}\n\t": result[3] for L, result in results})
