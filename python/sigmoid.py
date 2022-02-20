import numpy as np
import matplotlib.pylab as plt

def sigmoid(x):
	return 1/(1+np.exp(-x))

x = np.array([1.0,2.0])
print(sigmoid(x))


x = np.arange(-5,5,0.1)	# -5부터 5까지 0.1 간격으로 x에 담아라
y = sigmoid(x)

plt.plot(x,y)
plt.ylim(-0.1, 1.1)
plt.show()