#include "DaysAndTime.h"
#include "Alarm.h"
#include <math.h>

using namespace ArduinoGetPCDateTimeUtils;

#pragma region Constructors

namespace ArduinoAlarm
{
	// Initialize static members
	DaysAndTime Alarm::TempAbove40TimeOfDay = DaysAndTime(0, 12, 0, 0);
	int Alarm::DelayInSeconds = 0;

	TemperatureThreshold TemperatureThreshold::Null = TemperatureThreshold();

	Alarm::Alarm(AlarmType type) : _type(type), _frequency(DaysAndTime::Null), _active(false), _activeThresholdIndex(-1),
		_thresholdTimeOfDayTriggerEnabled(true)
	{
		_temperatureThresholds = new TemperatureThreshold[0];
		_temperatureThresholdsCount = 0;
	}

	Alarm::Alarm(AlarmType type, DaysAndTime frequency) : _type(type), _frequency(frequency), _active(false), 
		_activeThresholdIndex(-1), _thresholdTimeOfDayTriggerEnabled(true)
	{
		_temperatureThresholds = new TemperatureThreshold[0];
		_temperatureThresholdsCount = 0;
	}

	void Alarm::SetNewTrigger(DateAndTime startDateAndTime)
	{
		SetNewTrigger(0, startDateAndTime);
	}

	void Alarm::SetNewTrigger(int temperature, DateAndTime startDateAndTime)
	{
		if (startDateAndTime.IsNull())
			DateAndTime::getCurrentDateAndTime(startDateAndTime);
		// Frequency Alarm only supports Frequency Alarm intervals (not time of day)
		if (_type == AlarmType::Frequency)
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
					if (_activeThresholdIndex == thresholdIndex &&
						threshold.TimeType == TemperatureThresholdTimeType::TimeOfDay)
					{
						// Don't set a new trigger for TimeOfDay thresholds if the threshold hasn't changed
						_thresholdTimeOfDayTriggerEnabled = false;
					}
					else
					{
						_activeThresholdIndex = thresholdIndex;
						_thresholdTimeOfDayTriggerEnabled = true;
						SetNewTrigger(threshold, startDateAndTime);
					}
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
				_triggerDateAndTime.month = startDateAndTime.month;
				_triggerDateAndTime.day = startDateAndTime.day;
				_triggerDateAndTime.year = startDateAndTime.year;
				_triggerDateAndTime.hours = (int)temperatureThreshold.Frequency.GetHours();
				_triggerDateAndTime.minutes = (int)temperatureThreshold.Frequency.GetMinutes();
				_triggerDateAndTime.seconds = (int)temperatureThreshold.Frequency.GetSeconds();
				_triggerDateAndTime.addDays(1);
				}
			else
			{
				_triggerDateAndTime = startDateAndTime;
				_triggerDateAndTime.addDays(diffTime.GetDays());
				_triggerDateAndTime.addHours(diffTime.GetHours());
				_triggerDateAndTime.addMinutes(diffTime.GetMinutes());
				_triggerDateAndTime.addSeconds(diffTime.GetSeconds());
			}
			_triggerDateAndTime.addSeconds((long)-DelayInSeconds);
		}
		else if (temperatureThreshold.TimeType == TemperatureThresholdTimeType::TimeSpan)
		{
			_triggerDateAndTime = startDateAndTime;
			_triggerDateAndTime.addDays(temperatureThreshold.Frequency.GetDays());
			_triggerDateAndTime.addHours(temperatureThreshold.Frequency.GetHours());
			_triggerDateAndTime.addMinutes(temperatureThreshold.Frequency.GetMinutes());
			_triggerDateAndTime.addSeconds(temperatureThreshold.Frequency.GetSeconds());
			if (_type != AlarmType::Frequency)
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

	void Alarm::AddTemperatureThreshold(TemperatureThreshold threshold)
	{
		// _temperatureThresholds.push_back(threshold);
		int oldCount = _temperatureThresholdsCount;
		TemperatureThreshold* newThresholds = new TemperatureThreshold[++_temperatureThresholdsCount];
		if (oldCount > 0)
		{
			for (int i = 0; i < oldCount; i++)
			{
				newThresholds[i] = _temperatureThresholds[i];
			}
		}
		delete[] _temperatureThresholds;
		newThresholds[_temperatureThresholdsCount - 1] = threshold;
		_temperatureThresholds = newThresholds;
	}

	TemperatureThreshold* Alarm::GetTemperatureThresholds(int& count)
	{
		count = _temperatureThresholdsCount;
		return _temperatureThresholds;
	}

	TemperatureThreshold Alarm::GetTemperatureThresholdAt(int index)
	{
		//if (index < 0 || index > (int)_temperatureThresholds.size() - 1)
		if (index < 0 || index >(int)_temperatureThresholdsCount - 1)
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
		//for (int index = 0; index < (int)_temperatureThresholds.size(); index++)
		for (int index = 0; index < _temperatureThresholdsCount; index++)

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
		if (_type == AlarmType::TemperatureThreshold && !_thresholdTimeOfDayTriggerEnabled)
			return false;
		DateAndTime currentTime;
		DateAndTime::getCurrentDateAndTime(currentTime);
		int seconds = currentTime.secondsTo(_triggerDateAndTime);
		if (seconds <= 0 )
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