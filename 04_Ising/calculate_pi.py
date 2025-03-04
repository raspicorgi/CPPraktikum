import matplotlib.pyplot as plt
import numpy as np
import random
import tqdm.tqdm as tqdm

num_trials = 100

for i in range(num_trials):
    x = random.uniform(-1, 1)
    y = random.uniform(-1, 1)
    if x**2 + y**2 < 1:
        plt.plot(x, y, 'bo')
    else:
        plt.plot(x, y, 'ro')