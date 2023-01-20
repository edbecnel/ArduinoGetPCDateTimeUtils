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
        DateAndTime();
        DateAndTime(int monthVal, int dayVal, int yearVal, int hoursVal, int minutesVal, int secondsVal);
        DateAndTime(const DateAndTime& dateAndTime);
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
        static DateAndTime* getCurrentDateAndTime();
        static void setGetCurrentDateAndTimeFunction(DateAndTime*(*func)());
        typedef DateAndTime* (*GetCurrentDateAndTimeHanlderFunc)();
    private:
        static GetCurrentDateAndTimeHanlderFunc currentDateAndTimeHandler;
    };

    class DateAndTimeBytes
    {
    public:
        DateAndTimeBytes();
        DateAndTimeBytes(byte monthVal, byte dayVal, byte yearVal, byte hoursVal, byte minutesVal, byte secondsVal);
        DateAndTimeBytes(const DateAndTime&);
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
        static DateAndTimeBytes* getCurrentDateAndTime();
    };
}
#endif  // _DateAndTime
