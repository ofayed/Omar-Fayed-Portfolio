/*#include <iostream>
#include<stdlib.h>
#include<vector>
#include <math.h>
#include <string>

using namespace std;

struct instructions {
public:
	int regFile[31];
	string operation;
	int rd,rs1,rs2,imm,pc;
	//void shamt(int rs1);

};



string signextend(string extend)
{
	string zero = "0000000000000000";
	string one = "1111111111111111";


	if (extend[0] == 0)
	{
		return zero + extend;
	}

	else {
		return one + extend;
	}
}





void add(instructions add)
{
	add.regFile[add.rd] = add.regFile[add.rs1] + add.regFile[add.rs2];
};
void sub(instructions sub)
{
	
	sub.regFile[sub.rd] = sub.regFile[sub.rs1] - sub.regFile[sub.rs2];
};
void lb(instructions lb);
void lw(instructions lw)
{
	lw.regFile[lw.rd] = lw.regFile[lw.rs1];
};
void lh(instructions lh);
void LBU(instructions lbu);
void LHU(instructions LHU);
void SB(instructions SB);
void SH(instructions SH);
void SW(instructions SW);
void EBREAK(instructions EBREAK);

void ADDI(instructions ADDI);
void SLTI(instructions SLTI);
void SLTIU(instructions SLTIU);
void XORI(instructions XORI);
void ORI(instructions ORI);
void ANDI(instructions ANDI);
void SLLI(instructions SLLI);
void XOR(instructions XOR);
void ECALL(instructions ECALL);

void SRLI(instructions SRLI);
void SRAI(instructions SRAI);
void SLL(instructions SLL);
void SLT(instructions SLT);
void SLTU(instructions SLTU);
void SRL(instructions SRL);
void SRA(instructions SRA);
void OR(instructions OR);
void AND(instructions AND);
void FENCE(instructions FENCE);



void LUI(instructions LUI);
void AUIPC(instructions AUIPC);
void JAL(instructions JAL);
void JALR(instructions JALR);
void BEQ(instructions BEQ);
void BNE(instructions BNE);
void BLT(instructions BLT);
void BGE(instructions BGE);
void BLTU(instructions BLTU);
void BGEU(instructions BGEU);


*/