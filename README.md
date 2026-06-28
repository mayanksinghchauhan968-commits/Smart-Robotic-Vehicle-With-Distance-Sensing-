# Smart Robotic Vehicle With Distance Sensing

A 4-wheel-drive robotic vehicle built with Arduino, featuring Bluetooth control, autonomous obstacle avoidance, and voice control — all switchable depending on how you want to drive it.

## How It Works

The car is driven by 4 DC motors via an Adafruit Motor Shield (AFMotor library). It supports three control modes:

- **Bluetooth control** — drive manually using a mobile Bluetooth app, sending single-character commands over Serial
- **Autonomous obstacle avoidance** — a servo-mounted ultrasonic sensor (HC-SR04) continuously scans ahead; when an obstacle is detected within 12cm, the car reverses, checks both left and right distances, and automatically turns toward the clearer path
- **Voice control** — accepts symbolic voice-to-text commands relayed over Serial from a voice-to-text mobile app, letting you steer the car hands-free

## Features

- Manual Bluetooth driving (forward, backward, left, right, stop)
- Real-time ultrasonic distance sensing with servo sweep (left/right scanning)
- Fully autonomous obstacle avoidance — detects obstacles and re-routes automatically
- Voice-controlled driving via symbolic commands (`^` `-` `<` `>` `*`)
- Smooth integration between all three control modes

## Hardware Used

- Arduino Uno (or compatible)
- Adafruit Motor Shield (L293D-based, AFMotor library)
- 4x DC Motors
- HC-SR04 Ultrasonic Distance Sensor
- SG90 (or similar) Servo Motor
- HC-05 Bluetooth Module
- Chassis + wheels + battery pack

## Circuit Diagram

<table>
  <tr>
    <td><img src="images/circuit-1.png" width="250"></td>
    <td><img src="images/circuit-2.png" width="250"></td>
  </tr>
</table>

## Software / Libraries

- `Servo.h`
- `AFMotor.h`

Install `AFMotor` via the Arduino Library Manager (or Adafruit's GitHub) before compiling.

## Bluetooth Command Reference

| Command | Action |
|---|---|
| `F` | Move forward |
| `B` | Move backward |
| `L` | Turn left |
| `R` | Turn right |
| `S` | Stop |

## Voice Command Reference

| Command | Action |
|---|---|
| `^` | Move forward |
| `-` | Move backward |
| `<` | Turn left (if clear) |
| `>` | Turn right (if clear) |
| `*` | Stop |

## Setup

1. Open `SmartRoboticVehicle.ino` in the Arduino IDE.
2. Install the `AFMotor` library if not already installed.
3. Connect hardware as per pin definitions in the code:
   - Ultrasonic: `Trig` → A1, `Echo` → A0
   - Servo → Pin 10
   - Motors → Motor Shield ports M1–M4
   - Bluetooth module → Arduino RX/TX (Serial)
4. Upload the sketch to your Arduino.
5. Pair your phone with the Bluetooth module to drive manually, or let the car run autonomously using the obstacle-avoidance mode.

## Future Upgrades

- Add an Android/iOS companion app with live distance readouts and mode-switching controls
- Integrate camera-based object detection for smarter navigation, instead of relying only on ultrasonic distance

## Status

Fully functional. Supports Bluetooth control, autonomous obstacle avoidance, and voice control, with seamless switching between modes.
