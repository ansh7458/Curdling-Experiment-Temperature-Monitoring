#include <math.h>          // For logarithmic and power functions
#include "max6675.h"       // Library for MAX6675 thermocouple module
#include <Oversampling.h>  // For higher resolution ADC readings

// Create oversampling ADC object (10-bit base, 16x oversampling, 4x averaging)
Oversampling oversampledADC(10, 16, 4);

// MAX6675 thermocouple pin assignments
const int thermoSO  = 4;   // Serial Data Output (DO)
const int thermoCS  = 5;   // Chip Select
const int thermoSCK = 6;   // Serial Clock

// Initialize MAX6675 thermocouple object
MAX6675 thermocouple(thermoSCK, thermoCS, thermoSO);

// Thermistor setup (for surroundings)
const int thermistorPin     = A0;     // Analog pin connected to thermistor
const int pullUpResistor    = 10000;  // Pull-up resistor value (Ω)

// Steinhart–Hart coefficients for 10k NTC thermistor
// (replace with datasheet values for your thermistor if different)
const double coeffA = 1.2751e-03;
const double coeffB = 2.3781e-04;
const double coeffC = 8.6537e-08;

void setup() {
  Serial.begin(9600); 
  Serial.println("Starting temperature logging: Milk (thermocouple) + Surroundings (thermistor)");
}

void loop() {
  // === Surroundings: Thermistor Measurement ===
  long rawADC = oversampledADC.read(thermistorPin);   // Oversampled ADC reading
  float voltage = rawADC * (5.0 / 65535.0);           // Convert ADC to voltage
  double thermistorResistance = pullUpResistor * ((5.0 - voltage) / voltage);

  // Apply Steinhart–Hart equation
  double temperatureKelvin = 1.0 / (coeffA + coeffB * log(thermistorResistance) +
                                    coeffC * pow(log(thermistorResistance), 3));

  double tempSurroundingsC = temperatureKelvin - 273.15; // °C

  // === Milk: Thermocouple Measurement ===
  double tempMilkC = thermocouple.readCelsius(); // °C

  // === Output Data in CSV format: Surroundings, Milk ===
  Serial.print(tempSurroundingsC, 2);  // Column 1: surroundings (thermistor)
  Serial.print(",");
  Serial.println(tempMilkC, 2);        // Column 2: milk (thermocouple)

  delay(1000); // 1 minute  delay between readings
}
