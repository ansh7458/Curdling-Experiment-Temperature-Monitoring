#include <math.h>          // For logarithmic and power functions
#include "max6675.h"       // Library for MAX6675 thermocouple module
#include <Oversampling.h>  // For higher resolution ADC readings

// Oversampling ADC object (10-bit ADC, 16x oversampling, 6x averaging)
Oversampling oversampledADC(10, 16, 6);

// MAX6675 thermocouple pin assignments
const int thermoSO  = 4;   // Serial Data Output (DO)
const int thermoCS  = 5;   // Chip Select
const int thermoSCK = 6;   // Serial Clock

// Initialize MAX6675 thermocouple object
MAX6675 thermocouple(thermoSCK, thermoCS, thermoSO);

// Thermistor setup (for surroundings)
const int thermistorPin     = A0;     // Analog pin connected to thermistor
const int pullUpResistor    = 1000;   // Pull-up resistor value (Ω)

// Steinhart–Hart coefficients for NTC 102 thermistor
// (replace with datasheet coefficients if more precise)
const double coeffA = -0.0002860629305;
const double coeffB =  0.0004484292072;
const double coeffC = -0.0000008321267622;

void setup() {
  Serial.begin(9600); 
  Serial.println("Starting temperature logging: Milk (thermocouple avg) + Surroundings (thermistor)");
}

void loop() {
  // === Milk: Thermocouple Averaged Measurement ===
  const int numSamples = 6;        // number of readings for averaging
  double sumCelsius = 0;

  for (int i = 0; i < numSamples; i++) {
    sumCelsius += thermocouple.readCelsius();
  }

  double avgMilkCelsius = sumCelsius / numSamples;  // averaged milk temperature

  // === Surroundings: Thermistor Measurement ===
  long rawADC = oversampledADC.read(thermistorPin);  // Oversampled ADC value
  float voltage = rawADC * (5.0 / 65535.0);          // Convert ADC to voltage

  // Calculate thermistor resistance from voltage divider
  double thermistorResistance = pullUpResistor * ((5.0 - voltage) / voltage);

  // Apply Steinhart–Hart equation
  double temperatureKelvin = 1.0 / (coeffA + coeffB * log(thermistorResistance) +
                                    coeffC * pow(log(thermistorResistance), 3));

  double tempSurroundingsC = temperatureKelvin - 273.15;  // °C

  // === Output Data in CSV format: Surroundings, Milk ===
  Serial.print(tempSurroundingsC, 2); // Column 1: surroundings (thermistor, °C)
  Serial.print(",");
  Serial.println(avgMilkCelsius, 2);  // Column 2: milk (thermocouple avg, °C)

  delay(60000); // 1 minute delay between readings
}
