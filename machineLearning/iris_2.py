#iris_2.py

from sklearn import datasets
from sklearn.neighbors import KNeighborsClassifier
import numpy as np

dataset = datasets.load_iris()
X, y = dataset['data'],dataset['target']

model = KNeighborsClassifier(n_neighbors=5)
model.fit(X,y)

y_predicted = model.predict(X)

print('model\n{labels}'.format(labels=y_predicted))
print('real\n{labels}'.format(labels=y))

score = np.mean(y_predicted == y)
print(score)
print('{:.3f}'.format(score))