/*
 * \brief Прием данных с беспроводного пульта дистанционного управления.
 *
 * \author Konst <kreogen@email.ua>
 * \date 25.12.2017
 * \license MIT License (contact me if too restrictive)
 * \copyright Copyright (c) 2018 Konst
 * \version 1.0
 */

#include "WirelessRemoteController.h"

WirelessRemoteController::WirelessRemoteController(){
	pinMode(PIN_D0, INPUT);
	pinMode(PIN_D1, INPUT);
	pinMode(PIN_D2, INPUT);
	pinMode(PIN_D3, INPUT);
	
	pinMode(PIN_VT, INPUT);
}

WirelessRemoteController::~WirelessRemoteController(){};

/*! \brief Считываем биты данных.
*
*	Метод проверяет если на пульте нажаты кнопки и мы их считываем первый раз, 
*	тогда считываем данные с порта и ставим флаг flagVT = true чтобы знать что данные  уже считаны.
*	Когда кнопка на пульте отпущена, тогда следующая проверка сбросит флаг flagVT = false.
*	
*	\return Возвращает true- если пришли новые данные с пульта. 
 */
bool WirelessRemoteController::readBitsFromPort(){	
	if(readBitVT()){
		if (flagVT){
			flagVT = false;	
			_pinsBit = PIND & MASK_PULT_PIN;
			return true;
		}						
	}else{
		flagVT = true;
	}
	return false;
}

bool WirelessRemoteController::readBitsPortToTime(){
	static long time = millis();
	static bool flag;
	if(readBitVT()){
		if (!flag){
			flag= true;
			time = millis();
			_pinsBit = PIND & MASK_PULT_PIN;
			return true;
		}else {
			if ((time + 1500) < millis()){
				_pinsBit = PIND & MASK_PULT_PIN;
				delay(50);
				return true;	
			}else{
				return false;
			}	
		}				
	}else{
		flag = false;
		return false;
	}
	/*if(readBitVT()){
		if (flagVT){
			flagVT = false;	
			_pinsBit = PIND & MASK_PULT_PIN;
			return true;
		}
						
	}else{
		flagVT = true;
	}*/	

	return false;
}

bool WirelessRemoteController::readBitVT(){
	return (bool)digitalRead(PIN_VT);
}

void WirelessRemoteController::addTrigger(void (*function)()){	
	attachInterrupt(digitalPinToInterrupt(PIN_VT), function, RISING);  
}


