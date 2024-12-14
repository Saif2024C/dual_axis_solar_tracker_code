# **Dual Axis Solar Tracking System**

### **Project Overview**
This project implements a **Dual Axis Solar Tracking System** using:
- **LDRs (Light Dependent Resistors)** to detect light intensity.
- **Servos** for precise solar panel alignment (altitude and azimuth control).
- An **OLED display** to monitor solar panel voltage.

By dynamically tracking the sun's position, the system maximizes the solar panel's exposure to sunlight, thereby improving energy efficiency.

---

## **Features**
- **Real-time Light Detection**: Four LDRs measure light intensity to determine the optimal panel orientation.
- **Dual Axis Control**:
  - **Altitude**: Controls up-down movement.
  - **Azimuth**: Controls left-right movement.
- **Error Tolerance**: Adjustable threshold to minimize unnecessary movements.
- **Voltage Display**: Displays real-time **solar panel voltage** on an OLED screen.
- **Servo Control**: Smooth angle adjustments with configurable step size.

---

## **Components Used**
| **Component**                | **Description**                           |
|------------------------------|-------------------------------------------|
| Arduino Uno                  | Microcontroller board                     |
| LDR (x4)                     | Light Dependent Resistors for sensing     |
| Servo Motors (x2)            | Motors for altitude and azimuth control   |
| Adafruit SSD1306 OLED Screen | 128x64 display to monitor voltage         |
| Jumper Wires                 | For circuit connections                   |
| Solar Panel (optional)       | Source of solar voltage for measurement   |

---

## **Circuit Connections**
### **LDR Sensors**:
| LDR Position      | Arduino Pin |
|-------------------|-------------|
| Top Left          | A0          |
| Top Right         | A1          |
| Bottom Left       | A2          |
| Bottom Right      | A3          |

### **Servo Motors**:
| Servo            | Arduino Pin |
|------------------|-------------|
| Altitude Motor   | 9           |
| Azimuth Motor    | 10          |

### **OLED Display**:
- Connected via **I2C** (Pins: SDA and SCL).
- I2C Address: `0x3C`.

### **Solar Panel Voltage**:
- Connected to Analog Pin `A7`.

---

## **Code Workflow**
1. **Light Intensity Measurement**:
   - Four LDRs measure the light intensity at different positions.
   - Errors (`altitudeError` and `azimuthError`) are calculated based on LDR readings.

2. **Servo Motor Control**:
   - Adjust altitude (up-down) and azimuth (left-right) angles based on error values.
   - Movement step size and angle range are configurable to ensure smooth operation.

3. **Voltage Monitoring**:
   - Reads solar panel voltage via analog pin `A7`.
   - Displays the voltage on the **OLED screen**.

4. **OLED Display**:
   - Shows real-time solar panel voltage with appropriate formatting.

---

## **Code Highlights**
### **LDR Reading and Error Calculation**:
```cpp
avgTop = round(0.5 * (analogRead(topLeft) + analogRead(topRight)));
avgBottom = round(0.5 * (analogRead(bottomLeft) + analogRead(bottomRight)));
altitudeError = avgTop - avgBottom;
```

## **Contributors**
This project was developed by:

- **Raghav Sharma**  
- **Mohammad Saifullah**  

*Final Version Date*: **11 December 2023**

---

## **Contact**
For questions, suggestions, or contributions, feel free to reach out to the contributors.

---


