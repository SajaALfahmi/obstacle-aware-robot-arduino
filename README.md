# obstacle-aware-robot-arduino 

This project is a motion-control system built with Arduino that combines:
- **4 DC motors** (controlled via L293D motor drivers)
- **1 Servo motor**
- **Ultrasonic sensor** for obstacle detection

It executes a pre-defined sequence of motor movements and reacts intelligently to obstacles detected within **10 cm**.

---

## 🎯 Objectives

- Move forward for **30 seconds**
- Move backward for **60 seconds**
- Alternate between right and left for **60 seconds**
- Continuously rotate the servo motor between 45° and 135°
- **If an obstacle is detected** within 10 cm:
  - Stop all motors momentarily
  - Change the servo direction
  - Move backward briefly before resuming

---

## 🧩 Components Used

- Arduino Uno
- L293D motor driver (x2)
- 4 DC motors
- Servo motor 
- Ultrasonic sensor (HC-SR04)
- 9V Batteries
- Breadboard and jumper wires

---

## 🔁 Behavior Summary

| Condition          | Action                                   |
|--------------------|-------------------------------------------|
| Normal operation   | Motors follow the timed sequence         |
| Servo behavior     | Sweeps between 45° and 135° continuously |
| Obstacle ≤ 10 cm   | Motors stop, servo changes direction, bot moves back |

---

## 📂 Files

- `main.ino` → Arduino source code for motor + sensor + servo control
- `arduino-obstacle-avoidance-simulation.MOV` → Demonstration video of project behavior
- `README.md` → Project overview (this file)

---

## 📷 Demo

🎥 Watch the full simulation in [`arduino-obstacle-avoidance-simulation.mp4`](./arduino-obstacle-avoidance-simulation.MOV)

---

## 📎 Notes

- Timing is managed via `millis()` and `delay()`.
- Servo runs independently from obstacle detection for dynamic feedback.
- Designed to simulate smart motion redirection when facing real-world obstacles.
