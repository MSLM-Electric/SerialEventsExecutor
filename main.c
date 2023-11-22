#include "SerialEventsRegister.h"

typedef enum {
	APPLICATION_IDLE = 0,
	APPLICATION_START,
	APPLICATION_READY,
	APPLICATION_DISCONNECT
}ApplicationTypeDef;

int main(void)
{
	SerialEventsRegister_t SerialActions = { 0 };
	uint16_t Applic_state = 0;
	uint16_t PropeEventsFlag = 0;
	while (1)
	{
		SerialEventsRegister(APPLICATION_IDLE, APPLICATION_START, APPLICATION_READY, APPLICATION_DISCONNECT, APPLICATION_IDLE, &SerialActions);
		Applic_state = APPLICATION_IDLE;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_START;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_READY;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_DISCONNECT;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_IDLE;
		PropeEventsFlag = SerialEventsCheck(Applic_state, &SerialActions); //True! Good! Serial actions right occured.
		ResetEventsRegister(&SerialActions);

		Applic_state = APPLICATION_IDLE;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_START;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_IDLE;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_DISCONNECT;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_IDLE;
		PropeEventsFlag = SerialEventsCheck(Applic_state, &SerialActions); //False! Not serial registered actions evented.
		ResetEventsRegister(&SerialActions);

		Applic_state = APPLICATION_IDLE;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_START;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_READY;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_DISCONNECT;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_DISCONNECT;           //No matter how long it stays
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_IDLE;
		PropeEventsFlag = SerialEventsCheck(Applic_state, &SerialActions); //True! Good! Serial actions right occured.
		ResetEventsRegister(&SerialActions);

		Applic_state = APPLICATION_IDLE;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_START;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_READY;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_DISCONNECT;
		SerialEventsCheck(Applic_state, &SerialActions);
		Applic_state = APPLICATION_READY;
		PropeEventsFlag = SerialEventsCheck(Applic_state, &SerialActions); //False! Not serial registered actions evented.
		Applic_state = APPLICATION_DISCONNECT;
		PropeEventsFlag = SerialEventsCheck(Applic_state, &SerialActions); //False! Not serial registered actions evented.
		ResetEventsRegister(&SerialActions);
	}
}