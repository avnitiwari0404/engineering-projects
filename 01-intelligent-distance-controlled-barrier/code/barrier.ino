#include <Servo.h>

// -------- Pin definitions --------
const int TRIG_PIN = 7 ;
const int ECHO_PIN = 6 ;
const int SERVO_PIN = 9 ;

// -------- Servo object --------
Servo barrierServo;

// -------- Barrier settings --------
const int OPEN_DISTANCE = 25 ;   // Open if object is closer than 25 cm
const int CLOSE_DISTANCE = 35 ;  // Close only after object is farther than 35 cm

// -------- Barrier positions --------
const int CLOSED_ANGLE = 0;
const int OPEN_ANGLE = 90;


// ======================================================
// SETUP
// ======================================================

void setup() {

  // Ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Attach servo
  barrierServo.attach(SERVO_PIN);

  // Start with barrier closed
  barrierServo.write(CLOSED_ANGLE);

  // Start Serial Monitor
  Serial.begin(9600);

  Serial.println("Intelligent Distance-Controlled Barrier");
  Serial.println("System started.");
}


// ======================================================
// MEASURE DISTANCE
// ======================================================

float measureDistance() {

  // Make sure TRIG starts LOW
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10 microsecond trigger pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure how long ECHO stays HIGH
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance
  float distance = duration * 0.0343 / 2;

  return distance;
}


// ======================================================
// MAIN LOOP
// ======================================================

void loop() {

  // Measure distance
  float distance = measureDistance();

  // Display distance on Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  // --------------------------------------------------
  // OPEN THE BARRIER
  // --------------------------------------------------

  if (distance < OPEN_DISTANCE) {

    barrierServo.write(OPEN_ANGLE);

    Serial.println("Object detected -> BARRIER OPEN");
  }


  // --------------------------------------------------
  // CLOSE THE BARRIER
  // --------------------------------------------------

  else if (distance > CLOSE_DISTANCE) {

    barrierServo.write(CLOSED_ANGLE);

    Serial.println("Area clear -> BARRIER CLOSED");
  }


  // --------------------------------------------------
  // BETWEEN 25 AND 35 cm
  // --------------------------------------------------
  
  else {

    Serial.println("Hysteresis zone -> KEEP CURRENT POSITION");
  }


  delay(200);
}
