import numpy as np
import matplotlib.pyplot as plt
import padasip as pa

A = np.loadtxt('hardware.txt')
X = np.hstack((np.ones((A.shape[0],1)),A[:,[1]],A[:,[1]]**2))
T = A[:,[1]]
C = A[:,[0]]

#Least squares method
v, av, bv = np.linalg.lstsq(X, C, rcond=None)[0]
n_lsq = np.zeros((3,1))
n_lsq[0][0] = v
n_lsq[1][0] = av
n_lsq[2][0] = bv
print(n_lsq)

#Plot both the results
plt.plot(T, X@n_lsq)
plt.plot(T, C, 'k.')
plt.grid()
plt.ylabel('Output Voltage (V)')
plt.xlabel('Temperature ($^{\circ}$C)')
plt.tight_layout()
plt.savefig('train.png')

#Close current figure(s)
plt.close('all')

#Plot for validation
B = np.loadtxt('hardwaretest.txt')
Xv = np.hstack((np.ones((B.shape[0],1)),B[:,[1]],B[:,[1]]**2))
Cv = B[:,[0]]
Tv = B[:,[1]]
plt.plot(T, X@n_lsq)
plt.plot(Tv, Cv, 'k.')
plt.ylabel('Output Voltage (V)')
plt.xlabel('Temperature ($^{\circ}$C)')
plt.grid()
plt.tight_layout()
plt.savefig('valid.png')
