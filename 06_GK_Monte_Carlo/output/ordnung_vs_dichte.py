import pandas as pd
import matplotlib.pyplot as plt
import matplotlib
matplotlib.rcParams.update({'font.size': 12})

# Define the CSV files and corresponding titles
files_and_zs = [
    ('06_GK_Monte_Carlo/output/observables0.050000.csv', '0.05'),
    ('06_GK_Monte_Carlo/output/observables0.125000.csv', '0.125'),
    ('06_GK_Monte_Carlo/output/observables0.250000.csv', '0.25'),
    ('06_GK_Monte_Carlo/output/observables_1.csv', '0.56'),
    ('06_GK_Monte_Carlo/output/observables.csv', '0.84'),
    ('06_GK_Monte_Carlo/output/observables_2.csv', '1.1'),
    ('06_GK_Monte_Carlo/output/observables1.150000.csv', '1.15'),
    ('06_GK_Monte_Carlo/output/observables1.500000.csv', '1.5')
]

etas = []
eta_stds = []
Ordnungsparameter = []
S_stds = []

for file, z in files_and_zs:
    df = pd.read_csv(file, comment='#')
    etas.append(df['eta'].mean())
    eta_stds.append(df['eta'].std())
    S_abs = df['S'].abs()
    Ordnungsparameter.append(S_abs.mean())
    S_stds.append(S_abs.std())
    

fig = plt.figure(figsize=(8, 5))
# plt.scatter(zs, means)
plt.errorbar(etas, Ordnungsparameter, xerr=eta_stds, yerr=S_stds, fmt='o', capsize=5)
plt.xlabel("Dichte $\eta$")
plt.ylabel("Ordnungsparameter $|S|$")
plt.title("Ordnungsparameter $|S|$ in Abhängigkeit der Dichte")
plt.grid()
plt.savefig('06_GK_Monte_Carlo/output/ordnung_vs_dichte.png')
plt.close()
