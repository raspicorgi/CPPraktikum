import Ising_A4_lib as ising
import numpy as np
import matplotlib.pyplot as plt
import os.path
import pandas as pd
from mpl_toolkits.mplot3d import Axes3D


# Parameter
L = 128
hs = np.linspace(-1, 1, 10)
J = 1
betas = np.linspace(0, 1, 10)
N_sweeps = 1000

output_hs = []
output_betas = []
output_magnetizations = []
output_magnetizations_abs = []

# Run simulation
for h in hs:
    for beta in betas:
        mag, mag_abs = ising.simulate_heatbath(h, J, beta, N_sweeps, L)
        output_hs.append(h)
        output_betas.append(beta)
        output_magnetizations.append(mag)
        output_magnetizations_abs.append(mag_abs)


script_dir = os.path.dirname(os.path.abspath(__file__))
plot_dir = os.path.join(script_dir, 'outputs4c')
if not os.path.exists(plot_dir):
    os.makedirs(plot_dir)

output = pd.DataFrame({'h': output_hs, 'beta': output_betas, 'Magnetisierung': output_magnetizations, 'Magnetisierung_abs': output_magnetizations_abs})
output.to_csv(os.path.join(plot_dir, 'output.csv'), index=False)
print(output)


fig = plt.figure(figsize=(14, 6))

# 3D plot for Magnetization
ax1 = fig.add_subplot(121, projection='3d')
ax1.plot_trisurf(output['h'], output['beta'], output['Magnetisierung'], cmap='viridis')
ax1.set_xlabel('h')
ax1.set_ylabel('beta')
ax1.set_zlabel('Magnetisierung')
ax1.set_title('Magnetisierung vs h and beta')

# 3D plot for Magnetization_abs
ax2 = fig.add_subplot(122, projection='3d')
ax2.plot_trisurf(output['h'], output['beta'], output['Magnetisierung_abs'], cmap='plasma')
ax2.set_xlabel('h')
ax2.set_ylabel('beta')
ax2.set_zlabel('Magnetisierung_abs')
ax2.set_title('Magnetisierung_abs vs h and beta')

plt.tight_layout()
plt.savefig(os.path.join(plot_dir, 'magnetization_plots.png'))
plt.show()