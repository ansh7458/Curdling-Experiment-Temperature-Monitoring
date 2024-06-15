#include <math.h>
#include "max6675.h"

// --- Pin Assignments ---
// Milk thermocouple (sensor 1)
const int milkSO  = 5;   // Serial Out
const int milkCS  = 6;   // Chip Select
const int milkSCK = 7;   // Serial Clock

// Surroundings thermocouple (sensor 2)
const int surrSO  = 2;   // Serial Out
const int surrCS  = 3;   // Chip Select
const int surrSCK = 4;   // Serial Clock

// --- Thermocouple Objects ---
MAX6675 milkThermocouple(milkSCK, milkCS, milkSO);
MAX6675 surrThermocouple(surrSCK, surrCS, surrSO);

// --- Moving Average Configuration ---
const int numSamples = 8;       // number of samples for smoothing

// Arrays to store recent readings
float milkReadings[numSamples];
float surrReadings[numSamples];

// Index trackers
int milkIndex = 0;
int surrIndex = 0;

// Totals for rolling sums
float milkTotal = 0;
float surrTotal = 0;

// Moving averages
float milkAvg = 0;
float surrAvg = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("MAX6675 - Dual Sensor Logging");
  Serial.println("Milk Temp, Milk Avg, Surroundings Temp, Surroundings Avg");

  // Initialize readings arrays with initial values
  for (int i = 0; i < numSamples; i++) {
    milkReadings[i] = milkThermocouple.readCelsius();
    milkTotal += milkReadings[i];

    surrReadings[i] = surrThermocouple.readCelsius();
    surrTotal += surrReadings[i];
  }

  // Calculate initial averages
  milkAvg = milkTotal / numSamples;
  surrAvg = surrTotal / numSamples;
}

void loop() {
  // --- Current Readings ---
  float milkTemp = milkThermocouple.readCelsius();
  float surrTemp = surrThermocouple.readCelsius();

  // --- Update Milk Moving Average ---
  milkTotal = milkTotal - milkReadings[milkIndex] + milkTemp;
  milkReadings[milkIndex] = milkTemp;
  milkIndex = (milkIndex + 1) % numSamples;
  milkAvg = milkTotal / numSamples;

  // --- Update Surroundings Moving Average ---
  surrTotal = surrTotal - surrReadings[surrIndex] + surrTemp;
  surrReadings[surrIndex] = surrTemp;
  surrIndex = (surrIndex + 1) % numSamples;
  surrAvg = surrTotal / numSamples;

  // --- Serial Output (CSV format) ---
  Serial.print(milkAvg, 2);   Serial.print(", ");
  Serial.println(surrAvg, 2);

  // --- Delay ---
  // 300000 ms = 5 minute between readings
  delay(300000);
}
