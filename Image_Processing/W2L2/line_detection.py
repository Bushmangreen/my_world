import cv2 
import numpy as np

img = cv2.imread("test.png")

edges = cv2.Canny(img, 50, 50, apertureSize = 3)
lines = cv2.HoughLines(edges, 1, np.pi/180, 400)

for line in lines:
	for rho, theta in line:
		a = np.cos(theta)
		b = np.sin(theta)
		x0 = a * rho
		y0 = b * rho
		x1 = int(x0 + 10000 * (-b))
		y1 = int(y0 + 10000 * (a))
		x2 = int(x0 - 10000 * (-b))
		y2 = int(y0 - 10000 * (a))
		cv2.line(img, (x1,y1), (x2,y2),(0,0,255),2)
scale = 0.2
cv2.imshow("Window", cv2.resize(img,(0,0),fx = scale, fy= scale))
cv2.waitKey(0)