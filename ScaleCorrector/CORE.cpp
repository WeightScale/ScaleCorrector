
#include "CORE.h"
#include "WirelessRemoteController.h"
#include "HX711.h"

value_t EEMEM core_value_eep;
value_t core_value;

CoreClass CORE = CoreClass();

CoreClass::CoreClass(){};
	
CoreClass::~CoreClass(){};

/*! ������� ���������� ��������� ��������*/
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
				case ACTION_BUTTON_A:	/*! �������� ���*/
					if (p0 < 255){
						POTAD0.setResistance(++p0);	
					}					
				break;
				case ACTION_BUTTON_B:	/*! ������ ���*/
					if (p0 > 1){
						POTAD0.setResistance(--p0);
					}
				break;
				case ACTION_BUTTON_C:	/*! ����� � ��������� ��������� ����������*/					
					eeprom_update_block (&core_value, &core_value_eep, sizeof(value_t));	
					adc = hx711.read();		
					goto calout;
				break;
				case ACTION_BUTTON_D:	/*! ����� ��� ���������� */
					goto calout;
				break;
			}
		}
	}
	calout: ;
}

/*! ������� ���������� ���������� ��������*/
void CoreClass::doMinusCalibration(){

	while(1){
		if (remoteController.readBitsFromPort()){
			
			switch(remoteController.getBits()){
				case ACTION_BUTTON_A:	/*! ������ ���*/
				
				break;
				case ACTION_BUTTON_B:	/*! �������� ���*/
				
				break;
				case ACTION_BUTTON_C:	/*! ����� � ��������� ��������� ����������*/
				
					goto calout;
				break;
				case ACTION_BUTTON_D:	/*! ����� ��� ���������� */
					goto calout;
				break;
			}
		}
	}
	calout: ;
}
