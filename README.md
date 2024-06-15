# 🥛 Curdling Experiment — Temperature Monitoring

<p align="center">
  <img src="https://img.shields.io/badge/Platform-Arduino-00979D?style=for-the-badge&logo=arduino" />
  <img src="https://img.shields.io/badge/Language-Python-3776AB?style=for-the-badge&logo=python" />
  <img src="https://img.shields.io/badge/Sensor-MAX6675-red?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Sensor-NTC_Thermistor-orange?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Institute-NSUT-blue?style=for-the-badge" />
</p>

> **Centre for Electronic Design and Technology**  
> Netaji Subhas University of Technology, New Delhi  
> *Date: June 2024*

---

## 📋 Table of Contents
- [Synopsis](#-synopsis)
- [Introduction](#-introduction)
- [Procedure](#-procedure)
- [Results](#-results)
- [Conclusion](#-conclusion)
- [Bill of Materials](#-bill-of-materials)

---

## 🎯 Synopsis

This experiment aimed to monitor the **temperature profile of milk during the curdling process** to test the hypothesis that curdling is an **endothermic reaction**. The setup involved placing milk in a sealed earthen pot, insulating it in a thermocol box, and monitoring temperature overnight using three different sensor configurations. Data was logged via Arduino and analyzed in Python. The observed cooling trends suggested that the curdling process **absorbs heat** from the system.

## 📖 Introduction

Curdling of milk is a biochemical transformation where lactose is fermented into lactic acid, causing casein proteins to coagulate. This process is of interest in food science and thermodynamics, as it is suspected to be endothermic. Monitoring temperature over time provides an indirect way to study the energetics of the process.

## ⚙️ Procedure

1. Milk poured into a **sealed earthen pot**
2. Pot placed in a **thermocol box** for thermal isolation
3. Three sensor configurations tested:
   - Thermistor in ambient air (baseline)
   - Thermistor inside thermocol box with air gap
   - MAX6675 thermocouple inside box near the milk
4. Temperature logged **overnight** via Arduino
5. Data analyzed in Python

## 📊 Results

### Thermistor in Open Air
Showed temperature fluctuations following room environment — baseline for comparison.

### Thermistor Inside Enclosure
Smoother temperature variation with reduced external noise, indicating effective insulation.

### Thermocouple Inside Enclosure
Recorded actual thermal behavior during curdling. A slight **dip in temperature** was observed, suggesting heat absorption consistent with an endothermic process.

## ✅ Conclusion

The experiment provided qualitative evidence suggesting curdling is an **endothermic process**. The sealed earthen pot showed a slight drop in temperature during the curdling period. For more accurate results, a pH sensor should be integrated to detect the chemical transition directly.

## 📦 Bill of Materials

| S.No | Component | Value | Qty |
|------|-----------|-------|-----|
| 1 | Arduino Uno | — | 1 |
| 2 | Thermocouple (MAX6675) | K-type | 1 |
| 3 | NTC Thermistor | 10 kΩ | 1 |
| 4 | Resistor | 10 kΩ | 1 |
| 5 | Earthen Pot | 500 ml | 1 |
| 6 | Thermocol Box | — | 1 |

## 🛠️ Technologies Used

`Arduino` · `Python` · `MAX6675` · `NTC Thermistor` · `CoolTerm` · `Matplotlib`

## 👥 Authors
- **Ansh Gupta** — NSUT, New Delhi
- **Shubham Kumar** — NSUT, New Delhi

---
*Centre for Electronic Design and Technology, NSUT, New Delhi*
