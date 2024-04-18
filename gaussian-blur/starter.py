import matplotlib.pyplot as plt
import numpy as np
import math
from PIL import Image

def gaussian(x, y, sigma=1):
    a = 1 / (2 * math.pi * sigma ** 2)
    b = math.exp(-(x**2 + y**2)/(2*sigma**2))
    return a * b

def blurfilter(in_img, out_img):
    """ For each pixel in in_img calc the mean intensity values
    using square 7x7 stencil"""
    for c in range(3):
        for x in range(in_img.shape[1]):
            for y in range(in_img.shape[0]):
                val = 0
                for i in range(-3,4):
                    for j in range(-3,4):
                        if (x+i < img.shape[1]) and (x+i >= 0) and \
                            (y+j < img.shape[0] ) and (y+j >=0 ):
                                val += (int(img[y+j,x+i,c] )) * gaussian(i, j)
                out_img[y,x,c] = val // 49

img = np.array(Image.open('noisy1.jpg'))
print(img.shape)
imgblur= img.copy()
blurfilter(img, imgblur)
# Display and save blurred image
fig = plt.figure()
ax = fig.add_subplot(1, 2, 1)
imgplot = plt.imshow(img)
ax.set_title('Before')
ax = fig.add_subplot(1, 2, 2)
imgplot = plt.imshow(imgblur)
ax.set_title('After')
img2= Image.fromarray(imgblur)
img2.save("blurred.jpg")