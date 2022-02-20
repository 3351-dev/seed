import numpy as np

def softmaxFunction(x):
	expX = np.exp(x)
	sumExpX = np.sum(expX)
	return expX / sumExpX

a = np.array([2.3, -0.9, 3.6])
y4 = softmaxFunction(a)
print('#1')
print(y4, np.sum(y4))

'''
a = np.array([900, 1000, 1000])
y4 =softmaxFunction(a)
print('#2')
print(y4, np.sum(y4))
'''
# 지수함수를 사용하기에 계산 결과가 너무 크면 오버플로문제를 야기함

def softmaxFunc(x):
	expX = np.exp(x - np.max(x))
	sumExpX = np.sum(expX)
	return expX/sumExpX

a = np.array([900, 1000, 1000])
y4 =softmaxFunc(a)
print('#2')
print(y4, np.sum(y4))
# 다음과 같이 수정해줘야한다.