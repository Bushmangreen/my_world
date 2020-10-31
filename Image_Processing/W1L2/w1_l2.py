import cv2
import numpy as np
import tools as tl

# img = cv2.imread("sudoku.png",0)

# ret, th = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)
# th_gauss = cv2.adaptiveThreshold(img, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 3, 2)
# th_adap11 = cv2.adaptiveThreshold(img, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 2)

# ret_o, th_o = cv2.threshold(img, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)


# row1 = tl.concat_hor((img,th,th_o))
# row2 = tl.concat_hor((img, th_adap11, th_gauss))
# cv2.imshow("sudoku", tl.concat_ver((row1,row2)))

# cv2.waitKey(0)

img = cv2.imread("morphology2.png")

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

ret, th = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

kernel = np.ones((5,5), dtype = np.uint8)

# erosion = cv2.erode(th, kernel, iterations = 1)
# dialation = cv2.dilate(erosion, kernel, iterations = 1)

closing = cv2.morphologyEx(th, cv2.MORPH_OPEN, kernel, iterations = 2)

contours, hier = cv2.findContours(closing, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)



vis = cv2.cvtColor(closing, cv2.COLOR_GRAY2BGR)
# cv2.drawContours(vis, contours, -1, (0,255,0), 2)

max_x = -100
max_y = -100
min_x = 100
min_y = 100
for cnt in contours:
	x,y,w,h = cv2.boundingRect(cnt)
	if (x > max_x):
		max_x = x + w
	if (y > max_y):
		max_y = y + h
	if (x < min_x):
		min_x = x
	if (y < min_y):
		min_y = y 
			
cv2.rectangle(vis, (min_x,min_y), (max_x,max_y), (0,0,255), 1)

final_img = tl.concat_ver((img, th, vis ))
scale = 0.5

cv2.imshow("sudoku", cv2.resize(final_img,(0,0), fx = scale, fy = scale))

cv2.waitKey(0)