import pandas as pd
import matplotlib.pyplot as plt
import os.path
from mpl_toolkits.mplot3d import Axes3D

script_dir = os.path.dirname(os.path.abspath(__file__))
plot_dir = os.path.join(script_dir, 'outputs4c')
if not os.path.exists(plot_dir):
    os.makedirs(plot_dir)

output = pd.read_csv(os.path.join(plot_dir, 'output.csv'))


fig = plt.figure(figsize=(14, 6))

# 3D plot for Magnetization
ax1 = fig.add_subplot(121, projection='3d')
ax1.plot_trisurf(output['h'], output['beta'], output['Magnetisierung'], cmap='viridis')
ax1.set_xlabel('h')
ax1.set_ylabel(r'$\beta$')
ax1.set_zlabel('Magnetisierung')
ax1.invert_xaxis()
ax1.set_title('Magnetisierung')

# 3D plot for Magnetization_abs
ax2 = fig.add_subplot(122, projection='3d')
ax2.plot_trisurf(output['h'], output['beta'], output['Magnetisierung_abs'], cmap='plasma')
ax2.set_xlabel('h')
ax2.set_ylabel(r'$\beta$')
ax2.set_zlabel('|Magnetisierung|')
ax2.set_title('Betrag der Magnetisierung')

plt.tight_layout()
plt.savefig(os.path.join(plot_dir, 'magnetization_plots.png'))
plt.show()