#include "LedControl.h"
#include <DS3231.h>

DS3231  rtc(SDA, SCL);
LedControl lc = LedControl(A2, A3, A1, 1);

int state = 0;
int lastPress = 0;

void stateChange() {
  if(millis() - lastPress >= 300) {
    lastPress = millis(); 
    state++;
    if(state == 3) state = 0;
  } 
}

void setup() {
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), stateChange, FALLING);
  
  rtc.begin();
  
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

void loop() {
  if(state == 0) {
    lc.setChar(0, 0, rtc.getTimeStr()[0], false);
    lc.setChar(0, 1, rtc.getTimeStr()[1], false);
    lc.setChar(0, 2, rtc.getTimeStr()[3], false);
    lc.setChar(0, 3, rtc.getTimeStr()[4], false);
    lc.setChar(0, 4, rtc.getTimeStr()[6], false);
    lc.setChar(0, 5, rtc.getTimeStr()[7], false);
  }else if(state == 1) {
    lc.setChar(0, 0, rtc.getDateStr()[0], false);
    lc.setChar(0, 1, rtc.getDateStr()[1], false);
    lc.setChar(0, 2, rtc.getDateStr()[3], false);
    lc.setChar(0, 3, rtc.getDateStr()[4], false);
    lc.setChar(0, 4, rtc.getDateStr()[8], false);
    lc.setChar(0, 5, rtc.getDateStr()[9], false);
  } else {
    lc.setChar(0, 0, ' ', false);
    lc.setChar(0, 1, ' ', false);
    lc.setChar(0, 2, ' ', false);
    lc.setChar(0, 3, ' ', false);
    lc.setChar(0, 4, ' ', false);
    lc.setChar(0, 5, ' ', false);
  }
  
  delay(250);
}
