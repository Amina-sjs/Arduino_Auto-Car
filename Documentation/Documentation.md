# **TECH FAIRIES — Project Technical Documentation**

## **1. Overview**
This document provides a **comprehensive technical description** of the autonomous robotic platform **TECH FAIRIES**, including:

- **Hardware components**
- **Mechanical construction**
- **Electrical connections and soldering**
- **Software and required libraries**
- **Operational modes**: Line Following, Bluetooth Control, and Obstacle Avoidance

This documentation is intended for **replication, analysis, and modification** of the project.

---

## **2. Hardware Components**

### **2.1 Electronic Components**
- **Microcontroller:** Arduino UNO / MEGA  
- **Motor Driver:** Adafruit Motor Shield V1  
- **Motors:** 4 × DC geared motors  
- **Distance Sensor:** HC-SR04 ultrasonic sensor  
- **Servo Motor:** SG90 for rotating the ultrasonic sensor  
- **Line Sensors:** Left and Right IR sensors  
- **Bluetooth Module:** HC-05 (optional)  
- **Power Supply:** Rechargeable battery ≥ **8 V** (AA type)  
- **Wires:** Male-to-female connector wires  
- **Soldering:** For reliable connections of motors and sensors  

### **2.2 Mechanical Construction**
- **Chassis:** Wooden frame  
- **Wheels:** 4 units connected to DC motors  
- **Ultrasonic Sensor Holder:** Mounted on the servo without glue  
- **Motor Mounts:** Fixed attachments for motors and wheels  

> **All electrical connections** are made using **male-to-female wires** and **soldering** to ensure reliable operation.

---

## **3. Wiring Diagrams (ASCII)**

### **3.1 HC-SR04 Ultrasonic Sensor**

```
             +--------------------+
             |    HC-SR04         |
             |                    |
Arduino A1 ----> TRIG             |
Arduino A0 ----> ECHO             |
5V ------------> VCC              |
GND -----------> GND              |
             +--------------------+

```

### **3.2 Servo Motor**

```
             +----------------------+
             |        SERVO         |
             |                      |
D10 -------------> Signal           |
5V --------------> +5V              |
GND -------------> GND              |
             +----------------------+

```

### **3.3 Line IR Sensors**

```
        +----------------+
        | Left IR sensor |
        +----------------+

Signal  ---> A2
VCC     ---> 5V
GND     ---> GND

```

```
        +-----------------+
        | Right IR sensor |
        +-----------------+


Signal  ---> A3
VCC     ---> 5V
GND     ---> GND

```

```
### **3.4 Bluetooth Module HC-05 (optional)**
```

```
        +--------------------+
        |      HC-05         |
        +--------------------+

TX ----> Arduino RX (0)
RX ----> Arduino TX (1)
VCC ---> 5V
GND ---> GND

```
```
### **3.5 Motors via Adafruit Motor Shield**
```

Adafruit Motor Shield (V1)

```
       +--------------------------------------+
       |                                      |
M1 --=-----> Motor 1 (Front Left)             |
M2 --------> Motor 2 (Front Right)            |
M3 --------> Motor 3 (Rear Left)              |
M4 --------> Motor 4 (Rear Right)             |
       |                                      |
       +--------------------------------------+

---

## **4. Software and Libraries**
- **Servo.h** — for controlling the servo motor  
- **AFMotor.h** — for controlling motors via Adafruit Motor Shield  

**Library Installation:**  
Arduino IDE → *Sketch → Include Library → Manage Libraries*

---

## **5. Code Structure and Operational Modes**

### **5.1 Line Following**
> **Note:** The robot moves **on white surface**, and stops when black is detected.

- Left IR sensor → A2  
- Right IR sensor → A3  
- **White surface:** Move forward  
- **Black surface:** Stop  

### **5.2 Bluetooth Control**
| **Command** | **Action** |
|-------------|------------|
| F           | Forward    |
| B           | Backward   |
| L           | Turn Left  |
| R           | Turn Right |
| S           | Stop       |

### **5.3 Obstacle Avoidance**
- Measures distance using the ultrasonic sensor  
- If distance ≤ 12 cm → **Stop** and move slightly backward  
- Servo rotates to scan left and right  
- Chooses the direction with **maximum free distance**

---

## **6. Power Requirements**
- **Motors:** Rechargeable battery ≥ **8 V
- **Arduino:** USB / 5 V  
- **All grounds (GND)** must be connected

> Previous batteries did not provide sufficient power for motors, thus **8 V minimum** is required.

---

## **7. Recommendations and Future Improvements**
- Implement **PID control** for line following  
- Optimize **chassis and cable management**  
- Add additional **sensors or camera module**  
- Integrate **ESP32** with Wi-Fi for remote control

---

