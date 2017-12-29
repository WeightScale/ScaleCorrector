#include "Arduino.h"
#include <avr/eeprom.h>
#include "CAT5171.h"
#include "WirelessRemoteController.h"
#include "HX711.h"
#include "CORE.h"
/*
 * ScaleCorrector.ino
 *
 * Created: 12/25/2017 9:02:01 PM
 * Author: Kostya
 */ 
CoreClass CORE;
WirelessRemoteController remoteController;

CAT5171 POT_PLUS(CAT5171_AD0);
CAT5171 POT_MINUS(CAT5171_AD1);

Q2HX711 hx711(PIN_DATA, PIN_CLOCK);
uint8_t i0 = 1, i1 = 1;

void setup(){
	
	eeprom_read_block (&core_value, &core_value_eep, sizeof(value_t));
	//hx711.powerDown();	
	
	Wire.begin();
	POT_PLUS.setResistance(0);
	POT_MINUS.setResistance(0);
	//CORE.begin();
	//((value_t*)core_value)->offset = (long*)&CORE._adc_ofset;
	
	  /* add setup code here, setup code runs once when the processor starts */

}
byte b;
void loop(){	
	
	if (remoteController.readBitsFromPort()){
		b = remoteController.getBits();
		switch(b){
			case PLUS_CALIBRATION:
				CORE.doPlusCalibration();
				//i0 = potAD0.getResistance();
				//i1 = potAD1.getResistance();
			break;
			case MINUS_CALIBRATION:
				CORE.doMinusCalibration();
				//CORE.doMinusCalibration();
				//POTAD0.setResistance(--i0);				
			break;
			case ACTION_BUTTON_A:	/*! Включить додавление процентов */
				//POTAD0.setResistance(150);
				//POTAD1.setResistance(128);
				CORE.doPlus();
			break;
			case ACTION_BUTTON_B:	/*! Включить снятие процениов */
				CORE.doMinus();
				//POT_PLUS.setResistance(128);
				//POT_MINUS.setResistance(150);
			break;
			case ACTION_BUTTON_C:
				//POTAD0.shutdown();
				//POTAD1.shutdown();
				POT_PLUS.setResistance(0);
				POT_MINUS.setResistance(0);
			break;
			case ACTION_BUTTON_D:
				POT_PLUS.shutdown();
				POT_MINUS.shutdown();
			break;
		}	
	}	

	//delay(100);	

}



