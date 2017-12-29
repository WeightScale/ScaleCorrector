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
	
	Wire.begin();
	POT_PLUS.setResistance(0);
	POT_MINUS.setResistance(0);

}
byte b;
void loop(){	
	
	if (remoteController.readBitsFromPort()){
		b = remoteController.getBits();
		switch(b){
			case PLUS_CALIBRATION:
				CORE.doPlusCalibration();
			break;
			case MINUS_CALIBRATION:
				CORE.doMinusCalibration();				
			break;
			case ACTION_BUTTON_A:	/*! �������� ���������� ��������� */				
				CORE.doPlus();
			break;
			case ACTION_BUTTON_B:	/*! �������� ������ ��������� */
				CORE.doMinus();
			break;
			case ACTION_BUTTON_C:
				POT_PLUS.setResistance(0);
				POT_MINUS.setResistance(0);
			break;
			case ACTION_BUTTON_D:
				POT_PLUS.shutdown();
				POT_MINUS.shutdown();
			break;
		}	
	}	

}



