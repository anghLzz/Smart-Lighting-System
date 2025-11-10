
# Smart Lighting System

The "Smart Lighting System" project proposes a modern and efficient solution for indoor lighting automation, based on the ESP32 microcontroller and several complementary sensors.  
The system provides intelligent and adaptive control of light intensity and operation time, contributing to reduced energy consumption and to the creation of a comfortable and sustainable environment.

---

## Overview

The system uses the ESP32 microcontroller to collect data from multiple sensors and control light sources through logic-level MOSFET transistors.  
These components ensure efficient current switching and precise LED brightness adjustment, preventing microcontroller overload.

The main lighting is automatically controlled according to motion detection, ambient light level, and real-time clock, offering a fast and reliable response that adapts to user activity.

---

## Components Used

- ESP32 microcontroller  
- Logic-level MOSFETs (e.g. IRLZ44N) for LED power control  
- PIR sensor (motion detection)  
- KY-018 photoresistor (ambient light detection)  
- KY-038 microphone (sound detection)  
- RTC (Real Time Clock) module  
- White and ambient LEDs  
- Breadboard, jumper wires, PowerBank power supply

---

## Operating Principle

1. **Main Lighting Control**  
   The PIR sensor detects human presence and activates the main light only when necessary.  
   The MOSFET transistor acts as a fast and efficient electronic switch, regulating current to the LEDs.

2. **Automatic Brightness Adjustment**  
   The KY-018 photoresistor measures the ambient light level, allowing the system to adjust LED brightness automatically for optimal visibility and reduced energy usage.

3. **Sound-Based Control**  
   The KY-038 microphone enables the ambient lighting to react to sounds in the room, adding an interactive and dynamic behavior to the system.

4. **Real-Time Synchronization**  
   The RTC module provides accurate timekeeping, enabling scheduled lighting activation and deactivation according to real-world time and day/night cycles.

---

## Advantages

- Reduced energy consumption through intelligent light activation  
- Extended LED lifetime  
- Fully automated and flexible control  
- Expandable system (BLE, Wi-Fi, mobile app integration)

---

## Project Structure

Smart-Lighting-System/
  
  Block Scheme/                
  Code/                
  Images/
  
---

## Author

Bodan Anghel-Dan
Faculty of Electrical Engineering  
Developed as part of the **Academia Innova** competition  
Technical University of Cluj-Napoca
