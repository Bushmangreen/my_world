import cv2
import numpy as np

# img = cv2.imread("small.png")

# print(img.shape)

# print(img[0:5,0:5,0])
# cv2.imshow("Window", img)
# k = cv2.waitKey(0)

# square = 255 * np.ones((50,50,3))
# square[20:30,20:30,:] = 0 
# square = np.full((50,50),255, dtype= np.uint8)

car = cv2.imread("car.jpg")
gray = 0.114 * car[...,0] + 0.299 * car[...,1] + 0.587 * car[...,2]
gray = np.asarray(gray, dtype= np.uint8)

#********************************ALWAYS USED***********************
gray = cv2.cvtColor(car, cv2.COLOR_BGR2GRAY) 
#********************************ALWAYS USED***********************
kernel = np.ones((5,5), dtype= np.float64)/25
# blur = cv2.filter2D(gray, -1, kernel)
blur = cv2.GaussianBlur(gray, (25,25), 4)
cv2.imshow("GRAY", gray)
cv2.imshow("BLUR", blur)
cv2.waitKey(0)