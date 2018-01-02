#include "CORE.h"
#include "WirelessRemoteController.h"
#include "HX711.h"

value_t EEMEM core_value_eep;
value_t core_value;



CoreClass::CoreClass(){	
};
	
CoreClass::~CoreClass(){};

void CoreClass::begin(){
	Wire.begin();
	Wire.setClock(400000);	
	eeprom_read_block (&core_value, &core_value_eep, sizeof(value_t));	
}	

/*! 
*	\brief Функция калибровки плюсового значения. 
*	
*/
void CoreClass::doPlusCalibration(){
	unsigned char p0 = 0;
	POT_PLUS.setResistance(2);						///< Для визуального определения что вошли в калибровку.		
	POT_MINUS.setResistance(0);
	delay(500);
	POT_PLUS.setResistance(0);
	delay(100);
	core_value.offset = hx711.read();
	while(1){
		if (remoteController.readBitsPortToTime()){			
			switch(remoteController.getBits()){
				case ACTION_BUTTON_A:				///< Добатить вес.
					POT_PLUS.setResistance(++p0);
				break;
				case ACTION_BUTTON_B:				///< Отнять вес.
					POT_PLUS.setResistance(--p0);
				break;
				case PLUS_CALIBRATION:				///< Выйти и сохранить результат салибровки.
					{
						core_value.r = POT_PLUS.getResistance();
						core_value.l_adc = hx711.read();
						POT_PLUS.setResistance(0);
						core_value.factorP = float(core_value.r) / float(core_value.l_adc - core_value.offset) ;
						eeprom_update_block (&core_value, &core_value_eep, sizeof(value_t));						
						goto calout;
					}
				break;
				case OFFSET_CALIBRATION:				///< Калибровка наклона сдвига отклонения от реального веса.
						core_value.r = POT_PLUS.getResistance();
						core_value.r_adc = hx711.read();
						core_value.factorO = (float)core_value.r / float(core_value.r_adc - core_value.offset);	
						eeprom_update_block (&core_value, &core_value_eep, sizeof(value_t));
						POT_PLUS.setResistance(0);
						POT_PLUS.setResistance(2);
						delay(500);
						POT_PLUS.setResistance(core_value.r);
				break;
				case ACTION_BUTTON_D:				///< Выйти без сохранения.
					goto calout;
				break;
			}			
		}
	}
	calout: ;
	{
		POT_PLUS.setResistance(0);
		POT_PLUS.setResistance(2);								///< Для визуального определения что вышли в корректировку плюсования.
		delay(500);
		POT_PLUS.setResistance(0);
	}
}

/*! 
*	\brief Функция калибровки минусового значения.
*
*/
void CoreClass::doMinusCalibration(){
	unsigned char p1 = 0;
	POT_PLUS.setResistance(0);
	POT_MINUS.setResistance(2);						///< Для визуального определения что вошли в калибровку.
	delay(500);
	POT_MINUS.setResistance(0);
	delay(100);
	core_value.offset = hx711.read();
	while(1){
		if (remoteController.readBitsPortToTime()){
		
			switch(remoteController.getBits()){
				case ACTION_BUTTON_A:				///< Добатить минусовой вес.
					POT_MINUS.setResistance(++p1);
				break;
				case ACTION_BUTTON_B:				///< Отнять минусовой вес.
					POT_MINUS.setResistance(--p1);
				break;				
				case MINUS_CALIBRATION:				///< Выйти и сохранить результат салибровки.
					core_value.r = POT_MINUS.getResistance();
					core_value.l_adc = hx711.read();
					POT_MINUS.setResistance(0);
					core_value.factorM = float(core_value.r) / float(core_value.l_adc - core_value.offset) ;
					eeprom_update_block (&core_value, &core_value_eep, sizeof(value_t));				
					goto calout;
				break;
				case OFFSET_CALIBRATION:				///< Калибровка наклона сдвига отклонения от реального веса.
					core_value.r = POT_MINUS.getResistance();
					core_value.r_adc = hx711.read();
					core_value.factorO = (float)core_value.r / float(core_value.r_adc - core_value.offset);	
					eeprom_update_block (&core_value, &core_value_eep, sizeof(value_t));
					POT_MINUS.setResistance(0);
					POT_MINUS.setResistance(2);
					delay(500);
					POT_MINUS.setResistance(core_value.r);
				break;
				case ACTION_BUTTON_D:				///< Выйти без сохранения.
					goto calout;
				break;
			}
		}
	}
	calout: ;
	{
		POT_MINUS.setResistance(0);
		POT_MINUS.setResistance(2);								///< Для визуального определения что вышли в корректировку минусования.
		delay(500);
		POT_MINUS.setResistance(0);
	}
}

void CoreClass::doPlus(){
	POT_PLUS.setResistance(2);											///< Для визуального определения что вошли в корректировку плюсования.
	POT_MINUS.setResistance(0);
	delay(500);
	POT_PLUS.setResistance(0);
	while(1){
		core_value.r = float(hx711.read() - core_value.offset) * core_value.factorP;	///< Вычисляем значение сопротивления для корекции.		
		core_value.r = constrain(core_value.r, 0, 255);										///< Чтобы не вышло из диапазона.
		POT_PLUS.setResistance(core_value.r);				
		if (remoteController.readBitsFromPort()){
			switch(remoteController.getBits()){
				case ACTION_BUTTON_C:
					POT_PLUS.setResistance(2);								///< Для визуального определения что вышли в корректировку плюсования.
					delay(500);
					POT_PLUS.setResistance(0);
					return;
				case ACTION_BUTTON_B:
					goto _minus;
			}			
		}				
	}
	_minus: ;
	{
		remoteController.setFlagVT(true);									///< Устанавливаем флаг чтобы кнопка минус сработала	
	}
}

void CoreClass::doMinus(){
	POT_PLUS.setResistance(0);											///< Для визуального определения что вошли в корректировку минусования.
	POT_MINUS.setResistance(2);
	delay(500);
	POT_MINUS.setResistance(0);
	while(1){
		core_value.r = float(hx711.read() - core_value.offset) * core_value.factorM;	///< Вычисляем значение сопротивления для корекции.
		core_value.r = constrain(core_value.r, 0, 255);										///< Чтобы не вышло из диапазона.
		POT_MINUS.setResistance(core_value.r);
		if (remoteController.readBitsFromPort()){						///< Выходим из коректировки.
			switch(remoteController.getBits()){
				case ACTION_BUTTON_C:
					POT_MINUS.setResistance(2);								///< Для визуального определения что вышли в корректировку минусования.
					delay(500);
					POT_MINUS.setResistance(0);
				return;
				case ACTION_BUTTON_A:
					goto _plus;	
			}			
		}
	}
	_plus: ;
	{
		remoteController.setFlagVT(true);									///< Устанавливаем флаг чтобы кнопка плюс сработала	
	}
}

void CoreClass::standart(){
	hx711.powerDown();
	CORE.disconnect();
	while(1){		
		if (remoteController.readBitsFromPort()){
			switch(remoteController.getBits()){
				case ACTION_BUTTON_C:
				case ACTION_BUTTON_A:
				case ACTION_BUTTON_B:
					goto _exit;
				break;
			}			
		}
	}
	{
		_exit: ;
		hx711.powerUp();
		remoteController.setFlagVT(true);
	}
}

void CoreClass::disconnect(){
	POT_PLUS.shutdown();
	POT_MINUS.shutdown();
}

void CoreClass::reset(){
	POT_PLUS.setResistance(0);
	POT_MINUS.setResistance(0);
}


	
