import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# --- Exponential Moving Average function ---
def exponential_moving_average(data, alpha):
    ema = np.zeros_like(data)
    ema[0] = data[0]  # start with the first value
    for t in range(1, len(data)):
        ema[t] = alpha * data[t] + (1 - alpha) * ema[t - 1]
    return ema

# --- Enter CSV file name ---
file_name = "Curdling_Experiment_1.csv"#Enter the CSV file name (e.g., Curdling_Experiment_1.csv)

# --- Load CSV file ---
data = pd.read_csv(file_name)

# --- Extract columns ---
time = data['Time'].values
milk_temp = data['Milk Temp'].values
surr_temp = data['Surrounding Temp'].values

# --- Apply EMA smoothing ---
alpha = 0.05
smoothed_milk = exponential_moving_average(milk_temp, alpha)
smoothed_surr = exponential_moving_average(surr_temp, alpha)

# --- Plot results ---
plt.figure(figsize=(10, 6))
plt.plot(time, smoothed_milk, label='Milk Temperature', color="red", linewidth=5)
plt.plot(time, smoothed_surr, label='Surroundings Temperature', color="blue", linewidth=5)

plt.xlabel('Time (s)')
plt.ylabel('Temperature (°C)')
plt.title(f"Temperature VS Time)")
plt.legend()
plt.grid(True)
plt.show()
