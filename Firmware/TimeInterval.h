/*
	TimeInterval.h - Library replacement for delay function
	Created by Kriz Jade C. Garino, September 9, 2017.
*/

#ifndef TimeInterval_h
#define TimeInterval_h
#include "Arduino.h"

class TimeInterval{
	public:
		TimeInterval();
		void duration(unsigned long interval);
	private:
		unsigned long _prevMillis;
		unsigned long _currentMillis;
		unsigned long _interval;
};

#endif