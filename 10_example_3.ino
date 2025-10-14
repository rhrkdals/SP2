/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/faq/how-to-control-speed-of-servo-motor
 */

#include <Servo.h>
#define PULSE_DURATION 10
#define PIN_SERVO 10
#define PIN_ECHO 13
#define PIN_TRIG 12
#define INTERVAL 25
#define SND_VEL 346.0     // sound velocity at 24 celsius degree (unit: m/sec)

#define TIMEOUT ((INTERVAL / 2) * 1000.0) // maximum echo waiting time (unit: usec)
#define SCALE (0.001 * 0.5 * SND_VEL)     // coefficent to convert duration to distance

Servo myServo;
unsigned long MOVING_TIME =1000; // moving time is 3 seconds
unsigned long moveStartTime;
int startAngle = 30; // 30°
int stopAngle  = 150; // 90°

void setup() {
  myServo.attach(PIN_SERVO);
  moveStartTime = millis(); // start moving

  pinMode(PIN_TRIG,OUTPUT);
  pinMode(PIN_ECHO,INPUT);
  digitalWrite(PIN_TRIG, LOW);

  myServo.write(startAngle); // Set position
  delay(500);

  Serial.begin(57600);
}

float sigmoid(float x) {
  return 1.0 / (1.0 + exp(-x));
}

void loop() {
  unsigned long progress = millis() - moveStartTime;
  float dist_raw; 
  dist_raw = USS_measure(PIN_TRIG,PIN_ECHO);

 if(dist_raw< 100){
    for(float t=-6.0;t<=6.0; t+=0.1){
      float s = sigmoid(t);
      long angle = startAngle + s * (stopAngle-startAngle);
      myServo.write(angle);  
        delay(30);
    }
    while(dist_raw<100){
      dist_raw = USS_measure(PIN_TRIG, PIN_ECHO);

      Serial.print("wait raw:");
      Serial.println(dist_raw);
      if (dist_raw>100){
        break;
      }else{
        delay(10);
      }
    }
    for(float t=6.0;t>=-6; t-=0.1){
      float s = sigmoid(t);
      long angle = startAngle + s * (stopAngle-startAngle);
      myServo.write(angle);  
      delay(30);
    }
  }
}
  float USS_measure(int TRIG, int ECHO){
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE; // unit: mm

}
