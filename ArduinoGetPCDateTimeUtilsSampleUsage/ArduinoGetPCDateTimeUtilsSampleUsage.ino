#include <ArduinoGetPCDateTimeUtils.h>

using namespace ArduinoGetPCDateTimeUtils;


int setYear;
int setMonth;
int setDay;
int setHours;
int setMinutes;
int setSeconds;
int alarmYear;
int alarmMonth;
int alarmDay;
int alarmHours;
int alarmMinutes;
int alarmSeconds;
DateAndTimeBytes compileDateAndTimeBytes;

void setup() {
  Serial.begin(115200);

  // put your setup code here, to run once:
  bool success = compileDateAndTimeBytes.getCompileDateAndTime();
  if (success) {
    // Set compiler date and time on the RTCZero board...
    // Note: DateAndTimBytes.year is a byte data type and as such, has a maximum value of 127, so the year value doesn't include the century. I.e., 2022 is represented as 22
    // rtc.setDate(dateAndTimeBytes.month, dateAndTimeBytes.day, dateAndTimeBytes.year);
    // rtc.setTime(dateAndTimeBytes.hours, dateAndTimeBytes.minutes, dateAndTimeBytes.seconds);
    // Verify the date and time was set on the board...
    // setYear = rtc.getYear();
    // setMonth = rtc.getMonth();
    // setDay = rtc.getDay();
    // setHours = rtc.getHours();
    // setSMinutes = rtc.getMinutes();
    // setSeconds = rtc.getSeconds();

    // Set the alarm daqte and time on the RTCZero board...
    // alarmYear = 23;
    // alarmMonth = 2;
    // alarmDay = 10;
    // alarmHours = 13;
    // alarmMinutes = 5;
    // alarmSeconds = 17;
    // Set alarm date
    // rtc.setAlarmDate(alarmYear, alarmMonth, alarmYear);
    // Set alarm time
    // rtc.setAlarmTime(alarmHours, alarmMinutes, alarmSeconds);
    // Verify alarm date and time were set on the board...
    // alarmYear = rtc.getAlarmYear();
    // alarmMonth = rtc.getAlarmMonth();
    // alarmDay = rtc.getAlarmDay();
    // alarmHours = rtc.getAlarmHours();
    // alarmMinutes = rtc.getAlarmMinutes();
    // alarmSeconds = rtc.getAlarmSeconds();
  }

  delay(10000);
}

void loop() {
  // put your main code here, to run repeatedly:
  DateAndTimeBytes alarmDateAndTime(alarmMonth, alarmDay, alarmYear, alarmHours, alarmMinutes, alarmSeconds);
  int hoursToAlarm, minutesToAlarm, secondsToAlarm;
  // Get the remaining seconds to the alarm...
  secondsToAlarm = compileDateAndTimeBytes.secondsTo(alarmDateAndTime);
  // Get the remaining hours, minutes, and seconds to the alarm...
  compileDateAndTimeBytes.getHoursMinutesSecondsTo(alarmDateAndTime, hoursToAlarm, minutesToAlarm, secondsToAlarm);
}
