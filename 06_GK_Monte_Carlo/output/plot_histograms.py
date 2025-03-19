import pandas as pd
import matplotlib.pyplot as plt
import matplotlib
matplotlib.rcParams.update({'font.size': 12})

# Define the CSV files and corresponding titles
files_and_titles = [
    ('06_GK_Monte_Carlo/output/observables_1.csv', 'z = 0.56'),
    ('06_GK_Monte_Carlo/output/observables.csv', 'z = 0.84'),
    ('06_GK_Monte_Carlo/output/observables_2.csv', 'z = 1.1')
]

rename_dict = {
    'total_rods': '# Gesamt',
    'horizontal_rods': '# Horizontal',
    'vertical_rods': '# Vertikal',
    #'eta': '$\eta$'
    'S': 'S'
}
fig, axes = plt.subplots(len(files_and_titles), 4, figsize=(12, 2.5 * len(files_and_titles)))

for row, (file, title) in enumerate(files_and_titles):
    df = pd.read_csv(file, comment='#')
    columns = [col for col in df.columns if col in rename_dict]

    for ax, column in zip(axes[row], columns):
        ax.hist(df[column], bins=60, density=True)
        ax.set_title(rename_dict[column], fontsize=14)
    axes[row, 0].set_ylabel(f'{title}', fontsize=16)

fig.suptitle('Histogramme für verschiedene z-Werte', fontsize=16)
plt.tight_layout(rect=[0, 0, 1, 0.95])
plt.savefig('06_GK_Monte_Carlo/output/histograms_combined.png')
plt.close()
