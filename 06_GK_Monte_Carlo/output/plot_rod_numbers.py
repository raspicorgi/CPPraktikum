import pandas as pd
import matplotlib.pyplot as plt

# Load the data
df = pd.read_csv('06_GK_Monte_Carlo/output/orientations_1.csv', comment='#')

# Plot the data
plt.figure(figsize=(10, 6))

plt.plot(df['step'], df['total_rods'], label='Total Rods')
plt.plot(df['step'], df['horizontal_rods'], label='Horizontal Rods')
plt.plot(df['step'], df['vertical_rods'], label='Vertical Rods')
plt.legend()

plt.savefig('06_GK_Monte_Carlo/output/rod_numbers.png')