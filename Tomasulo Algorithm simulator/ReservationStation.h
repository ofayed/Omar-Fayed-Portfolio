#pragma once
#include <iostream>
using namespace std;

#pragma once
class ReservationStation {

public:
	bool busy;
	//for the names of the reservation station producing these values
	int Qj;
	int Qk;
	int Vj;
	int Vk;
	int A;

	int result;
	bool resultReady;  //used to avoid dependency

	int indexOfInst; //the address/index of the instruction

	int ExecuteCycle; // how many cycles will this OP takes
	int IssueCycle;
	int WriteBackCycle;

	string Op;
public:
	ReservationStation();

	ReservationStation(string OP, int rsOperandAvailable);

};

