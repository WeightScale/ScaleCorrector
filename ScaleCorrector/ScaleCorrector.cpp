#include "Arduino.h"
#include "CAT5171.h"
#include "WirelessRemoteController.h"
/*
 * ScaleCorrector.ino
 *
 * Created: 12/25/2017 9:02:01 PM
 * Author: Kostya
 */ 
#define buttonA 2
#define buttonB 0
#define buttonC 3
#define buttonD 1

WirelessRemoteController remote_controller(0, 1, 2, 3);

CAT5171 potAD0(CAT5171_AD0);
CAT5171 potAD1(CAT5171_AD1);

void setup(){
	
	Wire.begin();
	potAD0.begin();
	potAD1.begin();
	potAD0.reset();
	potAD1.reset();
	  /* add setup code here, setup code runs once when the processor starts */

}
unsigned char i0, i1=128;
void loop(){

	bool current_rx[4];
	if(remote_controller.getCurrentValue(current_rx)) {
		
		for (int i = 0; i < 4; i++) {
			if(current_rx[i]){
				switch(i){
					case buttonA:
						potAD0.setResistance(i1++);
						potAD1.setResistance(~i1);
					break;
					case buttonB:
						potAD0.setResistance(i1--);
						potAD1.setResistance(~i1);
					break;
					case buttonC:
						potAD0.shutdown();
						potAD1.shutdown();
					break;
				}	
			}
			
			/*if(current_rx[i])
				current_rx[i]=false;*/
		}
	}

	delay(1000);	

}


