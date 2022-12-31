// #include <RTCZero.h>
#include <ArduinoGetPCDateTimeUtils.h>

using namespace ArduinoGetPCDateTimeUtils;

byte alarmMonth;
byte alarmYear;
byte alarmDay;
byte alarmHours;
byte alarmMinutes;
byte alarmSeconds;
DateAndTimeBytes compileDateAndTimeBytes;

// RTCZero rtc;

void setup() {
  Serial.begin(115200);

  // rtc.begin();  // nitialize RTC 24H format

  // put your setup code here, to run once:
  bool success = compileDateAndTimeBytes.getCompileDateAndTime();
  if (success) {
    // Set compiler date and time on the RTCZero board...
    // Note: DateAndTimBytes.year is a byte data type and as such, has a maximum value of 127, so the year value doesn't include the century. I.e., 2022 is represented as 22
    // rtc.setDate(compileDateAndTimeBytes.month, compileDateAndTimeBytes.day, compileDateAndTimeBytes.year);
    // rtc.setTime(compileDateAndTimeBytes.hours, compileDateAndTimeBytes.minutes, compileDateAndTimeBytes.seconds);
    // Verify the date and time was set on the board...
    // setMonth = rtc.getMonth();
    // setDay = rtc.getDay();
    // setYear = rtc.getYear();
    // setHours = rtc.getHours();
    // setSMinutes = rtc.getMinutes();
    // setSeconds = rtc.getSeconds();

    // Set the alarm date and time on the RTCZero board...
    alarmMonth = 2;
    alarmDay = 28;
    alarmYear = 22;
    alarmHours = 13;
    alarmMinutes = 2;
    alarmSeconds = 15;
    // rtc.setAlarmDate(alarmDay, alarmMonth, alarmYear);
    // Set alarm time
    // rtc.setAlarmTime(alarmHours, alarmMinutes, alarmSeconds);
  }
}


void loop() {
  // put your main code here, to run repeatedly:

  // Get the alarm date and time that was  set on the board...
  // alarmMonth = rtc.getAlarmMonth();
  // alarmDay = rtc.getAlarmDay();
  // alarmYear = rtc.getAlarmYear();
  // alarmHours = rtc.getAlarmHours();
  // alarmMinutes = rtc.getAlarmMinutes();
  // alarmSeconds = rtc.getAlarmSeconds();

  // TODO: Replace the following with getting these values from the RTCZero object:
  byte currMonth = 1;
  byte currDay = 31;
  byte currYear = 23;
  byte currHours = 10;
  byte currMinutes = 13;
  byte currSeconds = 5;
  // byte currMonth = rtc.getMonth();
  // byte currDay = rtc.getDay();
  // byte currYear = rtc.getYear();
  // byte currHours = rtc.getHours();
  // byte currMinutes = rtc.getMinutes();
  // byte currSeconds = rtc.getSeconds();


  DateAndTimeBytes currentDateAndTime(currMonth, currDay, currYear, currHours, currMinutes, currSeconds);
  DateAndTimeBytes alarmDateAndTime(alarmMonth, alarmDay, alarmYear, alarmHours, alarmMinutes, alarmSeconds);
  int daysToAlarm, hoursToAlarm, minutesToAlarm, secondsToAlarm;
  // Get the remaining days, hours, minutes, and seconds to the alarm...
  // currentDateAndTime.getDaysHoursMinutesSecondsTo(alarmDateAndTime, daysToAlarm, hoursToAlarm, minutesToAlarm, secondsToAlarm);
  char buffer[100];
  sprintf(buffer, "Time remaining: %02d days %02d hours %02d minutes %02d seconds", daysToAlarm, hoursToAlarm, minutesToAlarm, secondsToAlarm);
  Serial.println(buffer);

  delay(10000);
}
