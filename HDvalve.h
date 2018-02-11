/*
HDvalve.h - Library to control valves.
Created by Tomat7, October 2017.
Released into the public domain.
*/
#ifndef HDvalve_h
#define HDvalve_h

#include "Arduino.h"
//#include <EtherCard.h>

#define LIBVERSION "HDvalve_v20180120 on pin "
#define DEBUG5
//#define USE_PORTB_ONLY

class Valve 
{
public:
	// конструктор создает экземпляр Valve и инициализирует 
	// переменные-члены класса и состояние
	// максимальное время открытия 255 мсек !! 
	// если надо больше - ниже и в .cpp нужно byte заменить на int
	Valve(int pin);
	boolean Flow;    // признак клапан открыт (HIGH = TRUE = открыт)
	byte lastON;	
	int lastOFF;
	unsigned int Clicks;
	void control();			// функция для регулярного вызова - она и управялет клапаном
	void init(int OffTime, byte OnTime); // задаём временные интервалы в миллисекундах!
	void setTime(int OffTime);		// задаём временные интервалы в миллисекундах!
	//
	// void setTime(int OffTime, byte OnTime);	// типа так и не понадобилось
	//
	// void setRate(int mlPerHour, int mlPer1000Click); // ******* не сделано !! *******
	// задаём скорость отбора 
	// mlPerHour: желаемая скорость отбора [мл/час]
	// mlPer1000Click: миллилитров-за-тысячу-кликов-клапана [мл/клик * 1000]
	// это расчетно-экспериментальная величина (коэффициент) для каждого клапана
	// полученная для определенного OnTime при "фиксированной" высоте подвеса клапана.
	// OnTime при которой получена/расчитана эта величина задается отдельно.
private:
	int _pin;					// номер управл€ющего пина 
	unsigned long _lastMillis; // последний момент смены состо€ни€
	byte _OnTime; 				// если надо больше 255 мсек - int
	int _OffTime; 				// врем€ поко€ в миллисекундах
	void _setState();
//	bool _usePortD = false;
};
#endif
