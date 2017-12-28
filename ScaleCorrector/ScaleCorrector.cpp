#include "Arduino.h"
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

WirelessRemoteController remoteController = WirelessRemoteController();

CAT5171 POTAD0(CAT5171_AD0);
CAT5171 POTAD1(CAT5171_AD1);

Q2HX711 hx711(PIN_DATA, PIN_CLOCK);
uint8_t i0 = 1, i1 = 1;

void setup(){
		
	Wire.begin();
	POTAD0.shutdown();
	POTAD1.shutdown();
	
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
				//CORE.doMinusCalibration();
				POTAD0.setResistance(--i0);				
			break;
			case ACTION_BUTTON_A:	/*! Включить додавление процентов */
				POTAD0.setResistance(150);
				POTAD1.setResistance(128);
			break;
			case ACTION_BUTTON_B:	/*! Включить снятие процениов */	
				POTAD0.setResistance(128);
				POTAD1.setResistance(106);
			break;
			case ACTION_BUTTON_C:
				POTAD0.shutdown();
				POTAD1.shutdown();
			break;
			case ACTION_BUTTON_D:
				POTAD0.setResistance(i0=1);
				POTAD1.setResistance(i1=1);
			break;
		}	
	}	

	//delay(100);	

}



