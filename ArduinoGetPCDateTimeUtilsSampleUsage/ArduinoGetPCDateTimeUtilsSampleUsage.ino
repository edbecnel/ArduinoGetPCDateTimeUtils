// #include <RTCZero.h>
#include <ArduinoGetPCDateTimeUtils.h>

using namespace ArduinoGetPCDateTimeUtils;

byte alarmMonth;
byte alarmYear;
byte alarmDay;
byte alarmHours;
byte alarmMinutes;
byte alarmSeconds;

byte currMonth;
byte currDay;
byte currYear;
byte currHours;
byte currMinutes;
byte currSeconds;

int delayInSecs = 5;

DateAndTimeBytes compileDateAndTimeBytes;

void GetCurrentDateAndTime()
{
  // currMonth = rtc.getMonth();
  // currDay = rtc.getDay();
  // currYear = rtc.getYear();
  // currHours = rtc.getHours();
  // currMinutes = rtc.getMinutes();
  // currSeconds = rtc.getSeconds();
  currMonth = 12;
  currDay = 31;
  currYear = 22;
  currHours = 23;
  currMinutes = 13;
  currSeconds = 5;
}

// RTCZero rtc;
void setup() {
  Serial.begin(115200);

  // rtc.begin();  // nitialize RTC 24H format

  GetCurrentDateAndTime();

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
    // alarmMonth = 11;
    // alarmDay = 3;
    // alarmYear = 23;
    // alarmHours = 1;
    // alarmMinutes = 23;
    // alarmSeconds = 52;
    alarmMonth = 12;
    alarmDay = 31;
    alarmYear = 22;
    alarmHours = 23;
    alarmMinutes = 14;
    alarmSeconds = 50;

    // rtc.setAlarmDate(alarmDay, alarmMonth, alarmYear);
    // Set alarm time
    // rtc.setAlarmTime(alarmHours, alarmMinutes, alarmSeconds);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(delayInSecs * 1000);

  // TODO:
  // Replace hard-coded values with values retrieve from the RTCZero object by commenting out lines with
  // hard-coded values and uncommenting lines with procedurally retreived values from the rtc object.

  // Get the alarm date and time that was  set on the board...
  // alarmMonth = rtc.getAlarmMonth();
  // alarmDay = rtc.getAlarmDay();
  // alarmYear = rtc.getAlarmYear();
  // alarmHours = rtc.getAlarmHours();
  // alarmMinutes = rtc.getAlarmMinutes();
  // alarmSeconds = rtc.getAlarmSeconds();
  // Get the current rtc date and time
  // GetCurrentDateAndTime();
  
  // Simulated clock ticking up.
  // WARNING: Only works until the current day goes over 28, then resets the current day to 1
  currSeconds += (byte)delayInSecs;
  if (currSeconds > 59)
  {
    currSeconds = 0;
    currMinutes++;
    if (currMinutes > 59)
    {
      currMinutes = 0;
      if (currHours > 23)
      {
        currHours = 0;
        currDay++;
        if (currDay > 28)
          currDay = 1;
      }
    }
  }
   
  // DateAndTimeBytes currentDateAndTime(currMonth, currDay, currYear, currHours, currMinutes, currSeconds);
  // DateAndTimeBytes alarmDateAndTime(alarmMonth, alarmDay, alarmYear, alarmHours, alarmMinutes, alarmSeconds);
  DateAndTimeBytes currentDateAndTime(currMonth, currDay, currYear, currHours, currMinutes, currSeconds);
  DateAndTimeBytes alarmDateAndTime(alarmMonth, alarmDay, alarmYear, alarmHours, alarmMinutes, alarmSeconds);
 
  long daysToAlarm, hoursToAlarm, minutesToAlarm, secondsToAlarm;
  // Get the remaining days, hours, minutes, and seconds to the alarm...
  currentDateAndTime.getDaysHoursMinutesSecondsTo(alarmDateAndTime, daysToAlarm, hoursToAlarm, minutesToAlarm, secondsToAlarm);
  char buffer[100];
  sprintf(buffer, "Time remaining: Days = %02d ", daysToAlarm);
  Serial.print(buffer);
  sprintf(buffer, "Hours = %02d ", hoursToAlarm);
  Serial.print(buffer);
  sprintf(buffer, "Minutes = %02d ", minutesToAlarm);
  Serial.print(buffer);
  sprintf(buffer, "Seconds = %02d", secondsToAlarm);
  Serial.println(buffer);

  // TODO: Remove the following when using the rtc object. It's used here only for debugging purposes.
  // Reset the current date and time back to its initial settings when the alarm is time has been reached (secondsTo remaining is 0 or less).
  long secondsTo = currentDateAndTime.secondsTo(alarmDateAndTime);
  if (secondsTo <= 0)
  {
    GetCurrentDateAndTime();
  }
}
