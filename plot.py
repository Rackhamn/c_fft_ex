import matplotlib.pyplot as plt
import numpy as np
import sys

xpoints = []
ypoints = []

# "Single-Sided Amplitude Spectrum of X(t)")
title = sys.stdin.readline()

# Sampling Rate (hz), 1000
Fs = int(sys.stdin.readline())

# Number of Samples (half will be given), 1024
L = int(sys.stdin.readline())

f = Fs/L*(L/2)

for line in sys.stdin:
    xpoints.append(len(xpoints))
    ypoints.append(float(line) * 2.0)

plt.plot(xpoints, ypoints)
plt.title(title)
plt.show()

