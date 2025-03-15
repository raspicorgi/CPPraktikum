import Ising_A4_lib as ising
from timeit import default_timer as timer
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os.path

# Parameter
L = 128
h_ext = 1
h_step_number = 100
N_sweeps = 1000
J = 1
beta = 0.8

# start timer
start = timer()

# Run simulation
# prepare lattice
lattice = ising.init_thermalized_lattice(L)
# run hysteresis simulation
lattice, hs1, magnetizations1 = ising.hysteresis_simulation(lattice, beta, J, 0, h_ext, h_step_number, N_sweeps, L)
lattice, hs2, magnetizations2 = ising.hysteresis_simulation(lattice, beta, J, h_ext, -h_ext, h_step_number*2, N_sweeps, L)
lattice, hs3, magnetizations3 = ising.hysteresis_simulation(lattice, beta, J, -h_ext, 0, h_step_number, N_sweeps, L)

# stop timer
end = timer()
print(f"Simulation took {end - start} seconds")

script_dir = os.path.dirname(os.path.abspath(__file__))
plot_dir = os.path.join(script_dir, 'outputs4b')
if not os.path.exists(plot_dir):
    os.makedirs(plot_dir)

# Concatenate hs and magnetizations
hs = np.concatenate((hs1, hs2, hs3))
magnetizations = np.concatenate((magnetizations1, magnetizations2, magnetizations3))

data = pd.DataFrame({'h': hs, 'Magnetisierung': magnetizations})
data.to_csv(os.path.join(plot_dir, 'hysteresekurve.csv'), index=False)
print(data)


# Plot results
plt.figure()
plt.title('Hysteresekurve')
plt.plot(hs, magnetizations, '-o')
plt.xlabel('h')
plt.ylabel('Magnetisierung')
plt.savefig(os.path.join(plot_dir, 'hysteresekurve.png'))