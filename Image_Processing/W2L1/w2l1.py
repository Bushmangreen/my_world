import cv2
import numpy as np
import tools as tl

img = cv2.imread("cv.png")
vis = img.copy()
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
gray = 255 - gray

blur = cv2.blur(gray, (21,1))

ret_o, th_otsu = cv2.threshold(blur, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

kernel = np.ones((1,15), dtype= np.uint8)
closing = cv2.morphologyEx(th_otsu, cv2.MORPH_CLOSE, kernel)

conts, _ = cv2.findContours(closing, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
cv2.drawContours(vis, conts, -1, (0,255,0), 1)

box_regions = []
h_sum = 0
for c in conts:
	x,y,w,h = cv2.boundingRect(c)
	h_sum += h
	box_regions.append((x,y,w,h))

mean_h = h_sum/float(len(conts))

text_regions = []
for box in box_regions:
	if box[3] > mean_h:
		x,y,w,h = box
		text_regions.append((x,y,x+w,y+h))
		cv2.rectangle(vis, (x,y), (x+w,y+h), (0,0,255), 1)

regions_img = []
for tr in text_regions:
	regions_img.append(img[tr[1]:tr[3],tr[0]:tr[2]])

text_img = tl.concat_ver(regions_img)

row1 = tl.concat_hor((vis, gray, blur))
row2 = tl.concat_hor((th_otsu,closing))
big_image = tl.concat_ver((row1, row2))
scale = 0.5
cv2.imshow("CV", cv2.resize(big_image, (0,0), fx = scale, fy = scale))


cv2.imshow("CV", cv2.resize(text_img, (0,0), fx = scale, fy = scale))

cv2.waitKey(0)