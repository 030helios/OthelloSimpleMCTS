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
cv2.imshow("image", img)
key = cv2.waitKey(2500)