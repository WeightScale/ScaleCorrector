#include "Arduino.h"
#include "CAT5171.h"
/*
 * ScaleCorrector.ino
 *
 * Created: 12/25/2017 9:02:01 PM
 * Author: Kostya
 */ 


//
//
CAT5171 potAD0(CAT5171_AD0);
CAT5171 potAD1(CAT5171_AD1);

void setup(){
	
	Wire.begin();
	potAD0.begin();
	potAD1.begin();
	potAD1.setResistance(256);
	  /* add setup code here, setup code runs once when the processor starts */

}
unsigned char i0, i1;
void loop(){
	
	potAD0.setResistance(i1);
	//i0++;
	i1++;
	//if(i0 > 254)
		//i0 = 1;
	if(i1 >= 254)
		i1 = 1;
	delay(100);
	//potAD0.reset();
	//potAD1.reset();
	//delay(500);
	
	//potAD0.shutdown();
	//potAD1.shutdown();
	  /* add main program code here, this code starts again each time it ends */

}


