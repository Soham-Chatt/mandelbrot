import pandas as pd
import numpy as np
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt

file_name = 'processing.txt'

# Load your data
with open(file_name, 'r') as f:
    lines = f.readlines()

data = {
    'Processing': [],
    'Time': []
}

for line in lines:
    processing, time = line.strip().split('Running for')
    processing = processing.replace('Processing:', '').replace('%', '').strip()
    time = time.replace('seconds.', '').strip()

    data['Processing'].append(float(processing))
    data['Time'].append(int(time))

df = pd.DataFrame(data)

# Train a linear regression model
model = LinearRegression()
model.fit(df['Processing'].values.reshape(-1, 1), df['Time'])

# Make prediction
x = np.array([0, 100]).reshape(-1, 1)
y = model.predict(x)

# Plot the data and the linear regression model
plt.scatter(df['Processing'], df['Time'])
plt.plot(x, y, color='red')
plt.xlabel('Processing (%)')
plt.ylabel('Time (seconds)')
plt.title('Prediction of Total Processing Time')
# plt.show()

# Estimate when 100% will be reached
print('Estimated time for 100% processing: ', round(y[1]), ' seconds')
