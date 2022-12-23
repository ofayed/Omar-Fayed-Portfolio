#include "ReservationStation.h"


ReservationStation::ReservationStation() {

	busy = false;
	Qj = 1;
	Qk = 1;
	Vj = 0;
	Vk = 0;
	A = 0;

	//Op = 0; 
	result = 0;
	resultReady = false;

	indexOfInst = -1;
	IssueCycle = 0;
	ExecuteCycle = 0;
	WriteBackCycle = 0;
}


ReservationStation::ReservationStation(string OP, int rsOperandAvailable) {

	busy = false;
	Qj = rsOperandAvailable;
	Qk = rsOperandAvailable;
	Vj = 0;
	Vk = 0;

	A = 0;
	Op = OP;
	result = 0;
	resultReady = false;

	//indexOfInst = 100000;
	IssueCycle = 0;
	WriteBackCycle = 0;
	ExecuteCycle = 0;
}
