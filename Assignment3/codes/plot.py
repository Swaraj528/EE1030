#Code by GVV Sharma
#July 22, 2024
#released under GNU GPL
#Line 


import sys                                          #for path to external scripts
sys.path.insert(0, '/home/gvt/Documents/sdcard/github/matgeo/codes/CoordGeo')        #path to my scripts
import numpy as np
import mpmath as mp
import numpy.linalg as LA
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

#local imports
from line.funcs import *
from triangle.funcs import *
from conics.funcs import circ_gen


data = np.loadtxt("values.dat", skiprows=1)  # Skip the header row

xp = data[0]
yp = data[1]
xq = data[2]
yq = data[3]
xa = data[4]
ya = data[5]
xb = data[6]
yb = data[7]
#Given points
A = np.array(([xa, ya])).reshape(-1,1) 
B = np.array(([xb, yb])).reshape(-1,1) 
P = np.array(([xp, yp])).reshape(-1,1) 
Q = np.array(([xq, yq])).reshape(-1,1)

x_AB = line_gen(A,B)

plt.plot(x_AB[0,:],x_AB[1,:],label='$distance(AB)$')

colors = np.arange(1,5)
#Labeling the coordinates
quad_coords = np.block([A,B,P,Q])
plt.scatter(quad_coords[0,:], quad_coords[1,:], c=colors)
vert_labels = ['A','B','P','Q']
for i, txt in enumerate(vert_labels):
    plt.annotate(f'{txt}\n({quad_coords[0,i]:.2f}, {quad_coords[1,i]:.2f})',
                 (quad_coords[0,i], quad_coords[1,i]), # this is the point to label
                 textcoords="offset points", # how to position the text
                 xytext=(10,-30), # distance from text to points (x,y)
                 ha='center') # horizontal alignment can be left, right or center

# use set_position
ax = plt.gca()
ax.spines['top'].set_color('none')
ax.spines['left'].set_position('zero')
ax.spines['right'].set_color('none')
ax.spines['bottom'].set_position('zero')
'''
ax.spines['left'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.spines['top'].set_visible(False)
ax.spines['bottom'].set_visible(False)
plt.xlabel('$x$')
plt.ylabel('$y$')
plt.legend(loc='best')
'''
plt.xlabel('X-Axis')
plt.ylabel('Y-Axis')
plt.title('Finding the points of trisection of A and B', loc = 'right', pad = 15)
plt.grid() # minor
plt.axis('equal')
plt.savefig('/home/gvt/Documents/sdcard/github/EE1030/Assignment3/figs/fig1.png')
plt.show()
