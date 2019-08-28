# This program draws two graphs: the first plots the time used to calculate
# the correlators as a function of N (that must be a parabola), while the
# other plots the time used to complete the Metropolis (that must be a line)

from math import *
import matplotlib.pyplot as plt
import numpy as np
import json
from scipy.optimize import curve_fit
import functions as f

data = json.load(open('../results/times.json', 'r'))
N = np.array([32, 64, 128, 256])
t_corr = np.zeros(len(N))
t_metr = np.zeros(len(N))
err_m = np.zeros(len(N))
err_c = np.zeros(len(N))
for n in N:
    i = list(N).index(n)
    vM = np.array([line["Metropolis"] for line in filter(
        lambda item: item["N"] == n, data)])
    vC = np.array([line["Correlators"] for line in filter(
        lambda item: item["N"] == n, data)])
    t_metr[i] = np.sum(vM) / len(vM)
    t_corr[i] = np.sum(vC) / len(vM)
    mean2_m = np.sum(vM*vM) / len(vC)
    mean2_c = np.sum(vC*vC) / len(vC)
    err_m[i] = np.sqrt((mean2_m - t_metr[i]*t_metr[i])/len(vM))
    err_c[i] = np.sqrt((mean2_c - t_corr[i]*t_corr[i])/len(vC))
    print('N = %i' % n)
    print('Time of the correlator: %f +- %f' % (t_corr[i], err_c[i]))
    print('Time of the metropolis: %f +- %f' % (t_metr[i], err_m[i]))
print("\n")
x = np.linspace(min(N), max(N), 100)

fig1 = plt.figure(1)
plt.errorbar(N, t_corr, yerr=err_c, ls='', marker='.', markersize=1,
             elinewidth=0.5, capsize=2.5, mec='red', ecolor='red')
best, c = curve_fit(f.quadratic, N, t_corr, p0=(10, 1, 0.1), sigma=err_c)
plt.plot(x, f.quadratic(x, *best), ls='-', color='b', linewidth=0.9)
plt.grid(linestyle=':')
plt.title("Behaviour of the computational times of the correlators")
plt.xlabel("N")
plt.ylabel(r"$t_{corr}$ (s)")
print("CORRELATORS")
print("Parameters: ", best)
print("Errors of the parameters: ", np.sqrt(np.diag(c)))
print("Covariance: ", c)

fig2 = plt.figure(2)
plt.errorbar(N, t_metr, yerr=err_m, ls='', marker='.', markersize=1,
             elinewidth=0.5, capsize=2.5, mec='red', ecolor='red')
best, c = curve_fit(f.linear, N, t_metr, p0=(1, 1), sigma=err_m)
plt.plot(x, f.linear(x, *best), ls='-', color='b', linewidth=0.9)
plt.grid(linestyle=':')
plt.title("Behavior of the computational times of the Metropolis")
plt.xlabel("N")
plt.ylabel(r"$t_{metr}$ (s)")

print("\nMETROPOLIS")
print("Parameters: ", best)
print("Errors of the parameters: ", np.sqrt(np.diag(c)))
print("Covariance: ", c)

fig1.savefig("graphs/correlators_times.png", dpi=(200), bbox_inches='tight')
fig2.savefig("graphs/metropolis_times.png", dpi=(200), bbox_inches='tight')
