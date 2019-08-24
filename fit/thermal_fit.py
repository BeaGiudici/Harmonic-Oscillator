# This program draws the graphs of the action versus the Markovian
# time for the hot and the cold starts of the thermalization

from math import *
import matplotlib.pyplot as plt
import numpy as np

i_cold, S_cold = np.genfromtxt("../results/cold_therm.dat", unpack=True)
i_hot, S_hot = np.genfromtxt("../results/hot_therm.dat", unpack=True)

fig1 = plt.figure(1)
plt.plot(i_cold[:100], S_cold[:100], ls='-',
         lw=1, c='blue', label='Cold Start')
plt.plot(i_hot[:100], S_hot[:100], ls='-', lw=1, c='red', label='Hot Start')
plt.title("Thermalization")
plt.xlabel("Markovian time")
plt.ylabel("S")
plt.grid(linestyle=':')
plt.legend()
plt.text(77.5, 420, "Parameters:\n\nN = 64\nM = 1\nW = 1",
         size=12, bbox=dict(fc="white"))

# Zoom on the first 25 indices
fig2 = plt.figure(2)
plt.plot(i_cold[:26], S_cold[:26], ls='-',
         lw=1, c='blue', label='Cold Start')
plt.plot(i_hot[:26], S_hot[:26], ls='-',
         lw=1, c='red', label='Hot Start')
plt.title("Thermalization (zoom)")
plt.xlabel("Markovian time")
plt.ylabel("S")
plt.grid(linestyle=':')
plt.legend()
plt.text(19.57, 420, "Parameters:\n\nN = 64\nM = 1\nW = 1",
         size=12, bbox=dict(fc="white"))

# Saving the graphs
fig1.savefig('graphs/first_thermalization.png', dpi=(200), bbox_inches='tight')
fig2.savefig('graphs/thermalization.png', dpi=(200), bbox_inches='tight')
