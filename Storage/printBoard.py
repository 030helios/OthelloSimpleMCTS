#!/usr/bin/env python3
# special thanks to Ji-Jia-Wu
import sys
import numpy as np
import matplotlib.pyplot as plt

EdgeSize = int(sys.argv[1])

plt.figure(figsize=(5, 5))
ax = plt.gca()

plt.xlim(0, EdgeSize)
plt.ylim(0, EdgeSize)
for i in range(EdgeSize):
    plt.axvline(i)
for j in range(EdgeSize):
    plt.axhline(j)

plt.fill([0, EdgeSize, EdgeSize, 0], [0, 0, EdgeSize, EdgeSize], 'gray')

index = 0

for stone in sys.argv[3].split('.'):
    i = int(index/EdgeSize)
    j = index % EdgeSize
    if stone == '1':
        c = plt.Circle((i+0.5, j+0.5), 0.4, color='black')
        ax.add_patch(c)
    elif stone == '-1':
        c = plt.Circle((i+0.5, j+0.5), 0.4, color='white')
        ax.add_patch(c)
    index += 1

plt.savefig(sys.argv[2])
