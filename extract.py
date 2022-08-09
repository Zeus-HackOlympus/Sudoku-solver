#!/usr/bin/env python3 
import cv2
import tensorflow as tf
import numpy as np 
from imutils.perspective import four_point_transform, order_points
from skimage.segmentation import clear_border
from tensorflow.keras.models import load_model

def extract(): 
    image = cv2.imread("./question.jpeg")
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    kernel = np.array([[0, 1, 0], [1, 1, 1], [0, 1, 0]], np.uint8)
    gray = cv2.dilate(gray, kernel)

    blurred = cv2.GaussianBlur(gray, (5, 5), 0)


    thresh = cv2.adaptiveThreshold(
        blurred, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY_INV, 11, 2
    )



    cnts, _ = cv2.findContours(thresh.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

    cnts = sorted(cnts, key=cv2.contourArea, reverse=True)
    mask = np.zeros((thresh.shape), np.uint8)
    c = cnts[0]

    clone = image.copy()

    peri = cv2.arcLength(c, closed=True)
    poly = cv2.approxPolyDP(c, epsilon=0.02 * peri, closed=True)

    if len(poly) == 4:
        cv2.drawContours(clone, [poly], -1, (0, 0, 255), 2)

        warped = four_point_transform(image, poly.reshape(-1, 2))


    warped = cv2.cvtColor(warped, cv2.COLOR_BGR2GRAY)
    winX = int(warped.shape[1] / 9.0)
    winY = int(warped.shape[0] / 9.0)

    model = load_model("model.h5")

    labels = []
    centers = []

    predictions = []
    for y in range(0, warped.shape[0], winY):
        for x in range(0, warped.shape[1], winX):

            window = warped[y : y + winY, x : x + winX]

            if window.shape[0] != winY or window.shape[1] != winX:
                continue

            clone = warped.copy()
            digit = cv2.resize(window, (28, 28))
            _, digit2 = cv2.threshold(digit, 120, 255, cv2.THRESH_BINARY_INV)
            digit3 = clear_border(digit2)
            numpixel = cv2.countNonZero(digit3)
            _, digit4 = cv2.threshold(digit3, 0, 255, cv2.THRESH_BINARY_INV)
            if numpixel < 20:
                label = 0
            else:
                _, digit4 = cv2.threshold(digit4, 0, 255, cv2.THRESH_BINARY_INV)
                digit4 = digit4 / 255.0
                array = model.predict(digit4.reshape(1, 28, 28, 1))
                label = np.argmax(array)
            labels.append(label)
            centers.append(((x + x + winX) // 2, (y + y + winY + 6) // 2))

            cv2.rectangle(clone, (x, y), (x + winX, y + winY), (0, 255, 0), 2)


    grid = np.array(labels).reshape(9, 9)

    with open("input","w") as f :
        for r in range(9) : 
            for c in  range(9) : 
                if grid[r][c] == 0: 
                    f.write(".") 
                else : 
                    f.write(str(grid[r][c]))
            f.write("\n")
