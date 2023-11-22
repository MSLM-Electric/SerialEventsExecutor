#include "SerialEventsRegister.h"

static uint8_t _i = 0;

/*Registering the serial actions*/
/*     _____                                                        _____
* |   |     | firstEvent                                           |     | firstEvent
* |___|_____|______________________________________________________|_____|_______________________________________________________________________
*            __________                                                                   __________
* |         |          | secEvent                                                        |          | secEvent
* |_________|__________|_________________________________________________________________|__________|____________________________________________
*                       ________                                          ________
* |                    |        |thirdEvent                              |        |thirdEvent
* |____________________|________|________________________________________|________|______________________________________________________________
*                                ____                                              ____
* |                             |    |fourthEvent                                 |    | fourthEvent
* |_____________________________|____|____________________________________________|____|_________________________________________________________
*                                     ____
* |Q                       Reg->Q    |    x <-- Reset() called                                       X (!Nothing happens cause the execution of events not properly serial!)
* |__________________________________|____X______________________________________________________________________________________________________
*/
void SerialEventsRegister(uint16_t firstEvent, uint16_t secEvent, uint16_t thirdEvent, uint16_t fourthEvent, uint16_t fifthEvent, SerialEventsRegister_t *SerialEventsReg)
{
	SerialEventsRegister_t* Reg = SerialEventsReg;
	uint16_t inputEvent = Reg->_inputEvent;
	Reg->Events[0] = firstEvent;
	Reg->Events[1] = secEvent;
	Reg->Events[2] = thirdEvent;
	Reg->Events[3] = fourthEvent;
	Reg->Events[4] = fifthEvent;
	_i = 0;
	return;
}

uint16_t RegisterEvent(uint16_t inputEvent, SerialEventsRegister_t* SerialEventsReg)
{
	SerialEventsReg->Events[_i] = inputEvent;
	_i++;
	if (_i >= sizeof(SerialEventsReg->Events)) {
		_i = 0;
		return SerialEventsCheck(inputEvent, SerialEventsReg);
	}
	return 0;
}

uint16_t SerialEventsCheck(uint16_t inputEvent, SerialEventsRegister_t* SerialEventsReg)
{
	SerialEventsReg->_inputEvent = inputEvent;
	SerialEventsRegister_t* Reg = SerialEventsReg;
	uint16_t firstEvent = Reg->Events[0];
	uint16_t secEvent = Reg->Events[1];
	uint16_t thirdEvent = Reg->Events[2];
	uint16_t fourthEvent = Reg->Events[3];
	uint16_t fifthEvent = Reg->Events[4];
	Reg->K[0] = ((inputEvent == firstEvent) | Reg->K[0]) & (~Reg->K[1]);
	Reg->K[1] = ((Reg->K[0] & (inputEvent == secEvent)) | Reg->K[1]) & (~Reg->K[2]);
	Reg->K[2] = ((Reg->K[1] & (inputEvent == thirdEvent)) | Reg->K[2]) & (~Reg->K[3]);
	Reg->K[3] = ((Reg->K[2] & (inputEvent == fourthEvent)) | Reg->K[3]) & (~Reg->Q);
	Reg->Q = ((Reg->K[3] & (inputEvent == fifthEvent)) | Reg->Q) & (~Reg->Reset);
	return Reg->Q;
}

void ResetEventsRegister(SerialEventsRegister_t* SerialEventsReg)
{
	memset(SerialEventsReg->K, 0, sizeof(SerialEventsReg->K));
	SerialEventsReg->Q = 0;
	_i++;
}


/*
uint16_t SerialEventsRegister(uint16_t firstEvent, uint16_t secEvent, uint16_t thirdEvent, uint16_t fourthEvent, uint16_t fifthEvent, SerialEventsRegister_t* SerialEventsReg)
{
	SerialEventsRegister_t* Reg = SerialEventsReg;
	uint16_t inputEvent = Reg->_inputEvent;
	Reg->Events[0] = firstEvent;
	Reg->Events[1] = secEvent;
	Reg->Events[2] = thirdEvent;
	Reg->Events[3] = fourthEvent;
	Reg->Events[4] = fifthEvent;
	Reg->K1 = ((inputEvent == firstEvent) | Reg->K1) & (~Reg->K2);
	Reg->K2 = (Reg->K1 | Reg->K2) & (inputEvent == secEvent) & (~Reg->K3);
	Reg->K3 = (Reg->K2 | Reg->K3) & (inputEvent == thirdEvent) & (~Reg->K4);
	Reg->K4 = (Reg->K3 | Reg->K4) & (inputEvent == fourthEvent) & (~Reg->Q);
	Reg->Q = ((Reg->K4 & (inputEvent == fifthEvent)) | Reg->Q) & (~Reg->Reset);
	return Reg->Q;
}

uint16_t SerialEventsCheck(uint16_t inputEvent, SerialEventsRegister_t* SerialEventsReg)
{
	SerialEventsReg->_inputEvent = inputEvent;
	return SerialEventsRegister()
}*/