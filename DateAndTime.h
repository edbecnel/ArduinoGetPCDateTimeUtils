#ifndef _DateAndTime_
#define _DateAndTime_ 1

typedef unsigned char byte;

namespace ArduinoGetPCDateTimeUtils
{
    class DateAndTime
    {
    public:
        DateAndTime();
        int day;
        int month;
        int year;
        int hours;
        int minutes;
        int seconds;
        bool getCompileDateAndTime();
    };

    class DateAndTimeBytes
    {
    public:
        DateAndTimeBytes();
        byte day;
        byte month;
        byte year;
        byte hours;
        byte minutes;
        byte seconds;
        bool getCompileDateAndTime();
        void convertDateAndTimeToBytes(const DateAndTime&);
    };
}

#endif  // _DateAndTime
