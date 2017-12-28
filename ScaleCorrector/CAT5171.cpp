// 
// 
// 

#include "CAT5171.h"

CAT5171::CAT5171(){
	_addr = CAT5171_AD0;	
};
	
CAT5171::CAT5171(int addr){
	_addr = addr;	
};

void CAT5171::begin(){
	shutdown();
}

void CAT5171::setResistance(uint8_t date){
	Wire.beginTransmission(_addr); 	
	Wire.write(0);             
	Wire.write(date);
	Wire.endTransmission();     
};

void CAT5171::shutdown(){
	Wire.beginTransmission(_addr);
	Wire.write(CAT5171_SHUTDOWN); 
	Wire.write(0);
	Wire.endTransmission();
};

void CAT5171::reset(){
	Wire.beginTransmission(_addr);
	Wire.write(CAT5171_RESET);
	Wire.write(0);
	Wire.endTransmission();
};

uint8_t CAT5171::getResistance(){
	uint8_t c;
	Wire.requestFrom(_addr, 8);    // ����������� � �������� ���������� #2 8 ���� 
	while(Wire.available()){    // ������� ���������� ����� ��������� �� ��� ������������� �����  
		c = Wire.read();    // ��������� ���� ������ � ���� �������
	}
	return c;
}