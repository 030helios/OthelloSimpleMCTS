#!/usr/bin/env python3
import numpy as np
import cv2 as cv2
import sys

EdgeSize = int(sys.argv[1])

img = np.full([EdgeSize, EdgeSize, 3], 90)
i = 0
for stone in sys.argv[3].split('.'):
    if stone == '1':
        img[int(i/EdgeSize), i % EdgeSize, :] = 0
    elif stone == '-1':
        img[int(i/EdgeSize), i % EdgeSize, :] = 180
    i += 1
img = np.uint8(img)
img = cv2.resize(img, (512, 512), interpolation=cv2.INTER_AREA)
bordersize = 20
img = cv2.copyMakeBorder(
    img,
    top=bordersize,
    bottom=bordersize,
    left=bordersize,
    right=bordersize,
    borderType=cv2.BORDER_CONSTANT,
    value=[50, 50, 50]
)

cv2.imwrite("Storage/"+sys.argv[2], img)