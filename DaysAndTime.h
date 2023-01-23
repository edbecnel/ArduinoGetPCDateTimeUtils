#ifndef _DayAndTime_
#define _DayAndTime_ 1

typedef unsigned char byte;

namespace ArduinoGetPCDateTimeUtils
{
    class DaysAndTime
    {
    public:
        static DaysAndTime Null;
        DaysAndTime();
        DaysAndTime(long days, long hours, long minutes, long seconds, bool normalize = false);
        void Set(long days, long hours, long minutes, long seconds, bool normalize = false);
        long GetDays();
        void SetDays(long days);
        long GetHours();
        void SetHours(long hours);
        long GetMinutes();
        void SetMinutes(long minutes);
        long GetSeconds();
        void SetSeconds(long seconds);
        long GetTotalTimeInSeconds();
        void Normalize();
        void Reset();
        bool IsNull();
        bool IsNormalized();
        bool IsEqualTo(DaysAndTime otherDayAndTime);
    private:
        double _remainder(double _x, double _y);
        long _days;
        long _hours;
        long _minutes;
        long _seconds;
        bool _isNull;
        bool _isNormalized;
    };
}

#endif  // _DayAndTime_