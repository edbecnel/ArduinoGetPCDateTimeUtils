#ifndef _DateAndTime_
#define _DateAndTime_ 1

typedef unsigned char byte;

namespace ArduinoGetPCDateTimeUtils
{
    class DateAndTime
    {
    public:
        DateAndTime();
        DateAndTime(int monthVal, int dayVal, int yearVal, int hoursVal, int minutesVal, int secondsVal);
        int month;
        int day;
        int year;
        int hours;
        int minutes;
        int seconds;
        bool getCompileDateAndTime();
        void addSeconds(int seconds);
        void addMinutes(int minutes);
        void addHours(int hours);
        void addDays(int days);
        void addTime(int days, int hours, int minutes, int seconds);
        char* toString();
    private:
        char toStringBuffer[20];
    };

    class DateAndTimeBytes
    {
    public:
        DateAndTimeBytes();
        DateAndTimeBytes(byte monthVal, byte dayVal, byte yearVal, byte hoursVal, byte minutesVal, byte secondsVal);
        DateAndTimeBytes(const DateAndTime&);
        byte month;
        byte day;
        byte year;
        byte hours;
        byte minutes;
        byte seconds;
        bool getCompileDateAndTime();
        void addSeconds(byte seconds);
        void addMinutes(byte minutes);
        void addHours(byte hours);
        void addDays(byte days);
        void addTime(byte days, byte hours, byte minutes, byte seconds);
        void convertToDateAndTime(DateAndTime&);
        void convertDateAndTimeToBytes(const DateAndTime&);
        char* toString();
    private:
        char toStringBuffer[18];
    };
}
#endif  // _DateAndTime
