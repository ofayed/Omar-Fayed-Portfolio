#pragma once
#include "ReservationStation.h";

class Instruction
{

public:
	int rA; //destination
	int rB; //source 1
	int rC; //source 2
	int begIssue;
	int begExec;
	int endExec;
	int begWB;
	string OP;

public:
	Instruction();
	Instruction(int rAIn, int rBIn, int rCIn);

};

