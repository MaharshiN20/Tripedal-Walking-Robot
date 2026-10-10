[README_Tripedal-Walking-Robot.md](https://github.com/user-attachments/files/33291472/README_Tripedal-Walking-Robot.md)
# Tripedal Walking Robot

Arduino firmware for a three-legged walking robot driven by a single servo joint. The robot walks forward on a repeating servo sweep and uses an ultrasonic sensor to stop when an obstacle comes within range.

Built as part of my research work at the AMIR Laboratory at Kennesaw State University.

<!-- Add a photo or GIF of the robot walking here, e.g.: ![Robot walking](media/walk.gif) -->

## How it works

1. **Startup:** The servo moves to a neutral position and serial logging starts at 9600 baud.
2. **Sensing:** Every 50 ms the sketch fires an HC-SR04 ultrasonic pulse. An interrupt on the echo pin times the return pulse without blocking the main loop, and the time is converted to distance in centimeters.
3. **Walking:** If the path is clear, the servo sweeps through its gait positions to take a step.
4. **Stopping:** If an obstacle is closer than **55 cm**, the robot moves to a rest position and halts.

## Hardware

| Component | Pin |
|---|---|
| Servo (leg joint) | 9 |
| Ultrasonic trigger | 11 |
| Ultrasonic echo (interrupt) | 2 |

- Arduino Uno (or compatible)
- HC-SR04 ultrasonic sensor
- Standard hobby servo
- Three-legged chassis

## Running it

1. Wire the components as shown above.
2. Open `TripedalWalkingRobotWalkCode.ino` in the Arduino IDE.
3. Select your board and port, then upload.
4. Open the Serial Monitor at 9600 baud to watch the distance readings.

## Notes

After it detects an obstacle, the sketch stops completely. Press the reset button to start walking again.
