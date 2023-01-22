#ifndef _DateAndTime_
#define _DateAndTime_ 1

#include <stdio.h>
#include "DaysAndTime.h"

typedef unsigned char byte;

namespace ArduinoGetPCDateTimeUtils
{
    class DateAndTime
    {
    public:
        static DateAndTime Null;

        DateAndTime();
        DateAndTime(int monthVal, int dayVal, int yearVal, int hoursVal, int minutesVal, int secondsVal);
        DateAndTime(const DateAndTime& dateAndTime);
        DateAndTime(DateAndTime* dateAndTimePtr);
        bool IsNull();
        long secondsTo(DateAndTime& otherDateTime);
        void getDaysHoursMinutesSecondsTo(DateAndTime& otherDateTime, long& days, long& hours, long& minutes, long& seconds);
        void getDaysHoursMinutesSecondsTo(DateAndTime& otherDateTime, DaysAndTime& daysAndTime);
        bool getCompileDateAndTime();
        void addSeconds(int seconds);
        void addMinutes(int minutes);
        void addHours(int hours);
        void addDays(int days);
        void addMonths(int months);
        void addYears(int years);
        void addTime(int years, int months, int days, int hours, int minutes, int seconds);
        int month;
        int day;
        int year;
        int hours;
        int minutes;
        int seconds;
        static void getCurrentDateAndTime(DateAndTime&);
        static void setGetCurrentDateAndTimeFunction(void(*func)(DateAndTime&));
        typedef void (*GetCurrentDateAndTimeHanlderFunc)(DateAndTime&);
    private:
        static GetCurrentDateAndTimeHanlderFunc currentDateAndTimeHandler;
    };

    class DateAndTimeBytes
    {
    public:
        static DateAndTimeBytes Null;

        DateAndTimeBytes();
        DateAndTimeBytes(byte monthVal, byte dayVal, byte yearVal, byte hoursVal, byte minutesVal, byte secondsVal);
        DateAndTimeBytes(const DateAndTime&);
        bool IsNull();
        long secondsTo(DateAndTimeBytes& otherDateTimeBytes);
        void getDaysHoursMinutesSecondsTo(DateAndTimeBytes& otherDateTimeBytes, long& days, long& hours, long& minutes, long& seconds);
        void getDaysHoursMinutesSecondsTo(DateAndTimeBytes& otherDateTime, DaysAndTime& daysAndTime);
        bool getCompileDateAndTime();
        void addSeconds(byte seconds);
        void addMinutes(byte minutes);
        void addHours(byte hours);
        void addDays(byte days);
        void addMonths(byte months);
        void addYears(byte years);
        void addTime(byte years, byte months, byte days, byte hours, byte minutes, byte seconds);
        void convertToDateAndTime(DateAndTime&);
        void convertDateAndTimeToBytes(const DateAndTime&);
        byte month;
        byte day;
        byte year;
        byte hours;
        byte minutes;
        byte seconds;
        static void getCurrentDateAndTime(DateAndTimeBytes&);
        static void convertDateAndTimeToBytes(const DateAndTime& dateAndTime, DateAndTimeBytes& dateAndTimeBytes);
    };
}
#endif  // _DateAndTime
