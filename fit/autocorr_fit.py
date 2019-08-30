# This program draws the graph of the autocorrelator
# and fits it with an exponential in order to find tau

from math import *
import matplotlib.pyplot as plt
import numpy as np
from functions import exponential
from scipy.optimize import curve_fit

t_M, gamma = np.genfromtxt("../results/gamma.dat", unpack=True)

fig = plt.figure()
plt.plot(t_M, gamma, ls='', marker='.', c='blue')
best, cov = curve_fit(exponential, t_M, gamma, p0=(1, 1))  # Fit
error = np.sqrt(np.diag(cov))

x = np.linspace(0, len(t_M), 100)
plt.plot(x, exponential(x, *best), c='red',
         lw=0.75, label=r'$y = A \cdot exp(-x/\tau)$')

plt.title(r"Autocorrelator at $t_{phys} = 5$")
plt.xlabel(r"$t_M$")
plt.ylabel("Autocorrelator")
plt.grid(linestyle=':')
plt.legend()
plt.text(34, 0.55, "Parameters:\n\nN = 64\nM = 1\nW = 1",
         size=12, bbox=dict(fc="white"))

# Writing the final results on a file
with open('../results/autocorr_fit.dat', 'w') as f:
    f.write('Results of the fit:\n')
    f.write('A = %f +- %f\n' % (best[0], error[0]))
    f.write('Tau = %.f +- %f\n' % (best[1], error[1]))
    f.write('\nParameters:\nN = 64\nM = 1\nW = 1')

fig.savefig('graphs/autocorr.png', dpi=(200), bbox_inches='tight')
