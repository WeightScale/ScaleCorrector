// CORE.h

#ifndef _CORE_h
#define _CORE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <avr/eeprom.h>
#include "CAT5171.h"

typedef struct{
	long offset  ;		//код ацп нулевой вес
	unsigned long int adc_min  ;		//код ацп ноля
	long int weight_max;				//калибровочный вес
	long int weight_min;				//вес ноль
	long int sensor_limit;		//Предельный вес датчика	
}value_t;

extern value_t EEMEM core_value_eep;
extern value_t core_value;

class CoreClass{
	
	private:
		long _adc_ofset;
		
	
	public:
		CoreClass();
		~CoreClass();
		void doPlusCalibration();
		void doMinusCalibration();
		void setAdcOfset(long a){_adc_ofset = a;};
		long getAdcOfset(){return _adc_ofset;}
	
};

extern CoreClass CORE;
extern CAT5171 POTAD0;
extern CAT5171 POTAD1;

#endif

