#include <ArduinoGetPCDateTimeUtils.h>

using namespace ArduinoGetPCDateTimeUtils;

void setup() {
  // put your setup code here, to run once:
  DateAndTimeBytes dateAndTimeBytes;

  bool success = dateAndTimeBytes.getCompileDateAndTime();
  if (success) {
    //rtc.setTime(dateAndTimeBytes.hours, dateAndTimeBytes.minutes, dateAndTimeBytes.seconds);
    // Note: DateAndTimBytes.year is a byte data type and as such, has a maximum value of 127, so the year value doesn't include the century. I.e., 2022 is represented as 22
    //rtc.setDate(dateAndTimeBytes.month, dateAndTimeBytes.day, dateAndTimeBytes.year);
  }
}

void loop() {
  delay(10000);

  // put your main code here, to run repeatedly:
  byte year = 22;
  byte month = 12;
  byte day = 31;
  byte hours = 23;
  byte minutes = 58;
  byte seconds = 0;

  // year = rtc.getYear();
  // month = rtc.getMonth();
  // day = rtc.getDay();
  // hours = rtc.getHours();
  // minutes = rtc.getMinutes();
  // seconds = rtc.getSeconds();

  DateAndTimeBytes dateAndTimeBytes(month, day, year, hours, minutes, seconds);
  dateAndTimeBytes.addMinutes(10);

  // rtc.setAlarmDate(day, month, year);
  // rtc.setAlarmTime(hours, minutes, seconds);
}
