#include "DaysAndTime.h"
#include "Alarm.h"
#include <math.h>

using namespace ArduinoGetPCDateTimeUtils;

#pragma region Constructors

namespace ArduinoAlarm
{
	// Initialize static members
	DaysAndTime Alarm::TempAbove40TimeOfDay = DaysAndTime(0, 12, 0, 0);
	int Alarm::DelayInSeconds = 55;

	TemperatureThreshold TemperatureThreshold::Null = TemperatureThreshold();

	Alarm::Alarm(AlarmType type) : _type(type), _frequency(DaysAndTime::Null), _active(false), _activeThresholdIndex(-1)
	{
	}

	Alarm::Alarm(AlarmType type, vector<TemperatureThreshold> thresholds) : _type(type), _temperatureThresholds(thresholds),
		_frequency(DaysAndTime::Null), _active(false), _activeThresholdIndex(-1)
	{
	}

	Alarm::Alarm(AlarmType type, vector<TemperatureThreshold> thresholds, DaysAndTime frequency) : _type(type),
		_temperatureThresholds(thresholds), _frequency(frequency), _active(false), _activeThresholdIndex(-1)
	{
	}

	Alarm::Alarm(AlarmType type, DaysAndTime frequency) : _type(type), _frequency(frequency), _active(false), _activeThresholdIndex(-1)
	{
	}

	void Alarm::SetNewTrigger(DateAndTime startDateAndTime)
	{
		SetNewTrigger(0, startDateAndTime);
	}

	void Alarm::SetNewTrigger(int temperature, DateAndTime startDateAndTime)
	{
		if (startDateAndTime.IsNull())
			DateAndTime::getCurrentDateAndTime(startDateAndTime);
		// Debug Alarm only supports Frequency Alarm intervals (not time of day)
		if (_type == AlarmType::Debug)
		{
			_triggerDateAndTime = startDateAndTime;
			_triggerDateAndTime.addDays(_frequency.GetDays());
			_triggerDateAndTime.addHours(_frequency.GetHours());
			_triggerDateAndTime.addMinutes(_frequency.GetMinutes());
			_triggerDateAndTime.addSeconds(_frequency.GetSeconds());
		}
		else if (_type == AlarmType::TemperatureThreshold)
		{
			// For temperature range alarm type, get temperatureThreshold for new temperature
			int thresholdIndex = GetThresholdIndexForTemperature(temperature);
			if (thresholdIndex > -1)
			{
				TemperatureThreshold threshold = GetTemperatureThresholdAt(thresholdIndex);
				if (!threshold.IsNull())
				{
					_activeThresholdIndex = thresholdIndex;
					SetNewTrigger(threshold, startDateAndTime);
				}
			}
		}
	}

	void Alarm::SetNewTrigger(TemperatureThreshold temperatureThreshold, DateAndTime startDateAndTime)
	{
		if (startDateAndTime.IsNull())
			DateAndTime::getCurrentDateAndTime(startDateAndTime);
		if (temperatureThreshold.TimeType == TemperatureThresholdTimeType::TimeOfDay)
		{
			DaysAndTime diffTime(0, 0, 0, 0);
			// Attempt to set trigger time based on time of day.
			// Use startDateAndTime for month, day, and year
			DateAndTime triggerDateAndTime(startDateAndTime.month, startDateAndTime.day, startDateAndTime.year,
				(int)temperatureThreshold.Frequency.GetHours(), (int)temperatureThreshold.Frequency.GetMinutes(), 
				(int)temperatureThreshold.Frequency.GetSeconds());
			startDateAndTime.getDaysHoursMinutesSecondsTo(triggerDateAndTime, diffTime);
			// If the time difference is <= 0 , then we need to advance the day by 1 and get a new diffTime that is positive
			if (diffTime.GetTotalTimeInSeconds() <= 0)
			{
				triggerDateAndTime.month = startDateAndTime.month;
				triggerDateAndTime.day = startDateAndTime.day;
				triggerDateAndTime.year = startDateAndTime.year;
				triggerDateAndTime.hours = (int)temperatureThreshold.Frequency.GetHours();
				triggerDateAndTime.minutes = (int)temperatureThreshold.Frequency.GetMinutes();
				triggerDateAndTime.seconds = (int)temperatureThreshold.Frequency.GetSeconds();
				triggerDateAndTime.addDays(1);
				startDateAndTime.getDaysHoursMinutesSecondsTo(triggerDateAndTime, diffTime);
			}
			_triggerDateAndTime = startDateAndTime;
			_triggerDateAndTime.addDays(diffTime.GetDays());
			_triggerDateAndTime.addHours(diffTime.GetHours());
			_triggerDateAndTime.addMinutes(diffTime.GetMinutes());
			_triggerDateAndTime.addSeconds(diffTime.GetSeconds());
			_triggerDateAndTime.addSeconds((long)-DelayInSeconds);
		}
		else if (temperatureThreshold.TimeType == TemperatureThresholdTimeType::TimeSpan)
		{
			_triggerDateAndTime = startDateAndTime;
			_triggerDateAndTime.addDays(_frequency.GetDays());
			_triggerDateAndTime.addHours(_frequency.GetHours());
			_triggerDateAndTime.addMinutes(_frequency.GetMinutes());
			_triggerDateAndTime.addSeconds(_frequency.GetSeconds());
			if (_type != AlarmType::Debug)
				_triggerDateAndTime.addSeconds(-DelayInSeconds);
		}
	}

	void Alarm::Start(int temperature, DateAndTime startDateAndTime)
	{
		if (_frequency.IsNull())
		{
			SetActive(false);
			return;
		}
		SetActive(true);
		SetNewTrigger(temperature, startDateAndTime);
	}

	void Alarm::Stop()
	{
		SetActive(false);
	}

	bool Alarm::GetActive()
	{
		return _active;
	}

	void Alarm::SetActive(bool active)
	{
		_active = active;
	}

	DaysAndTime Alarm::GetFrequency()
	{
		return _frequency;
	}

	void Alarm::SetFrequency(DaysAndTime frequency)
	{
		_frequency = frequency;
	}

	DateAndTime Alarm::GetTriggerDateAndTime()
	{
		return _triggerDateAndTime;
	}

	AlarmType Alarm::GetType()
	{
		return _type;
	}

	void Alarm::SetType(AlarmType type)
	{
		// Alarm must not be Active to set its Type
		if (GetActive())
		{
			Stop();
		}
		_type = type;
	}

	void Alarm::SetTemperatureThresholds(vector<TemperatureThreshold> thresholds)
	{
		_temperatureThresholds = thresholds;
	}

	void Alarm::AddTemperatureThreshold(TemperatureThreshold threshold)
	{
		_temperatureThresholds.push_back(threshold);
	}

	vector<TemperatureThreshold> Alarm::GetTemperatureThresholds()
	{
		return _temperatureThresholds;
	}

	TemperatureThreshold Alarm::GetTemperatureThresholdAt(int index)
	{
		if (index < 0 || index > (int)_temperatureThresholds.size() - 1)
			return TemperatureThreshold::Null;
		return _temperatureThresholds[index];
	}

	int Alarm::GetThresholdIndexForTemperature(int temperature)
	{
		if (GetType() != AlarmType::TemperatureThreshold)
			return -1;
		int lowestThresholdTemperature = 999;
		int lowestThresholdIndex = -1;
		int highestThresholdTemperature = -999;
		int highestThresholdIndex = -1;
		for (int index = 0; index < (int)_temperatureThresholds.size(); index++)
		{
			TemperatureThreshold threshold(_temperatureThresholds[index]);
			switch (threshold.Type)
			{
			case TemperatureThresholdType::IsEqual:
				if (temperature != threshold.Temperature)
					return index;
				break;
			case TemperatureThresholdType::Above:
				if (temperature > threshold.Temperature)
				{
					if (threshold.Temperature > highestThresholdTemperature)
					{
						highestThresholdTemperature = threshold.Temperature;
						highestThresholdIndex = index;
					}
				}
				break;
			case TemperatureThresholdType::Below:
				if (temperature < threshold.Temperature)
				{
					if (threshold.Temperature < lowestThresholdTemperature)
					{
						lowestThresholdTemperature = threshold.Temperature;
						lowestThresholdIndex = index;
					}
				}
				break;
			}
		}
		if (lowestThresholdIndex > -1)
			return lowestThresholdIndex;
		return highestThresholdIndex;
	}

	TemperatureThreshold Alarm::GetThresholdForTemperature(int temperature)
	{
		TemperatureThreshold threshold;

		if (GetType() != AlarmType::TemperatureThreshold)
			return TemperatureThreshold::Null;

		int index = GetThresholdIndexForTemperature(temperature);
		if (index > -1)
		{
			threshold = GetTemperatureThresholdAt(index);
			return threshold;
		}

		return TemperatureThreshold::Null;
	}

	bool Alarm::IsTriggered()
	{
		if (!_active)
			return false;
		DateAndTime currentTime;
		DateAndTime::getCurrentDateAndTime(currentTime);
		if (currentTime.secondsTo(_triggerDateAndTime) <= 0)
			return true;
		return false;
	}

	bool Alarm::IsKindOf(AlarmType type)
	{
		return IsKindOf(_type, type);
	}

	bool Alarm::IsKindOf(AlarmType typeToCheck, AlarmType isType)
	{
		AlarmType checkType = (AlarmType)((int)typeToCheck & (int)isType);
		return checkType == isType ? true : false;
	}

	bool Alarm::TemperatureThresholdCrossed(int currTemperature)
	{
		int currIndex = GetThresholdIndexForTemperature(currTemperature);
		return (currIndex != _activeThresholdIndex) ? true : false;
	}

	bool Alarm::TypesAreDifferent(Alarm alarm1, Alarm alarm2)
	{
		if (alarm1.GetType() != alarm2.GetType())
			return true;
		return false;
	}
}