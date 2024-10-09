import numpy as np
import matplotlib.pyplot as plt
import os

points = np.loadtxt("values.dat", delimiter=',', max_rows=len(list(open("./values.dat"))))
centre=np.array([points[0][0],points[0][1]])
xp = points[:1000, 0]
yp = points[:1000, 1]
xc = points[-1000:,0]
yc = points[-1000:,1]
plt.figure()
plt.plot(xp, yp, label='y^2=4x', color='blue')
plt.plot(xc, yc, label='x^2+y^2=8x', color='red')
plt.gca().set_aspect('equal', adjustable='box')
plt.xlabel("x")
plt.ylabel("y")
plt.grid(True)
plt.savefig('/home/gvt1/Documents/sdcard/github/EE1030/Assignment5/figs/fig.png')
plt.show()
