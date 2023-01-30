#ifndef _PrintUtils_
#define _PrintUtils_ 1

// TODO: Remove inclusion of Arduino.h when running outside of the Arduino environment/compiler
#include "Arduino.h"
#include "Alarm.h"
#include "DaysAndTime.h"
#include "DateAndTime.h"

using namespace ArduinoAlarm;

namespace ArduinoPrintUtils
{
	class PrintUtils
	{
	public:
		static void print(const char* msg, bool newLine = false);
		static void print(char* msg, bool newLine = false);
		static void print(int number, bool newLine = false);
		static void print(int number, const char* format, bool newLine = false);
		static void print(long number, bool newLine = false);
		static void print(long number, const char* format, bool newLine = false);
		static void printNewLine();
		static void print2digits(int number, bool newLine = false);
		static void printTime(int hours, int minutes, int seconds, bool newLine = false);
		static void printDate(int month, int day, int year, bool newLine = false);
		static void printDaysAndTime(DaysAndTime daysAndTime, bool newLine = false);
		static void printDateAndTime(DateAndTime dateAndTime, bool newLine = false);
		static void printTimeSpan(DaysAndTime frequency, bool newLine = false);
		static void printTimeOfDay(DaysAndTime timeOfDay, bool newLine = false);
		static void printAlarmTriggerDateAndTime(Alarm alarm, bool newLine = false);
		static void printTimeType(TemperatureThresholdTimeType timeType, bool newLine = false);
		static void printTriggerAndThreshold(Alarm alarm, TemperatureThreshold threshold, bool newLine = false);
	};
}

#endif	// _PrintUtils_