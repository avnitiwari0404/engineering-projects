# Theory & Working Principles

## 1. Ultrasonic Distance Measurement

The ultrasonic sensor measures the distance between the sensor and an object by sending an ultrasonic pulse and measuring the time taken for the echo to return.

The sensor has four pins:

- VCC
- TRIG
- ECHO
- GND

The Arduino sends a short trigger pulse to the TRIG pin.

The sensor then sends an ultrasonic wave. When the wave reflects from an object, the ECHO pin stays HIGH for a duration proportional to the travel time of the sound wave.

The Arduino measures this time using `pulseIn()`.

---

## 2. Distance Calculation

The code calculates distance using:

`distance = duration × 0.0343 / 2`

The value `0.0343` represents the approximate speed of sound in centimetres per microsecond.

The division by 2 is required because the measured time represents the sound travelling:

Object → Sensor

and

Sensor → Object.

Therefore, the measured time is for the complete round trip.

---

## 3. Servo Motor

The servo motor is used to move the barrier.

The Arduino controls the servo using the Servo library.

In this project:

- `0°` = barrier closed
- `90°` = barrier open

The servo signal wire is connected to Arduino pin 9.

---

## 4. Control Logic

The Arduino continuously measures the distance.

If:

`distance < 25 cm`

the barrier opens.

If:

`distance > 35 cm`

the barrier closes.

Between 25 cm and 35 cm, the barrier keeps its current position.

---

## 5. Hysteresis

The difference between the opening distance and closing distance creates a hysteresis zone.

Opening threshold:

`25 cm`

Closing threshold:

`35 cm`

This prevents the barrier from repeatedly opening and closing when an object is hovering around a single threshold.

---

## 6. Main Components

### Arduino Uno

Acts as the controller of the system. It reads the ultrasonic sensor, calculates distance, and controls the servo.

### HC-SR04 Ultrasonic Sensor

Measures the distance to an object using ultrasonic sound waves.

### Servo Motor

Converts the electrical control signal from the Arduino into mechanical rotation to move the barrier.

---

## 7. System Flow

Object approaches
↓
Ultrasonic sensor measures distance
↓
Arduino calculates distance
↓
Arduino compares distance with thresholds
↓
Servo position is determined
↓
Barrier opens or closes
