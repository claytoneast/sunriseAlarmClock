#include <DS3232RTC.h>
//#include <Streaming.h>
#include <Arduino.h>
#include <Servo.h>
Servo myservo; 
int pos = 0;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  Serial.print("We have initialized");
  //setSyncProvider() causes the Time library to synchronize with the
  //external RTC by calling RTC.get() every five minutes by default.
  setSyncProvider(RTC.get);
}

void loop() {
  time_t t;
  t = now();
  Serial.println();
  Serial.print("minute");
  Serial.print(minute(t));
  Serial.print("hour");
  Serial.print(hour(t));
  if (hour(t) == 7 && minute(t) == 15) {
    activateClock();
  }
  delay(59000); // delay slightly less than a minute to be sure to check all minutes
}

void activateClock() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(1667);         // 1667ms between degree acutations === 5 minute total time
  }
  myservo.write(0);
}
