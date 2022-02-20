def ReLU(x):
	if x>0:
		return x
	else :
		return 0

print(ReLU(-2))
print(ReLU(4))

import numpy as np
import matplotlib.pylab as plt

def ReLU(x):
	return np.maximum(0,x)

x = np.arange(-5,5,1)
y = ReLU(x)

plt.plot(x,y)
plt.ylim(-1, 5)
plt.show()