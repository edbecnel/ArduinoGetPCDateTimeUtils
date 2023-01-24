#include <stdio.h>
#include <string.h>
#include <ctype.h>
// #include <ctime>
#include <stdlib.h>
#include "ArduinoGetPCDateTimeUtils.h"
#include "DaysAndTime.h"
#include "Alarm.h"

DateAndTime startTime;
DateAndTime currentTime;

using namespace ArduinoGetPCDateTimeUtils;
using namespace ArduinoAlarm;

Alarm alarms[2];
long seconds = 0;
int prevTemperature = -999;
int currTemperature = 41;
int loopTimeDelaySeconds = 1;  // In seconds

void print(const char* msg, bool newLine = false);
void print(int number, bool newLine = false);
void print(long number, bool newLine=false);
void print(int number, const char* format, bool newLine = false);
void print2digits(int number, bool newLine = false);
void printTime(int hours, int minutes, int seconds, bool newLine = false);
void printDate(int month, int day, int year, bool newLine = false);
void printDaysAndTime(DaysAndTime daysAndTime, bool newLine = false);
void printDateAndTime(DateAndTime dateAndTime, bool newLine = false);
void printTimeSpan(DaysAndTime frequency, bool newLine = false);
void printTimeOfDay(DaysAndTime timeOfDay, bool newLine = false);
void printAlarmTriggerDateAndTime(Alarm alarm, bool newLine = false);
void printTimeType(TemperatureThresholdTimeType timeType, bool newLine = false);
void printTriggerAndThreshold(Alarm alarm, TemperatureThreshold threshold, bool newLine = false);
int GetCurrentTemperature(bool displayOnChange = false);


void print(const char* msg, bool newLine)
{
    if (msg == NULL)
        return;
    Serial.print(msg);
    if (newLine)
        Serial.println("");
}

void printNewLine()
{
    print("", true);
}

void print(int number, const char* format, bool newLine)
{
    char buffer[50];
    if (format == NULL)
        sprintf(buffer, "%d", number);
    else
        sprintf(buffer, format, number);
    print(buffer, newLine);
}

void print(long number, const char* format, bool newLine)
{
    char buffer[50];
    if (format == NULL)
        sprintf(buffer, "%ld", number);
    else
        sprintf(buffer, format, number);
    print(buffer, newLine);
}

void print(int number, bool newLine)
{
    print(number, NULL, newLine);
}

void print(long number, bool newLine)
{
    print(number, NULL, newLine);
}

void print2digits(int number, bool newLine)
{
    print(number, "%02d", newLine);
}

void printTime(int hours, int minutes, int seconds, bool newLine)
{
    print2digits(hours);
    print(":");
    print2digits(minutes);
    print(":");
    print2digits(seconds, newLine);
}

void printDate(int month, int day, int year, bool newLine)
{
    print2digits(month);
    print("/");
    print2digits(day);
    print("/");
    print(year, newLine);
}

void printAlarmTriggerDateAndTime(Alarm alarm, bool newLine)
{
    print("Alarm Has Been Set for [mon/day/yr hr:min:sec]: ");
    DateAndTime dateAndTime = alarm.GetTriggerDateAndTime();
    // Print date...
    printDate(dateAndTime.month, dateAndTime.day, dateAndTime.year);
    print("  ");
    // ...and time
    printTime(dateAndTime.hours, dateAndTime.minutes, dateAndTime.seconds, true);
}

void printTimeType(TemperatureThresholdTimeType timeType, bool newLine)
{
    switch (timeType)
    {
    case TemperatureThresholdTimeType::TimeOfDay:
        print("TimeOfDay", newLine);
        break;
    case TemperatureThresholdTimeType::TimeSpan:
        print("TimeSpan", newLine);
        break;
    case TemperatureThresholdTimeType::None:
        print("None", newLine);
        break;
    }
}

void printDaysAndTime(DaysAndTime daysAndTime, bool newLine)
{
    print(daysAndTime.GetDays());
    print(" ");
    print2digits(daysAndTime.GetHours());
    print(":");
    print2digits(daysAndTime.GetMinutes());
    print(":");
    print2digits(daysAndTime.GetSeconds());
    if (newLine);
    printNewLine();
}

void printDateAndTime(DateAndTime dateAndTime, bool newLine)
{
    print2digits(dateAndTime.month);
    print("/");
    print2digits(dateAndTime.day);
    print("/");
    print(dateAndTime.year);
    print(" ");
    print2digits(dateAndTime.hours);
    print(":");
    print2digits(dateAndTime.minutes);
    print(":");
    print2digits(dateAndTime.seconds, newLine);
}

void printTimeSpan(DaysAndTime frequency, bool newLine)
{
    print("TimeSpan: [Days Hours:Minute:Seconds] = ");
    printDaysAndTime(frequency, newLine);
}

void printTimeOfDay(DaysAndTime timeOfDay, bool newLine)
{
    print("TimeOfDay: [Day Hour:Minute:Second] = ");
    printDaysAndTime(timeOfDay, newLine);
}

void printTriggerAndThreshold(Alarm alarm, TemperatureThreshold threshold, bool newLine)
{
    printAlarmTriggerDateAndTime(alarm);
    print(" ");
    switch (threshold.TimeType)
    {
    case TemperatureThresholdTimeType::TimeOfDay:
        printTimeOfDay(threshold.Frequency, newLine);
        break;
    case TemperatureThresholdTimeType::TimeSpan:
        printTimeSpan(threshold.Frequency, newLine);
        break;
    default:
        printTimeType(threshold.TimeType, newLine);
        break;
    }
}

// TODO: Replace the implementation of this function to get the temperature from the temperature sensor
int GetCurrentTemperature(bool displayOnChange)
{
    DateAndTime currTime;
    DateAndTime::getCurrentDateAndTime(currTime);
    long elapsedSeconds = abs(startTime.secondsTo(currTime));

    // if (elapsedSeconds < 32)
    if (elapsedSeconds < 17)
    {
        currTemperature = 41;
    }
    // else if (elapsedSeconds < 63)
    else if (elapsedSeconds < 33)
    {
        currTemperature = 40;
    }
    // else if (elapsedSeconds < 94)
    else if (elapsedSeconds < 62)
    {
        currTemperature = 31;
    }
    else
    {
        currTemperature = 41;
    }
    // Keep this code for debugging purposes
    if (elapsedSeconds > seconds || currTemperature != prevTemperature)
    {
        if (displayOnChange)
        {
            seconds = elapsedSeconds;
            print("Temperature = ");
            print(currTemperature);
            print(" Time = ");
            print2digits(currTime.hours);
            print(":");
            print2digits(currTime.minutes);
            print(":");
            print2digits(currTime.seconds);
            printNewLine();
        }

        prevTemperature = currTemperature;
    }
    return currTemperature;
}


// TODO: Replace the implementation of this function with getting the current time from the RTCZero board
void GetCurrentDateAndTime(DateAndTime& dateAndTime)
{
    dateAndTime.month = currentTime.month;
    dateAndTime.day = currentTime.day;
    dateAndTime.year = currentTime.year;
    dateAndTime.hours = currentTime.hours;
    dateAndTime.minutes = currentTime.minutes;
    dateAndTime.seconds = currentTime.seconds;
}

void setup() 
{
    Serial.begin(115200);

    // Give some time to clear the Serial Monitor
    delay(5000);
    // Must set function for getting the current date and time
    DateAndTime::setGetCurrentDateAndTimeFunction(&GetCurrentDateAndTime);


    // TODO: *** Remove the following code after properly implementing GetCurrentDateAndTime() to get the date and time from the RTCZero board
    currentTime = DateAndTime(1, 24, 2023, 14, 20, 0);
    print("Starting date/time: ");
    printDateAndTime(currentTime, true);

    DateAndTime::getCurrentDateAndTime(startTime);
    currentTime = startTime;

    // Use the DelayInSeconds when only when using the RTCZero's alarm.
    // DelayInSeconds isn't necessary when using our Alarm object's triggers detected via code in the loop() function.
    // FlushTotalTimeInSeconds is the total time delay caused by the Flush sequence.
    // To keep the alarm triggering at the correct time, setting Alarm::DelayInSeconds will cause the Alarm
    // to take this delay into account by subtracting the delay time from the Alarm trigger time.
    Alarm::DelayInSeconds = 0;
    // Alarm::DelayInSeconds = FlushTotalTimeInSeconds;

    // Frequency Alarm
    DaysAndTime frequency(0, 0, 0, 5); // Every 5 seconds
    alarms[0] = Alarm(AlarmType::Frequency, frequency);

    DateAndTime currTime;
    DateAndTime::getCurrentDateAndTime(currTime);
    currTime.addSeconds(15);
    DaysAndTime above40TimeOfDay(0, currTime.hours, currTime.minutes, currTime.seconds);

    currTime.addSeconds(15);
    DaysAndTime below41TimeOfDay(0, currTime.hours, currTime.minutes, currTime.seconds);

    // Temperature Alarm
    // Above 40 threshold
    TemperatureThreshold threshold(40, TemperatureThresholdType::Above, TemperatureThresholdTimeType::TimeOfDay, above40TimeOfDay);
    alarms[1] = Alarm(AlarmType::TemperatureThreshold, frequency);
    alarms[1].AddTemperatureThreshold(threshold);

    // Below 41 threshold
    threshold.Temperature = 41;
    threshold.Type = TemperatureThresholdType::Below;
    // threshold.TimeType = TemperatureThresholdTimeType::TimeSpan;
    // frequency.Set(0, 1, 0, 0);  // Once per hour
    // threshold.Frequency = frequency;
    threshold.TimeType = TemperatureThresholdTimeType::TimeOfDay;
    threshold.Frequency = below41TimeOfDay;
    alarms[1].AddTemperatureThreshold(threshold);

    // Below 32 threshold
    threshold.Temperature = 32;
    threshold.TimeType = TemperatureThresholdTimeType::TimeSpan;
    // frequency.Set(0, 0, 15, 0);  // Once every 15 minutes
    frequency.Set(0, 0, 0, 15);     // Once every 15 seconds
    threshold.Frequency = frequency;
    alarms[1].AddTemperatureThreshold(threshold);

    alarms[0].Start();
    int temperature = GetCurrentTemperature();
    alarms[1].Start(temperature);

    print("alarms[1] Threshold - ");
    printTriggerAndThreshold(alarms[1], alarms[1].GetThresholdForTemperature(GetCurrentTemperature()), true);
}

void loop() 
{
    if (alarms[0].IsTriggered())
    {
        print("Frequency Alarm 0 triggered", true);
        alarms[0].SetNewTrigger();
    }
    int temperature = GetCurrentTemperature(true);
    if (alarms[1].IsTriggered())
    {
        print("Temperature Threshold Alarm 1 triggered", true);
        alarms[1].SetNewTrigger(temperature);
    }
    if (alarms[1].TemperatureThresholdCrossed(temperature))
    {
        print("Temperature Threshold Crossed - Set New Trigger for Alarm 1", true);
        alarms[1].SetNewTrigger(temperature);
        TemperatureThreshold newThreshold = alarms[1].GetThresholdForTemperature(temperature);
        printTriggerAndThreshold(alarms[1], newThreshold, true);
    }
    // TODO: *** Remove this when using a real clock and temperature sensor
    delay(loopTimeDelaySeconds * 1000);  // Needed to mock up time since GetCurrentDateAndTime simple ticks up 1 second on each loop (delay is in milliseconds)
    currentTime.addSeconds(1); 
}
