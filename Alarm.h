#ifndef _Alarm_
#define _Alarm_ 1

#include "DateAndTime.h"
#include "DaysAndTime.h"


using namespace ArduinoGetPCDateTimeUtils;
using namespace std;

namespace ArduinoAlarm
{
    enum class TemperatureThresholdType
    {
        None = 0,
        Above = 1,
        Below = 2,
        IsEqual
    };

    enum class TemperatureThresholdTimeType
    {
        None = 0,
        TimeOfDay = 1,
        TimeSpan = 2
    };

    class TemperatureThreshold
    {
    public: 
        TemperatureThreshold() :
            Temperature(0), Type(TemperatureThresholdType::None), TimeType(TemperatureThresholdTimeType::None),
            Frequency(DaysAndTime(0, 0, 0, 0))
        {}

        TemperatureThreshold(int temperature, TemperatureThresholdType type, TemperatureThresholdTimeType timeType, DaysAndTime frequency) :
            Temperature(temperature), Type(type), TimeType(timeType), Frequency(frequency)
        {}

        static TemperatureThreshold Null;
        bool IsNull()
        {
            if (Type == TemperatureThresholdType::None)
                return true;
            return false;
        }
        int Temperature;    // Degrees Fahrenheit
        TemperatureThresholdType Type;
        TemperatureThresholdTimeType TimeType;
        DaysAndTime Frequency;
    };

    enum class AlarmType
    {
        None = 0,
        TemperatureThreshold = 1,
        Debug = 2
    };

    class Alarm
    {
    public:
        static DaysAndTime TempAbove40TimeOfDay;
        static int DelayInSeconds;
        static int DebugFrequencyInSeconds;

        Alarm(AlarmType type = AlarmType::None);
        Alarm(AlarmType type, DaysAndTime frequency);

        void SetNewTrigger(DateAndTime startDateAndTime = DateAndTime::Null);
        void SetNewTrigger(int temperature, DateAndTime startDateAndTime = DateAndTime::Null);
        void SetNewTrigger(TemperatureThreshold temperatureThreshold, DateAndTime startDateAndTime = DateAndTime::Null);
        void Start(int temperature = 0, DateAndTime startDateAndTime = DateAndTime::Null);
        void Stop();
        bool GetActive();
        void SetActive(bool active);

        DaysAndTime GetFrequency();
        void SetFrequency(DaysAndTime frequency);
        DateAndTime GetTriggerDateAndTime();
        AlarmType GetType();
        void SetType(AlarmType type);

        void AddTemperatureThreshold(TemperatureThreshold threshold);
        TemperatureThreshold* GetTemperatureThresholds(int& count);
        TemperatureThreshold GetTemperatureThresholdAt(int index);

        int GetThresholdIndexForTemperature(int temperature);
        TemperatureThreshold GetThresholdForTemperature(int temperature);
        bool IsTriggered();
        bool IsKindOf(AlarmType type);
        bool TemperatureThresholdCrossed(int currTemperature);

        static bool IsKindOf(AlarmType typeToCheck, AlarmType isType);
        static bool TypesAreDifferent(Alarm alarm1, Alarm alarm2);

    private:
        bool _active;
        DaysAndTime _frequency;
        DateAndTime _triggerDateAndTime;
        AlarmType _type;
        TemperatureThreshold* _temperatureThresholds;
        int _temperatureThresholdsCount;
        int _activeThresholdIndex;
    };
}

#endif  // _Alarm_