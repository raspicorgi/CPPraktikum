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

for file, title in files_and_titles:
    df = pd.read_csv(file, comment='#')
    # Create subplots
    fig, axes = plt.subplots(1, 5, figsize=(15, 3))
    columns = [col for col in df.columns if col != 'step']
    for ax, column in zip(axes, columns):
        # Plot the data
        ax.hist(df[column], bins=60, density=True)
        ax.set_title(column, fontsize=16)
    fig.suptitle(f'Histogramme für {title}')#, fontsize=20)
    plt.tight_layout()
    plt.savefig(f'06_GK_Monte_Carlo/output/histograms_{title}.png')
    plt.close()