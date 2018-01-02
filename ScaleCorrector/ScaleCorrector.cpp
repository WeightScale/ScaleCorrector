/*
 * ScaleCorrector.ino
 *
 * Created: 12/25/2017 9:02:01 PM
 * Author: Kostya
 */ 
#include "Arduino.h"
#include <avr/eeprom.h>
#include "CAT5171.h"
#include "WirelessRemoteController.h"
#include "HX711.h"
#include "CORE.h"

CoreClass CORE;
WirelessRemoteController remoteController;
CAT5171 POT_PLUS(CAT5171_AD0);
CAT5171 POT_MINUS(CAT5171_AD1);
Q2HX711 hx711(PIN_DATA, PIN_CLOCK);

void setup(){	
	CORE.begin();
	CORE.standart();	
}

void loop(){	
	
	if (remoteController.readBitsFromPort()){
		switch(remoteController.getBits()){
			case PLUS_CALIBRATION:			///< Войти в процесс калибровки плюсовой коррекции.
				CORE.doPlusCalibration();
			break;
			case MINUS_CALIBRATION:			///< Войти в процесс калибровки минусовой коррекции.
				CORE.doMinusCalibration();				
			break;
			case ACTION_BUTTON_A:			///< Включить додавление процентов.
				CORE.doPlus();
			break;
			case ACTION_BUTTON_B:			///< Включить снятие процениов.
				CORE.doMinus();
			break;
			case ACTION_BUTTON_C:			///< Сбросить коррекцию					
				hx711.powerUp();			
				CORE.reset();
			break;
			case ACTION_BUTTON_D:			///< Отключится от схемы
				CORE.standart();
			break;
		}	
	}
	core_value.l_adc = hx711.read();
	core_value.r = float(core_value.l_adc - core_value.offset) * core_value.factorO;
	if (core_value.r<0){
		core_value.r = abs(core_value.r);
		POT_PLUS.setResistance(0);
		POT_MINUS.setResistance(core_value.r);
	}else{
		POT_PLUS.setResistance(core_value.r);
		POT_MINUS.setResistance(0);
	}
}





