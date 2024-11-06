import numpy as np
import matplotlib.pyplot as plt
import os
points = np.loadtxt("values.dat", delimiter=',', max_rows=len(list(open("./values.dat"))))
centre=np.array([points[0][0],points[0][1]])
xp = points[:2002, 0]
yp = points[:2002, 1]
xc = points[-2002:,0]
yc = points[-2002:,1]
plt.figure()
plt.plot(xp, yp, label='y^2=4x', color='blue')
plt.plot(xc, yc, label='x^2+y^2=8x', color='red')
plt.gca().set_aspect('equal', adjustable='box')
plt.fill_between(xc, yp, yc, where = (yc>0)&(yp>0)&(xc<4), color='green', alpha=0.5)
plt.xlabel("x")
plt.ylabel("y")
plt.grid(True)
plt.savefig('path/to/figs/fig.png')
plt.show()
