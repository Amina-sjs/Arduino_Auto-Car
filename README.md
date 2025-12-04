# Tech Fairies — Autonomous Robot

## Description
The robot is built on **Arduino**, equipped with **four motors**, **two line IR sensors**, an **ultrasonic sensor on a servo**, and a **Bluetooth module**.  
It can interact autonomously with its environment and perform various tasks, including line following and obstacle avoidance.

> Full details about assembly, wiring, components, and code are provided in the [Documentation](../Documentation/Documentation.md).

---


![Photo](./Images/перед 2.jpg)


## Main Features

### Line Following
The robot uses **2 line IR sensors** to navigate:  
- **White surface** → moves forward  
- **Black surface** → stops  

### Obstacle Avoidance
The **HC-SR04 ultrasonic sensor** on a servo allows the robot to:  
- detect obstacles  
- stop and move slightly backward if needed  
- scan the area left and right  
- choose a safe direction to continue moving  

### Bluetooth Control
With the **HC-05 module**, the robot can receive the following commands:

| Command | Action      |
|---------|------------|
| F       | Forward    |
| B       | Backward   |
| L       | Turn left  |
| R       | Turn right |
| S       | Stop       |

---

## 3D Model
The complete 3D model of the robot is created in **TinkerCAD**, showing the structure of all components:  

![Photo](./Images/1.jpg) 


[3D Model Tech Fairies](https://www.tinkercad.com/things/fstViYy1P9D/edit?returnTo=%2Fdashboard%2Fcollections%2FeZgqgnvjpSY%2F3d)

---

## Circuit Diagram
The wiring and connections diagram is available in **TinkerCAD**:  

![Photo](./Images/схема.jpg) 


[Circuit Diagram](https://www.tinkercad.com/things/h6YwGCP9HN5-shiny-robo/editel)

---

## Video Demonstration
A demonstration of the robot in action:  
[YouTube](https://youtube.com/shorts/G4Z6CIAt2s8?si=E3beH1C6xB5_kXdD)

---

## Project Purpose
The project demonstrates the integration of **mechanics, electronics, sensors, and programming**.  
The robot performs autonomous movement, responds to obstacles, follows a line, and can be controlled via Bluetooth.  

> Full technical information and implementation details are available in the [Documentation](../Documentation/Documentation.md).