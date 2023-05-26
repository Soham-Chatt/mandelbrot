import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error

# Load the data
data = pd.read_csv('data.csv')

# Specify input features and target variable
features = ['Width', 'Height', 'Max_iterations', 'Palette_size']
target = 'Time'

# Split the data into train and test sets
X_train, X_test, y_train, y_test = train_test_split(data[features], data[target], test_size=0.2)

# Initialize and train a linear regression model
model = LinearRegression()
model.fit(X_train, y_train)

# Make predictions with the model
predictions = model.predict(X_test)

# Evaluate the model
mse = mean_squared_error(y_test, predictions)
print('Mean Squared Error:', mse)

new_width = input('Enter width: ')
new_height = input('Enter height: ')
new_max_iterations = input('Enter max iterations: ')
new_palette_size = input('Enter palette size: ')

new_set = pd.DataFrame([[new_width, new_height, new_max_iterations, new_palette_size]], columns=features)
predicted_time = model.predict(new_set)
print('Predicted Time:', round(predicted_time[0]))
