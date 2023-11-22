#include <stdint.h>
#include <string.h> //only memset

typedef struct
{
	uint16_t _inputEvent;
	uint16_t Events[5];
	//uint16_t K1;
	//uint16_t K2;
	//uint16_t K3;
	//uint16_t K4;
	uint16_t K[5 - 1];
	uint16_t Q;
	uint16_t Reset;
}SerialEventsRegister_t;

void SerialEventsRegister(uint16_t firstEvent, uint16_t secEvent, uint16_t thirdEvent, uint16_t fourthEvent, uint16_t fifthEvent, SerialEventsRegister_t* SerialEventsReg);
uint16_t RegisterEvent(uint16_t inputEvent, SerialEventsRegister_t* SerialEventsReg);
uint16_t SerialEventsCheck(uint16_t inputEvent, SerialEventsRegister_t* SerialEventsReg);
void ResetEventsRegister(SerialEventsReg);