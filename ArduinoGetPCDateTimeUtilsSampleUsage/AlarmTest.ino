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

void print2digits(int number)
{
    char buffer[5];
    sprintf(buffer, "%02d",number);
    Serial.print(buffer);
}

void GetCurrentDateAndTime(DateAndTime& dateAndTime)
{
    // TODO: Replace the implementation of this function with getting the current time from the RTCZero board
    dateAndTime.month = currentTime.month;
    dateAndTime.day = currentTime.day;
    dateAndTime.year = currentTime.year;
    dateAndTime.hours = currentTime.hours;
    dateAndTime.minutes = currentTime.minutes;
    dateAndTime.seconds = currentTime.seconds;
}

int GetCurrentTemperature()
{
    // Keep this code
    DateAndTime::getCurrentDateAndTime(currentTime);
    long elapsedSeconds = abs(startTime.secondsTo(currentTime));
    // End: Keep this code

    // TODO: *** Replace the following lines of code to get the current temperature from the Arduino board that senses temperature
    if (elapsedSeconds < 32)
    {
        currTemperature = 41;
    }
    else if (elapsedSeconds < 63)
    {
        currTemperature = 40;
    }
    else if (elapsedSeconds < 94)
    {
        currTemperature = 31;
    }
    else
    {
        currTemperature = 41;
    }
    // TODO: *** End code replacement

    // Keep the following code
    if (elapsedSeconds > seconds || currTemperature != prevTemperature)
    {
        seconds = elapsedSeconds;

        Serial.print("Temperature = ");
        //printf("Time = % 02d: % 02d : % 02d\n", currTemperature, currTime.hours, currTime.minutes, currTime.seconds);
        Serial.print(currTemperature);
        Serial.print(" Time = ");
        print2digits(currentTime.hours);
        Serial.print(":");
        print2digits(currentTime.minutes);
        Serial.print(":");
        print2digits(currentTime.seconds);
        Serial.println();

        prevTemperature = currTemperature;
    }
    return currTemperature;
}

void setup() 
{
    Serial.begin(115200);

    delay(3000);
    Serial.println ("************ Start Alarm Test ************");

    DateAndTime::setGetCurrentDateAndTimeFunction(&GetCurrentDateAndTime);

    // TODO: *** Remove the following code after properly implementing GetCurrentDateAndTime() to get the date and time from the RTCZero board
    currentTime = DateAndTime(1, 23, 2023, 13, 0, 0);

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


    // Temperature Alarm
    // Above 40 threshold. Alarm triggered on TimeOfDay
    DateAndTime currTime;
    DateAndTime::getCurrentDateAndTime(currTime);
    currTime.addSeconds(30);
    DaysAndTime above40TimeOfDay(0, currTime.hours, currTime.minutes, currTime.seconds);
    TemperatureThreshold threshold(40, TemperatureThresholdType::Above, TemperatureThresholdTimeType::TimeOfDay, above40TimeOfDay);
    alarms[1] = Alarm(AlarmType::TemperatureThreshold, frequency);
    alarms[1].AddTemperatureThreshold(threshold);

    // Below 41 threshold. Alarm triggered on TimeOfDay
    currTime.addSeconds(30);
    DaysAndTime below41TimeOfDay(0, currTime.hours, currTime.minutes, currTime.seconds);
    threshold.Temperature = 41;
    threshold.Type = TemperatureThresholdType::Below;
    // threshold.TimeType = TemperatureThresholdTimeType::TimeSpan;
    // frequency.Set(0, 1, 0, 0);  // Once per hour
    // threshold.Frequency = frequency;
    threshold.TimeType = TemperatureThresholdTimeType::TimeOfDay;
    threshold.Frequency = below41TimeOfDay;
    alarms[1].AddTemperatureThreshold(threshold);

    // Below 32 threshold. Alarm triggered by frequency (e.g. every 15 minutes, every 15 seconds. etc.)
    threshold.Temperature = 32;
    threshold.TimeType = TemperatureThresholdTimeType::TimeSpan;
    // frequency.Set(0, 0, 15, 0);  // Once every 15 minutes
    frequency.Set(0, 0, 0, 15);     // Once every 15 seconds
    threshold.Frequency = frequency;
    alarms[1].AddTemperatureThreshold(threshold);

    alarms[0].Start();
    int temperature = GetCurrentTemperature();
    alarms[1].Start(temperature);
}

void loop() 
{
    if (alarms[0].IsTriggered())
    {
        Serial.println("Frequency Alarm 0 triggered");
        alarms[0].SetNewTrigger();
    }
    int temperature = GetCurrentTemperature();
    if (alarms[1].IsTriggered())
    {
        Serial.println("Temperature Threshold Alarm 1 triggered");
        alarms[1].SetNewTrigger(temperature);
    }
    if (alarms[1].TemperatureThresholdCrossed(temperature))
    {
        Serial.println("Temperature Threshold Crossed - Set New Trigger for Alarm 1");
        alarms[1].SetNewTrigger(temperature);
    }
    // TODO: *** Remove this when using a real clock and temperature sensor
    delay(loopTimeDelaySeconds * 1000);  // Needed to mock up time since GetCurrentDateAndTime simple ticks up 1 second on each loop (delay is in milliseconds)
    currentTime.addSeconds(1); 
}
