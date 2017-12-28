#include "CORE.h"
#include "HX711.h"
#include "WirelessRemoteController.h"
#include "CAT5171.h"
/*
 * ScaleCorrector.ino
 *
 * Created: 12/25/2017 9:02:01 PM
 * Author: Kostya
 */ 

CAT5171 potAD0(CAT5171_AD0);
CAT5171 potAD1(CAT5171_AD1);

void setup(){
	
	Wire.begin();
	potAD0.begin();
	potAD1.begin();

	  /* add setup code here, setup code runs once when the processor starts */

}

void loop(){
	
	potAD0.reset();
	
	delay(500);
	
	potAD0.shutdown();

	  /* add main program code here, this code starts again each time it ends */

}
