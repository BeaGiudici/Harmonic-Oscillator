# This program draws the graph of the means of the correlators

from math import *
import matplotlib.pyplot as plt
import numpy as np

t, corr = np.genfromtxt("../results/corr_mean.dat", unpack=True)

fig = plt.figure()
plt.plot(t, corr, ls='', marker='.', c='red')
plt.title("Mean of the correlator")
plt.xlabel("t")
plt.ylabel("Correlator")
plt.grid(linestyle=':')
plt.text(50, 150, "Parameters:\n\nN = 64\nM = 1\nW = 1",
         size=12, bbox=dict(fc="white"))
fig.savefig('graphs/corr_mean.png', dpi=(200), bbox_inches='tight')
