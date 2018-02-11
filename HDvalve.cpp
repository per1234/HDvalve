/*
HDvalve.cpp - Library to operate with valves
Created by Tomat7, October 2017.
*/

#include "Arduino.h"
#include "HDvalve.h"

Valve::Valve(int pin)
{
#ifdef USE_PORTB_ONLY
	_pin = pin-8;
	DDRB |= (1 << _pin);
#else
	_pin = pin;
	pinMode(_pin, OUTPUT);
/*
	if (_pin < 8) { 
		_pin = pin;
		_usePortD = true;
	} else
	{ 
		_pin = pin-8;
	}
*/	
#endif

	Flow = false;
	_OnTime = 0;
	_OffTime = 0;
	Clicks = 0;
}

void Valve::init(int OffTime, byte OnTime)
{
	_OnTime = OnTime;
	_OffTime = OffTime;
	Serial.print(F(LIBVERSION));
	Serial.println(_pin);
}

void Valve::control()
{
	//unsigned long msNow = millis(); // текущее время в миллисекундах
	if ((_OnTime == 0) || (_OffTime == 0)) // не щёлкать совсем!!
	{
		Flow = false; // выключаем
		_setState();
		return;
	}

	unsigned long msPassed = millis() - _lastMillis;
	// выясняем не настал ли момент сменить состояние клапана
	if ((Flow) && (msPassed >= _OnTime))
	{
		Flow = false; // выключаем
		_setState();
		lastON = msPassed;
		Serial.print("on: ");
		Serial.println(msPassed);
		//Serial.println(currentMillis);
	}
	else if ((!Flow) && (msPassed >= _OffTime))
	{
		Flow = true; // включаем
		_setState();
		Clicks++;
		lastOFF = msPassed;
		Serial.print("off: ");
		Serial.println(msPassed);
	}
	return;
}

void Valve::setTime(int OffTime)
{
	_OffTime = OffTime;
}


void Valve::_setState()
{
#ifdef USE_PORTB_ONLY
	//if (Flow) 	{ PORTB |= _BV(_pin); }
	//else 		{ PORTB &= ~_BV(_pin); }
	if (Flow) 	{ PORTB |= 1<<_pin; }
	else 		{ PORTB &= ~(1<<(_pin)); }
/*	if (Flow)
	{
		if (_usePortD) 	{ PORTD |= 1<<_pin; }
		else 			{ PORTB |= 1<<_pin; }
	} else
	{
		if (_usePortD) 	{ PORTD &= ~(1<<_pin); }
		else 			{ PORTB &= ~(1<<(_pin)); }
	}
*/
#else
	digitalWrite(_pin, Flow); // реализуем новое состояние
#endif

	_lastMillis = millis(); // запоминаем момент времени
}


/*
void Valve::setTime(int OffTime, byte OnTime)
{
	_OnTime = OnTime;
	_OffTime = OffTime;
}
*/

/*
mlPerHour: желаемая скорость отбора мл/час
mlPerFlow: миллилитров-за-один-клик-клапана * 1000
некая расчетно-экспериментальная величина дл¤ каждого клапана
постоянная при фиксированных OnTime и высоте подвеса самого клапана!
************* !!!! не готово !!!   *********************************

void Valve::setRate(int mlPerHour, int mlPer1000Flow)
{
	_OffTime = round((3600 * mlPer1000Flow / mlPerHour) - _OnTime);
	//_OnTime = OnTime;
}
*/

