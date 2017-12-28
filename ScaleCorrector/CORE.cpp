
#include "CORE.h"
#include "WirelessRemoteController.h"
#include "HX711.h"

value_t EEMEM core_value_eep;
value_t core_value;

CoreClass CORE = CoreClass();

CoreClass::CoreClass(){};
	
CoreClass::~CoreClass(){};

/*! Функция калибровки плюсового значения*/
void CoreClass::doPlusCalibration(){
	long adc;
	unsigned char p0 = 1, p1 = 1;
	POTAD0.shutdown();
	POTAD1.shutdown();
	delay(100);
	core_value.offset = hx711.read();
	POTAD0.setResistance(p0);
	POTAD1.setResistance(p1);
	while(1){
		if (remoteController.readBitsFromPort()){
			
			switch(remoteController.getBits()){
				case ACTION_BUTTON_A:	/*! Добатить вес*/
					if (p0 < 255){
						POTAD0.setResistance(++p0);	
					}					
				break;
				case ACTION_BUTTON_B:	/*! Отнять вес*/
					if (p0 > 1){
						POTAD0.setResistance(--p0);
					}
				break;
				case ACTION_BUTTON_C:	/*! Выйти и сохранить результат салибровки*/					
					eeprom_update_block (&core_value, &core_value_eep, sizeof(value_t));	
					adc = hx711.read();		
					goto calout;
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

	while(1){
		if (remoteController.readBitsFromPort()){
			
			switch(remoteController.getBits()){
				case ACTION_BUTTON_A:	/*! Отнять вес*/
				
				break;
				case ACTION_BUTTON_B:	/*! Добавить вес*/
				
				break;
				case ACTION_BUTTON_C:	/*! Выйти и сохранить результат салибровки*/
				
					goto calout;
				break;
				case ACTION_BUTTON_D:	/*! Выйти без сохранения */
					goto calout;
				break;
			}
		}
	}
	calout: ;
}
