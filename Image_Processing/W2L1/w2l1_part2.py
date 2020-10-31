import cv2
import numpy as np
import tools as tl

img = cv2.imread("cv.png")
vis = img.copy()

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
gray = 255 - gray

verp = np.sum(gray, axis = 1)/255

verp_vis = tl.getDrawProjectionVer(vis, verp)

big_image = tl.concat_hor((vis, verp_vis))

scale = 0.5
cv2.imshow("CV", cv2.resize(big_image, (0,0), fx = scale, fy = scale))


cv2.waitKey(0)