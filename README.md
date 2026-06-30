# HomeBoy

A temperature monitoring system built for MCD1160 (Assignment 1), using Arduino.

## What it does

- Reads an analog temperature sensor and calculates Celsius, Fahrenheit, and Kelvin
- Displays live readings on an LCD
- RGB LED shifts colour based on temperature range: blue when cold, green when in the normal 20-30°C range, red when hot
- Buzzer alerts when temperature drops below 10°C or rises above 35°C
- Button-triggered serial menu to view readings in a specific unit or see running averages across all readings taken so far

## Hardware

- Arduino board
- Analog temperature sensor
- 16x2 LCD
- RGB LED (common cathode)
- Push button
- Buzzer

## Notes

Team assignment for a university electronics unit. Wrote the full firmware solo; a teammate handled the physical circuit build.
