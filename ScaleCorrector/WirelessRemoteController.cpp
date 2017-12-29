/*
 * \brief Receive data from wireless remote controller (implementation)
 *
 * \author Quentin Comte-Gaz <quentin@comte-gaz.com>
 * \date 1 July 2016
 * \license MIT License (contact me if too restrictive)
 * \copyright Copyright (c) 2016 Quentin Comte-Gaz
 * \version 1.0
 */

#include "WirelessRemoteController.h"

WirelessRemoteController::WirelessRemoteController(){
	_pins[0] = PIN_D0;
	_pins[1] = PIN_D1;
	_pins[2] = PIN_D2;
	_pins[3] = PIN_D3;

	for (int i = 0; i < 4; i++){
		pinMode(_pins[i], INPUT);
	}
}

WirelessRemoteController::~WirelessRemoteController(){};

bool WirelessRemoteController::getCurrentValue(bool data[4]){
	bool is_valid = false;

	for(int i = 0; i < 4; i++){
		data[i] = digitalRead(_pins[i]);
		is_valid |= data[i];
		
		_pinsBit <<= 1;
		if (data[i]){
			_pinsBit++;
		}
	}

	return is_valid;
}

/*! Получаем биты данных на порту
	Возвращаем true если есть данные
 */
bool WirelessRemoteController::readBitsFromPort(){
	//_pinsBit = 0;
	
	if(digitalRead(PIN_VT)){
		if (flagVT){
			flagVT = false;	
			_pinsBit = PIND & 0x0f;
			return true;
		}				
	}else{
		flagVT = true;
	}	

	return false;
}

void WirelessRemoteController::addTrigger(void (*function)()){	
	attachInterrupt(digitalPinToInterrupt(PIN_VT), function, RISING);  
}


