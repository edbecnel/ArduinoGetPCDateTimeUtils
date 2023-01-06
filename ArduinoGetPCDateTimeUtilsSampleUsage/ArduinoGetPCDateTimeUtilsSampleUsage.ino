#include <RTCZero.h>
#include <ArduinoGetPCDateTimeUtils.h>

using namespace ArduinoGetPCDateTimeUtils;

// Comment out the line below if testing without the RTCZero board
RTCZero rtc;

int delayInSecs = 5;

DateAndTimeBytes compilerDateAndTime;
DateAndTimeBytes currentDateAndTime;
DateAndTimeBytes alarmDateAndTime;

// Set the compiler date and time on the RTCZero board
void SetCompilerDateAndTime()
{
  compilerDateAndTime.getCompileDateAndTime();
  // Set compiler date and time on the RTCZero board...
  // Note: DateAndTimBytes.year is a byte data type and as such, has a maximum value of 127, so the year value doesn't include the century. I.e., 2022 is represented as 22
  // Comment out the lines below if testing without the RTCZero board
  rtc.setDate(compilerDateAndTime.month, compilerDateAndTime.day, compilerDateAndTime.year);
  rtc.setTime(compilerDateAndTime.hours, compilerDateAndTime.minutes, compilerDateAndTime.seconds);
}

// Retrieve the current date and time set on the RTCZero board
void GetCurrentDateAndTime()
{
  // Get the date and time that is set on the RTCZero board...
  currentDateAndTime.month = rtc.getMonth();
  currentDateAndTime.day = rtc.getDay();
  currentDateAndTime.year = rtc.getYear();
  currentDateAndTime.hours = rtc.getHours();
  currentDateAndTime.minutes = rtc.getMinutes();
  currentDateAndTime.seconds = rtc.getSeconds();
  // Replace the above with code below to test without the RTCZero board...
  // currentDateAndTime.month = 12;
  // currentDateAndTime.day = 31;
  // currentDateAndTime.year = 22;
  // currentDateAndTime.hours = 23;
  // currentDateAndTime.minutes = 13;
  // currentDateAndTime.seconds = 5;
}

// Retrieve the alarm date and time set on the RTCZero board
void GetAlarmDateAndTime()
{
  // Note: If testing without the RTCZero board, comment out the contents of this function to use the previously set date and time
  // Get the alarm date and time that is set on the RTCZero board...
  alarmDateAndTime.month = rtc.getAlarmMonth();
  alarmDateAndTime.day = rtc.getAlarmDay();
  alarmDateAndTime.year = rtc.getAlarmYear();
  alarmDateAndTime.hours = rtc.getAlarmHours();
  alarmDateAndTime.minutes = rtc.getAlarmMinutes();
  alarmDateAndTime.seconds = rtc.getAlarmSeconds();
}

void GetSimulatedCountdownDateAndTime()
{
  // Simulated clock ticking up.
  // WARNING: Only works until the current day goes over 28, then resets the current day to 1
  currentDateAndTime.seconds += (byte)delayInSecs;
  if (currentDateAndTime.seconds > 59)
  {
    currentDateAndTime.seconds = 0;
    currentDateAndTime.minutes++;
    if (currentDateAndTime.minutes > 59)
    {
      currentDateAndTime.minutes = 0;
      if (currentDateAndTime.hours > 23)
      {
        currentDateAndTime.hours = 0;
        currentDateAndTime.day++;
        if (currentDateAndTime.day > 28)
          currentDateAndTime.day = 1;
      }
    }
  }
}

// Prints the date and time along with an optional preceding message. The format is: Month/Day/Year Hours:Minutes:Seconds
void DisplayDateAndTime(char* messagePrefix, DateAndTimeBytes dateAndTime)
{
  char buffer[50] = "";
  if (messagePrefix != NULL && strlen(messagePrefix) > 0)
  {
    Serial.print(messagePrefix);
    Serial.print(": ");
  }
  sprintf(buffer, "%02d/", dateAndTime.month);
  Serial.print(buffer);
  sprintf(buffer, "%02d/", dateAndTime.day);
  Serial.print(buffer);
  sprintf(buffer, "%02d ", dateAndTime.year);
  Serial.print(buffer);
  sprintf(buffer, "%02d:", dateAndTime.hours);
  Serial.print(buffer);
  sprintf(buffer, "%02d:", dateAndTime.minutes);
  Serial.print(buffer);
  sprintf(buffer, "%02d", dateAndTime.seconds);
  Serial.println(buffer);
}

void DisplayCountdownTimeToAlarm()
{
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
}

// Set the alarm date and time on the RTCZero board
void SetAlarmDateAndTime()
{
  // Assign values for alarm date and time
  alarmDateAndTime.month  = 12;
  alarmDateAndTime.day = 31;
  alarmDateAndTime.year = 22;
  alarmDateAndTime.hours = 23;
  alarmDateAndTime.minutes = 14;
  alarmDateAndTime.seconds = 50;

  // Set the alarm date and time on the RTCZero board...
  // Comment out the lines below if testing without the RTCZero board
  rtc.setAlarmDate(alarmDateAndTime.day, alarmDateAndTime.month, alarmDateAndTime.year);
  rtc.setAlarmTime(alarmDateAndTime.hours, alarmDateAndTime.minutes, alarmDateAndTime.seconds);
}

void setup() {
  Serial.begin(115200);

  // Comment out the line below if testing without the RTCZero board
  rtc.begin();  // Initialize RTC 24H format

  delay(delayInSecs * 1000);  // Delay to provide time to clear Serial Monitor for debugging purposes

  SetCompilerDateAndTime();   // Set the compiler date and time as the current time on the RTCZero board
  DisplayDateAndTime("Compiler date and time", compilerDateAndTime);
  GetCurrentDateAndTime();    // Get the current date and time on the RTCZero board to confirm it has been set
  DisplayDateAndTime ("Current date and time", currentDateAndTime);
  SetAlarmDateAndTime();
  DisplayDateAndTime ("Alarm date and time set", alarmDateAndTime);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(delayInSecs * 1000);

  // Get the current date and time that is set on the RTCZero board
  GetCurrentDateAndTime();
  // If testing without the RTCZero board, replace the above line of code with the following to retrieve a simulated date and time...
  // GetSimulatedCountdownDateAndTime();
  DisplayDateAndTime ("Current date and time", currentDateAndTime);

  // Get the alarm date and time that is set on the RTCZero board
  GetAlarmDateAndTime();
  DisplayDateAndTime ("Alarm date and time", alarmDateAndTime);

  DisplayCountdownTimeToAlarm();  
}
