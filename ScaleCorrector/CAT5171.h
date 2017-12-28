// CAT5171.h

#ifndef _CAT5171_h
#define _CAT5171_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Wire.h>

class CAT5171{
	private:
	int _addr;
	
	public:
	CAT5171();
	CAT5171(int addr);
	void setResistance(uint8_t);
	uint8_t getResistance();
	void begin();
	void shutdown();
	void reset();
	
};


#define CAT5171_AD0 0x2C /*! ����� AD0 ��������� CAT5171  */
#define CAT5171_AD1 0x2D /*! ����� AD1 ��������� CAT5171  */

#define CAT5171_SHUTDOWN	0x20
#define CAT5171_RESET		0x40

#endif

