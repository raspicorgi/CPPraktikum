import pandas as pd
import matplotlib.pyplot as plt
import matplotlib
matplotlib.rcParams.update({'font.size': 15})

# Define the CSV files and corresponding titles
files_and_titles = [
    ('06_GK_Monte_Carlo/output/observables_1.csv', 'Thermalisierung für $z = 0.56$'),
    ('06_GK_Monte_Carlo/output/observables.csv', 'Thermalisierung für $z = 0.84$'),
    ('06_GK_Monte_Carlo/output/observables_2.csv', 'Thermalisierung für $z = 1.1$')
]

# Create subplots
fig, axes = plt.subplots(3, 1, figsize=(10, 15), sharex=True)


for ax, (file, title) in zip(axes, files_and_titles):
    # Load the data
    df = pd.read_csv(file, comment='#')
    
    # Plot the data
    ax.plot(df['step'], df['total_rods'], label='Stäbchen gesamt')
    ax.plot(df['step'], df['horizontal_rods'], label='horizontale Stäbchen')
    ax.plot(df['step'], df['vertical_rods'], label='vertikale Stäbchen')
    ax.set_ylabel('Anzahl Stäbchen', fontsize=14)
    ax.set_title(title, fontsize=16)
    ax.legend(fontsize=12, loc = 'lower right')

# Set common x-label
axes[-1].set_xlabel('Schritt', fontsize=14)

# Adjust layout and save the figure
plt.tight_layout()
plt.savefig('06_GK_Monte_Carlo/output/rod_numbers_stacked.png')
