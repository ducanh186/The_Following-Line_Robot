# Line Following Robot

## Project Overview
**Project:** Line Following Robot  
**Framework:** ArduinoIDE  
**Platform:** ESP32  

## Description
- This project uses 8 LDR sensors to detect the line on the ground.
- White color LEDs are used to detect the black line.
- The robot will follow the line based on the sensor data.
- The robot will stop when all sensors do not detect the line.

## Connection
- LDR sensors are connected to GPIO pins as defined in the code.
- Motors are connected to GPIO pins as defined in the code.

## Algorithm
- The robot will move straight if both center sensors detect the line.
- The robot will turn left if the left sensors detect the line.
- The robot will turn right if the right sensors detect the line.
- The robot will stop if all sensors do not detect the line.

## How to Calculate the Threshold Value
- The threshold value is the average value of the ADC readings when the sensor detects the line.
- The threshold value is used to compare with the current ADC readings to determine if the sensor detects the line.

## Notes
- The threshold values are set based on the environment and the line color.
- The base speed and the adjustment factor are set based on the robot's performance.
- The robot may need to adjust the threshold values, the base speed, and the adjustment factor to follow the line correctly.

## Version
**Current Version:** 1.0

## Features
- Read ADC values from 8 LDR sensors.
- Detect the line based on the threshold values.
- Control the robot to follow the line.
- Stop the robot when all sensors do not detect the line.

## Upcoming Upgrades
- Add PID control for better line following.
- Add obstacle avoidance feature.
- Add Bluetooth, Wi-Fi control for remote operation.
# Line Following Robot

## Project Overview
**Project:** Line Following Robot  
**Framework:** ArduinoIDE  
**Platform:** ESP32  

## Description
- This project uses 8 LDR sensors to detect the line on the ground.
- Cảm biến hồng ngoại are used to detect the line of different colors.
- The robot will follow the line based on the sensor data.
- The robot will stop when all sensors do not detect the line.

## Connection
- LDR sensors are connected to GPIO pins as defined in the code.
- Motors are connected to GPIO pins as defined in the code.

## Algorithm
- The robot will move straight if both center sensors detect the line.
- The robot will turn left if the left sensors detect the line.
- The robot will turn right if the right sensors detect the line.
- The robot will stop if all sensors do not detect the line.

## How to Calculate the Threshold Value
- The threshold value is the average value of the ADC readings when the sensor detects the line.
- The threshold value is used to compare with the current ADC readings to determine if the sensor detects the line.

## Notes
- The threshold values are set based on the environment and the line color.
- The base speed and the adjustment factor are set based on the robot's performance.
- The robot may need to adjust the threshold values, the base speed, and the adjustment factor to follow the line correctly.

## Version
**Current Version:** 1.0

## Features
- Read ADC values from 8 LDR sensors.
- Detect the line based on the threshold values.
- Control the robot to follow the line.
- Stop the robot when all sensors do not detect the line.

## Upcoming Upgrades
- Add PID control for better line following.
- Add obstacle avoidance feature.
- Add Bluetooth, Wi-Fi control for remote operation.
**Schematics and PCB layout will be updated soon.**

**Schematics and PCB layout will be updated soon.**