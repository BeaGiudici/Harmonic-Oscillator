# This program draws the graphs of the energies and the matrix elements for the
# different values of a; then, it finds the mean value of them and it writes all
# of them on two files, every time with the corrispettive value of a

from math import *
import matplotlib.pyplot as plt
import numpy as np
import json
import sys

if len(sys.argv) == 1:
    print('ERROR: Number of arguments not correct')
    print('Please compile as\n\tpython3 %s <file_energies> <file_mel>' %
          sys.argv[0])
    exit(1)
else:
    file_energies = sys.argv[1]
    file_mel = sys.argv[2]

results = {
    "a": 0,
    "energy": {"value": 0, "error": 0},
    "mel": {"value": 0, "error": 0}
}

# ENERGIES
with open(file_energies, 'r') as f:
    N = int(f.readline())
t, dE, err = np.genfromtxt(file_energies, unpack=True, skip_header=1)
results["a"] = 64/N

# I consider only the values with a relative error lower than a threshold
counter = 0
for j in range(len(dE)):
    if(err[j]/dE[j] < 0.008):
        counter += 1
# The values are symmetric, so the final result must be divided by 2
counter = int(counter/2)

# Plotting the energy differences with their errors
fig1 = plt.figure()
plt.errorbar(t, dE, yerr=err, ls='', marker='.', markersize=1,
             color='r', elinewidth=0.5, capsize=2.5, ecolor='b')
plt.title(r"$\Delta$ E for a = %f" % results["a"])
plt.xlabel("t")
plt.ylabel(r"$\Delta$ E")
plt.grid(linestyle=':')

# Plotting the errors of the energies, when there is still signal,
# to underline the exponential behaviour
if N == 512:
    fig3 = plt.figure()
    plt.title("First relative errors of the energy")
    plt.xlabel("t")
    plt.ylabel(r"$\sigma_r$")
    plt.grid(linestyle=':')
    plt.plot(t[:counter+1], err[:counter+1]/dE[:counter+1],
             ls='', marker='.', c='blue')

# Calculating the mean of the energies and its error
if counter != 0:
    if counter < 5:
        weight = list(map(lambda x: 1/(x*x), err[1:counter+1]))
        results["energy"]["value"] = sum(dE[1:counter+1]*weight) / sum(weight)
        results["energy"]["error"] = np.sqrt(1/sum(weight))
    else:
        results["energy"]["value"] = sum(dE[1:counter+1]) / counter
        mean2 = sum(dE[1:counter+1]*dE[1:counter+1]) / counter
        results["energy"]["error"] = np.sqrt(
            mean2 - results["energy"]["value"]**2)
else:
    results["energy"]["value"] = dE[1]
    results["energy"]["error"] = err[1]


# MATRIX ELEMENTS
with open(file_mel, 'r') as f:
    N = int(f.readline())
t, mel, err = np.genfromtxt(file_mel,
                            unpack=True, skip_header=1)

# I consider only the values with a relative error lower than a threshold
counter = 0
for j in range(len(mel)):
    if(err[j]/mel[j] < 0.01):
        counter += 1
# The values are symmetric, so the final result must be divided by 2
counter = int(counter/2)

# Plotting the matrix elements and their errors
fig2 = plt.figure()
plt.errorbar(t, mel, yerr=err, ls='', marker='.', markersize=1,
             color='r', elinewidth=0.5, capsize=2.5, ecolor='b')
plt.title("Matrix elements of the matrix element")
plt.xlabel("t")
plt.ylabel("Matrix element")
plt.grid(linestyle=':')

# Plotting the errors of the energies, when there is still signal,
# to underline the exponential behaviour
if N == 512:
    fig4 = plt.figure()
    plt.title("First relative errors of the matrix element")
    plt.xlabel("t")
    plt.ylabel(r"$\sigma_r$")
    plt.grid(linestyle=':')
    plt.plot(t[:counter+1], err[:counter+1]/mel[:counter+1],
             ls='', marker='.', c='blue')


# Calculating the mean of the matrix elements and its error
if counter != 0:
    if counter < 5:
        weight = list(map(lambda x: 1/(x*x), err[1:counter+1]))
        results["mel"]["value"] = sum(mel[1:counter+1]*weight) / sum(weight)
        results["mel"]["error"] = np.sqrt(1/sum(weight))
    else:
        results["mel"]["value"] = sum(mel[1:counter+1]) / counter
        mean2 = sum(mel[1:counter+1]*mel[1:counter+1]) / counter
        results["mel"]["error"] = np.sqrt(
            mean2 - results["mel"]["value"]**2)
else:
    results["mel"]["value"] = mel[1]
    results["mel"]["error"] = err[1]

with open('../results/cont_limit.json', 'a') as f:
    json.dump(results, f, indent=4)
    if results["a"] != 0.125:
        f.write(',\n')

fig1.savefig('graphs/deltaE_%d.png' % N, dpi=(200), bbox_inches='tight')
fig2.savefig('graphs/mel_%d.png' % N, dpi=(200), bbox_inches='tight')
if N == 512:
    fig3.savefig('graphs/energy_errors.png', dpi=(200), bbox_inches='tight')
    fig4.savefig('graphs/mel_errors.png', dpi=(200), bbox_inches='tight')
