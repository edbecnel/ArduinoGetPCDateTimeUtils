#include "DaysAndTime.h"
#include <math.h>

using namespace ArduinoGetPCDateTimeUtils;

#pragma region Constructors

DaysAndTime::DaysAndTime() : _days(0), _hours(0), _minutes(0), _seconds(0)
{
    _isNull = true;
    _isNormalized = false;
}

DaysAndTime::DaysAndTime(long days, long hours, long minutes, long seconds, bool normalize) :
    _days(days), _hours(hours), _minutes(minutes), _seconds(seconds)
{
    _isNull = false;
    _isNormalized = normalize;
    if (normalize)
        Normalize();
}

#pragma endregion Constructor

#pragma region Private Methods

void DaysAndTime::Normalize()
{
    _isNormalized = true;
    if (_seconds > 59)
    {
        double minutes = (double)_seconds / 60.0;
        _minutes += (long)floor(minutes);
        double seconds = round(remainder(minutes, floor(minutes)) * 60.0);
        _seconds = (long)seconds;
    }
    if (_minutes > 59)
    {
        double hours = (double)_minutes / 60.0;
        _hours += (long)floor(hours);
        double minutes = round(remainder(hours, floor(hours)) * 60.0);
        _minutes = (long)minutes;
    }
    if (_hours > 23)
    {
        double days = (double)_hours / 24.0;
        _days += (long)floor(days);
        double hours = round(remainder(days, floor(days)) * 24.0);
        _hours = (long)hours;
    }
}

#pragma endregion Private Methods

#pragma region Public Getters and Setters

long DaysAndTime::GetDays()
{
    return _days;
}

void DaysAndTime::SetDays(long days)
{
    _days = days;
    _isNull = false;
    if (_isNormalized)
        Normalize();
}

long DaysAndTime::GetHours()
{
    return _hours;
}

void DaysAndTime::SetHours(long hours)
{
    _hours = hours;
    _isNull = false;
    if (_isNormalized)
        Normalize();
}

long DaysAndTime::GetMinutes()
{
    return _minutes;
}

void DaysAndTime::SetMinutes(long minutes)
{
    _minutes = minutes;
    _isNull = false;
    if (_isNormalized)
        Normalize();
}

long DaysAndTime::GetSeconds()
{
    return _seconds;
}

void DaysAndTime::SetSeconds(long seconds)
{
    _seconds = seconds;
    _isNull = false;
    if (_isNormalized)
        Normalize();
}

void DaysAndTime::Reset()
{
    _days = _hours = _minutes = _seconds = 0;
    _isNull = true;
}

bool DaysAndTime::IsNull()
{
    return _isNull;
}

bool DaysAndTime::IsNormalized()
{
    return _isNormalized;
}

#pragma endregion Public Getters and Setters