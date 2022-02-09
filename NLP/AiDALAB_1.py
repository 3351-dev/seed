import numpy as np
from tensorflow import keras
from tensorflow.keras import optimizers
from tensorflow.keras.layers import Dense, Input

model = keras.Sequential()
model.add(Input(1))
model.add(Dense(10, activation='tanh'))
model.add(Dense(10, activation='tanh'))
model.add(Dense(1))

model.compile(optimizer="SGD", loss="mse")

x=np.arange(-1,1,0.01)
y = x **2

model.fit(x,y, epochs=1000, verbose=0, batch_size=20)

result_y = model.predict(x)