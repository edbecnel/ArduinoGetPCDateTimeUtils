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
  // put your main code here, to run repeatedly:

}
