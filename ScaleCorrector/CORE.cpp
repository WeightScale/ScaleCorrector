
#include "CORE.h"
#include "WirelessRemoteController.h"
#include "HX711.h"

value_t EEMEM core_value_eep;
value_t core_value;// = {&CORE._adc_ofset, 0, 0};



CoreClass::CoreClass(){	
};
	
CoreClass::~CoreClass(){};

void CoreClass::begin(){
}	

/*! Функция калибровки плюсового значения*/
void CoreClass::doPlusCalibration(){
	long l_adc;
	unsigned char p0 = 0;
	POT_PLUS.setResistance(2);
	POT_MINUS.setResistance(0);	
	delay(500);
	POT_PLUS.setResistance(0);
	delay(100);
	core_value.offset = hx711.read();
	while(1){
		if (remoteController.readBitsFromPort()){
			
			switch(remoteController.getBits()){
				case ACTION_BUTTON_A:	/*! Добатить вес*/
					if(p0 < 255){
						POT_PLUS.setResistance(++p0);	
					}	
				break;
				case ACTION_BUTTON_B:	/*! Отнять вес*/
					if(p0 > 0){
						POT_PLUS.setResistance(--p0);	
					}										
				break;
				case ACTION_BUTTON_C:	/*! Выйти и сохранить результат салибровки*/
					{
						core_value.r = POT_PLUS.getResistance();
						core_value.l_adc = hx711.read();
						POT_PLUS.setResistance(0);
						core_value.factorP = ((float)core_value.l_adc - (float)core_value.offset) / (float)core_value.r;
						eeprom_update_block (&core_value, &core_value_eep, sizeof(value_t));
						
						goto calout;
					}
				break;
				case ACTION_BUTTON_D:	/*! Выйти без сохранения */
					goto calout;
				break;
			}
		}
	}
	calout: ;
}

/*! Функция калибровки минусового значения*/
void CoreClass::doMinusCalibration(){
	long l_adc;
	unsigned char p1 = 0;
	POT_PLUS.setResistance(0);
	POT_MINUS.setResistance(2);
	delay(500);
	POT_MINUS.setResistance(0);
	delay(100);
	core_value.offset = hx711.read();
	while(1){
		if (remoteController.readBitsFromPort()){
		
			switch(remoteController.getBits()){
				case ACTION_BUTTON_A:	/*! Добатить вес*/
				if(p1 < 255){
					POT_MINUS.setResistance(++p1);
				}
				break;
				case ACTION_BUTTON_B:	/*! Отнять вес*/
				if(p1 > 0){
					POT_MINUS.setResistance(--p1);
				}
				break;
				case ACTION_BUTTON_C:	/*! Выйти и сохранить результат салибровки*/
				{
					core_value.r = POT_MINUS.getResistance();
					core_value.l_adc = hx711.read();
					POT_MINUS.setResistance(0);
					core_value.factorM = ((float)core_value.l_adc - (float)core_value.offset) / (float)core_value.r;
					eeprom_update_block (&core_value, &core_value_eep, sizeof(value_t));				
					goto calout;
				}
				break;
				case ACTION_BUTTON_D:	/*! Выйти без сохранения */
				goto calout;
				break;
			}
		}
	}
	calout: ;
}

void CoreClass::doPlus(){
	unsigned char r;
	POT_PLUS.setResistance(2);
	POT_MINUS.setResistance(0);
	delay(500);
	POT_PLUS.setResistance(0);
	while(1){
		r = (hx711.read() - core_value.offset) / core_value.factorP;
		r = constrain(r, 0, 255);
		POT_PLUS.setResistance(r);
		if (remoteController.readBitsFromPort()){
			if (remoteController.getBits()==ACTION_BUTTON_C){
				POT_PLUS.setResistance(0);
				POT_MINUS.setResistance(0);
				return;
			}
		}	
	}
}

void CoreClass::doMinus(){
	unsigned char r;
	POT_PLUS.setResistance(0);
	POT_MINUS.setResistance(2);
	delay(500);
	POT_MINUS.setResistance(0);
	while(1){
		r = (hx711.read() - core_value.offset) / core_value.factorM;
		r = constrain(r, 0, 255);
		POT_MINUS.setResistance(r);
		if (remoteController.readBitsFromPort()){
			if (remoteController.getBits()==ACTION_BUTTON_C){
				POT_PLUS.setResistance(0);
				POT_MINUS.setResistance(0);
				return;
			}
		}
	}
}

uint8_t CoreClass::isResistance(long adc){	
	return;
};
	
