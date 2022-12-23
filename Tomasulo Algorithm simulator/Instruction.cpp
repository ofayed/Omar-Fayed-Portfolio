#include "Instruction.h"


Instruction::Instruction() {
	rA = 0;
	rB = 0;
	rC = 0;
	begIssue = 0;
	begExec = 0;
	endExec = 0;
	begWB = 0;
	OP = "";
}