import numpy as np
from sklearn.datasets import load_iris
from sklearn.linear_model import LinearRegression

print("Loading Iris Data")
iris_raw = load_iris()

#train = iris_raw.data #4 values of "sepal length", "sepal width", "petal length", "petal width" (cm)A
#NOTE: train is ordered in "setosa", "versicolor", and "virginica" evenly. 50 are 'setosa', 50 are the next, etc

print("Begin Training")
lr = LinearRegression()
lr.fit(iris_raw.data, iris_raw.target)

print("Check on results of training")
predictions = lr.predict(iris_raw.data)

corr = 0
for i in range(len(predictions)):
	value = np.floor(predictions[i] + 0.5) #predictions are in floats, return these to normal ints
	if value == iris_raw.target[i]:
		corr += 1

print("Amount correct:", corr, "/ 150 =", corr / 150)
print("\nHyperparameters:")
print("Coefficients:", lr.coef_)
print("Intercept:", lr.intercept_)