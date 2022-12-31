#include <ArduinoGetPCDateTimeUtils.h>

using namespace ArduinoGetPCDateTimeUtils;


int setYear;
int setMonth;
int setDay;
int setHours;
int setMinutes;
int setSeconds;
byte alarmMonth = 2;
byte alarmYear = 22;
byte alarmDay = 28;
byte alarmHours = 13;
byte alarmMinutes = 2;
byte alarmSeconds 15;
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
  // TODO: Replace the following with getting these values from the RTCZero object:
  byte currMonth = 1;
  byte currDay = 31;
  byte currYear = 23;
  byte currHours = 10;
  byte currMinutes = 13;
  byte currSeconds = 5;
  DateAndTimeBytes currentDateAndTime(currMonth, currDay, currYear, currHours, currMinutes, currSeconds);
  DateAndTimeBytes alarmDateAndTime(alarmMonth, alarmDay, alarmYear, alarmHours, alarmMinutes, alarmSeconds);
  int daysToAlarm, hoursToAlarm, minutesToAlarm, secondsToAlarm;
  // Get the remaining days, hours, minutes, and seconds to the alarm...
  currentDateAndTime.getDaysHoursMinutesSecondsTo(alarmDateAndTime, daysToAlarm, hoursToAlarm, minutesToAlarm, secondsToAlarm);
}
