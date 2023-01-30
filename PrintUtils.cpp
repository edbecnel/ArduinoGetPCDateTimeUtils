#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "Alarm.h"
#include "PrintUtils.h"

using namespace ArduinoGetPCDateTimeUtils;
using namespace ArduinoAlarm;
using namespace ArduinoPrintUtils;


void PrintUtils::print(const char* msg, bool newLine)
{
    if (msg == NULL)
        return;
    // TODO: 
    // Use printf when running in Visual Studio
    // Use Serial.print when running in Arduino environment
    // printf(msg);
    Serial.print(msg);
    if (newLine)
        Serial.print("\n");
}

void PrintUtils::print(char* msg, bool newLine)
{
    if (msg == NULL)
        return;
    // TODO: 
    // Use printf when running in Visual Studio
    // Use Serial.print when running in Arduino environment
    // printf(msg);
    // printf(msg);
    Serial.print(msg);
    if (newLine)
        Serial.print("\n");
}

void PrintUtils::printNewLine()
{
    PrintUtils::print("", true);
}

void PrintUtils::print(int number, const char* format, bool newLine)
{
    char buffer[50];
    if (format == NULL)
        sprintf(buffer, "%d", number);
    else
        sprintf(buffer, format, number);
    print(buffer, newLine);
}

void PrintUtils::print(long number, const char* format, bool newLine)
{
    char buffer[50];
    if (format == NULL)
        sprintf(buffer, "%ld", number);
    else
        sprintf(buffer, format, number);
    print(buffer, newLine);
}

void PrintUtils::print(int number, bool newLine)
{
    print(number, NULL, newLine);
}

void PrintUtils::print(long number, bool newLine)
{
    print(number, NULL, newLine);
}

void PrintUtils::print2digits(int number, bool newLine)
{
    print(number, "%02d", newLine);
}

void PrintUtils::printTime(int hours, int minutes, int seconds, bool newLine)
{
    print2digits(hours);
    print(":");
    print2digits(minutes);
    print(":");
    print2digits(seconds, newLine);
}

void PrintUtils::printDate(int month, int day, int year, bool newLine)
{
    print2digits(month);
    print("/");
    print2digits(day);
    print("/");
    print(year, newLine);
}

void PrintUtils::printAlarmTriggerDateAndTime(Alarm alarm, bool newLine)
{
    print("Alarm Has Been Set for [mon/day/yr hr:min:sec]: ");
    DateAndTime dateAndTime = alarm.GetTriggerDateAndTime();
    // Print date...
    printDate(dateAndTime.month, dateAndTime.day, dateAndTime.year);
    print("  ");
    // ...and time
    printTime(dateAndTime.hours, dateAndTime.minutes, dateAndTime.seconds, true);
}

void PrintUtils::printTimeType(TemperatureThresholdTimeType timeType, bool newLine)
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

void PrintUtils::printDaysAndTime(DaysAndTime daysAndTime, bool newLine)
{
    print(daysAndTime.GetDays());
    print(" ");
    print2digits(daysAndTime.GetHours());
    print(":");
    print2digits(daysAndTime.GetMinutes());
    print(":");
    print2digits(daysAndTime.GetSeconds());
    if (newLine)
        printNewLine();
}

void PrintUtils::printDateAndTime(DateAndTime dateAndTime, bool newLine)
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

void PrintUtils::printTimeSpan(DaysAndTime frequency, bool newLine)
{
    print("TimeSpan: [Days Hours:Minute:Seconds] = ");
    printDaysAndTime(frequency, newLine);
}

void PrintUtils::printTimeOfDay(DaysAndTime timeOfDay, bool newLine)
{
    print("TimeOfDay: [Day Hour:Minute:Second] = ");
    printDaysAndTime(timeOfDay, newLine);
}

void PrintUtils::printTriggerAndThreshold(Alarm alarm, TemperatureThreshold threshold, bool newLine)
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
