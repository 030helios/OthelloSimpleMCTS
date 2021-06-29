#!/usr/bin/env python3
import numpy as np
import cv2 as cv2
import sys

img = np.full([8, 8, 3], 100)
i = 0
for stone in sys.argv[1].split('.'):
    if stone == '1':
        img[int(i/8), i % 8, :] = 0
    elif stone == '-1':
        img[int(i/8), i % 8, :] = 255
    i += 1
img = np.uint8(img)
img = cv2.resize(img, (512, 512), interpolation=cv2.INTER_AREA)
bordersize = 10
img = cv2.copyMakeBorder(
    img,
    top=bordersize,
    bottom=bordersize,
    left=bordersize,
    right=bordersize,
    borderType=cv2.BORDER_CONSTANT,
    value=[50, 50, 50]
)
cv2.imwrite('output.jpg', img)