# This program uses the results of single_fit.py to draw the final graphs of
# the mean of the energy and the mean of the matrix element versus a**2

from math import *
import functions as f
import matplotlib.pyplot as plt
import numpy as np
import json
from scipy.optimize import curve_fit


data = json.load(open('../results/cont_limit.json', 'r'))
a = np.array([data[i]["a"] for i in range(len(data))])
E_mean = np.array([data[i]["energy"]["value"] for i in range(len(data))])
error_E = np.array([data[i]["energy"]["error"] for i in range(len(data))])
mel = np.array([data[i]["mel"]["value"] for i in range(len(data))])
error_mel = np.array([data[i]["mel"]["error"] for i in range(len(data))])
x = np.linspace(min(a), max(a), 100)

# ENERGIES
fig1 = plt.figure(1)
plt.title('Mean of the energy step')
plt.errorbar(a, E_mean/a, yerr=error_E/a, ls='', linewidth=0.5, marker='.', markersize=1,
             elinewidth=0.5, capsize=2.5)
best, covar = curve_fit(f.quadratic, a, E_mean/a,
                        p0=(1., -1/24, 3/640), sigma=error_E/a)
plt.plot(x, f.quadratic(x, *best), ls='-', c='r')

d = len(a) - len(best)  # Degree of freedom of the fit

plt.xlabel('a')
plt.ylabel(r'$\langle \Delta \bar{E} \rangle / W$')
plt.grid(linestyle=':')

chi = f.red_chi_sq(
    E_mean/a, f.quadratic(a, *best), error_E/a, dof=d)

print("ENERGIES:")
for i in range(len(a)):
    print('a = %f, DeltaE/W = %f, Error = %f' %
          (a[i], E_mean[i]/a[i], error_E[i]/a[i]))
print('\n')
print("\tParameters: ", best)
print("\tError of the parameters: ", np.sqrt(np.diag(covar)))
print("t-factor for the parameters: ",
      np.fabs((best - [1., -1/24, 3/640])/np.sqrt(np.diag(covar))))

print("\tReduced chi-square = %f" % chi)
print("\tCHI^2 / ndf = %f / %f\n" % (chi*d, d))

# MATRIX ELEMENTS
fig2 = plt.figure(2)
plt.title('Mean of the matrix element')
plt.errorbar(a, mel, yerr=error_mel, ls='', marker='.', markersize=1,
             elinewidth=0.5, capsize=2.5, ecolor='b')
best, covar = curve_fit(f.quadratic, a, mel,
                        p0=(1/np.sqrt(2), -np.sqrt(2)/32, 5*np.sqrt(2)/1024), sigma=error_mel)
plt.plot(x, f.quadratic(x, *best), ls='-', c='r')

d = len(a) - len(best)  # Degree of freedom of the fit

plt.xlabel('a')
plt.ylabel('Matrix element')
plt.grid(linestyle=':')

chi = f.red_chi_sq(mel, f.quadratic(a, *best), error_mel, dof=d)

print("MATRIX ELEMENTS:")
for i in range(len(a)):
    print('a = %f, mel = %f, error = %f' % (a[i], mel[i], error_mel[i]))
print('\n')
print("\tParameters: ", best)
print("\tErrors of the parameters: ", np.sqrt(np.diag(covar)))
print("\tCovariance: ", covar)
print("t-factor for the parameters: ",
      np.fabs((best - [1/np.sqrt(2), -np.sqrt(2)/32, 5*np.sqrt(2)/1024])/np.sqrt(np.diag(covar))))
print("\tReduced chi-square = %f" % chi)
print("\tCHI^2 / ndf = %f / %f" % (chi*d, d))

fig1.savefig('graphs/energy_vs_a.png', dpi=(200), bbox_inches='tight')
fig2.savefig('graphs/mel_vs_a.png', dpi=(200), bbox_inches='tight')
