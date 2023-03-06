#include <Wire.h>
#include <TimeLib.h>
#include <RTClib.h>
RTC_DS1307 rtc;


int inputPins[] = {2, 3, 6, 7, 9, 11, 13};  // an array of the input pins

void setup() {
  Serial.begin(9600);  // initialize the serial monitor
rtc.begin();
  // Set the time on the RTC module to the current time
rtc.adjust(DateTime(2023, 3, 2, 18, 20, 20));

  // set the input pins as inputs with pull-up resistors
  for (int i = 0; i < 7; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }
}

void loop() {
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  int openCircuitCount = 0; // declare and initialize the variable before the for-loop
  // read the state of each input pin and print a message to the serial monitor
  for (int i = 0; i < 7; i++) {
    bool currentState = digitalRead(inputPins[i]) == LOW;
    if (currentState) {
      Serial.print("Circuit ");
      Serial.print(i + 1);
      Serial.println(" closed");
    } else {
      Serial.print("Circuit ");
      Serial.print(i + 1);
      Serial.println(" open");
      openCircuitCount++; // increment the open circuit count
    }
  }
  Serial.print("Number of open circuits: ");
  Serial.println(openCircuitCount);
  Serial.println(rtc.now().timestamp());
  delay(2000);  // wait for 100 milliseconds before reading again
}