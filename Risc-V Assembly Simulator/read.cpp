#include <iostream>
#include<stdlib.h>
#include<vector>
#include <math.h>
#include <string>
#include<bitset>
#include <fstream>
#include <map>
#include <string.h>
using namespace std;



struct instructions {
public:
	string operation;
	string rd, rs1, rs2,base;
	int imm,off;
	int pc = 0;
	 

};


#define ull unsigned long long int
struct functions
{
	int decToBinary(int N)
	{

		// To store the binary number
		ull B_Number = 0;
		int cnt = 0;
		while (N != 0) {
			int rem = N % 2;
			ull c = pow(10, cnt);
			B_Number += rem * c;
			N /= 2;

			// Count used to store exponent value
			cnt++;
		}

		return B_Number;
	};
	void decToHexa(int n)
	{
		// char array to store hexadecimal number
		char hexaDeciNum[100];

		// counter for hexadecimal number array
		int i = 0;
		while (n != 0) {
			// temporary variable to store remainder
			int temp = 0;

			// storing remainder in temp variable.
			temp = n % 16;

			// check if temp < 10
			if (temp < 10) {
				hexaDeciNum[i] = temp + 48;
				i++;
			}
			else {
				hexaDeciNum[i] = temp + 55;
				i++;
			}

			n = n / 16;
		}

		// printing hexadecimal number array in reverse order
		for (int j = i - 1; j >= 0; j--)
			cout << hexaDeciNum[j];
	};
	int JALR(instructions& JALR, map<string,int>& reg) {
		if (JALR.rd != "x0")
			return  reg[JALR.rd] = JALR.pc + 4;
		else
			return JALR.pc = reg[JALR.rs1] + (JALR.imm);
	};

	int lbu(instructions& lbu, map<string, int>& reg, map<string, int>& mem, int& counter)

	{
		int out;
		cout << endl << "operation: " << lbu.operation;
		out = decToBinary(reg[lbu.rs1]);
		cout << endl << "rs1: " << reg[lbu.rs1] << "  " << out << "   ";
		decToHexa(reg[lbu.rs1]);
		out = decToBinary(lbu.off);
		cout << endl << "off: " << lbu.off << "  " << out << "   ";
		decToHexa(lbu.off);

		string addr;
		int unsigned add;
		if(lbu.rs1.size()==2)
		add = stoi(lbu.rs1.substr(1, 1)) + (lbu.off / 4);
		else
			add = stoi(lbu.rs1.substr(1, 2)) + (lbu.off / 4);
		addr = "x" + to_string(add);
		cout << endl << addr << endl;
		if (reg[addr] > 256)
			reg[lbu.rd] = 256;
		else
			reg[lbu.rd] = mem[addr];

		out = decToBinary(reg[lbu.rd]);
		cout << endl << "rd: " << reg[lbu.rd] << "  " << out << "   ";
		decToHexa(reg[lbu.rd]);
		return counter + 4;

	}
	int lhu(instructions& lhu, map<string, int>& reg,  map<string, int>& mem, int& counter)

	{
		int out;
		cout << endl << "operation: " << lhu.operation;
		out = decToBinary(reg[lhu.rs1]);
		cout << endl << "rs1: " << reg[lhu.rs1] << "  " << out << "   ";
		decToHexa(reg[lhu.rs1]);
		out = decToBinary(lhu.off);
		cout << endl << "off: " << lhu.off << "  " << out << "   ";
		decToHexa(lhu.off);

		string addr;
		int unsigned add;
		if (lhu.rs1.size() == 2)
			add = stoi(lhu.rs1.substr(1, 1)) + (lhu.off / 4);
		else
			add = stoi(lhu.rs1.substr(1, 2)) + (lhu.off / 4);
		addr = "x" + to_string(add);
		cout << endl << addr << endl;
		if (reg[addr] > 256)
			reg[lhu.rd] = 256;
		else
			reg[lhu.rd] = mem[addr];

		out = decToBinary(reg[lhu.rd]);
		cout << endl << "rd: " << reg[lhu.rd] << "  " << out << "   ";
		decToHexa(reg[lhu.rd]);
		return counter + 4;

	}

	int lb(instructions& lb, map<string, int>& reg,  map<string, int>& mem, int& counter)

	{
		int out;
		cout << endl << "operation: " << lb.operation;
		out = decToBinary(reg[lb.rs1]);
		cout << endl << "rs1: " << reg[lb.rs1] << "  " << out << "   ";
		decToHexa(reg[lb.rs1]);
		out = decToBinary(lb.off);
		cout << endl << "off: " << lb.off << "  " << out << "   ";
		decToHexa(lb.off);

		string addr;
		int add;
		if (lb.rs1.size() == 2)
			add = stoi(lb.rs1.substr(1, 1)) + (lb.off / 4);
		else
			add = stoi(lb.rs1.substr(1, 2)) + (lb.off / 4);
		addr = "x" + to_string(add);
		cout << endl << addr << endl;
		if (reg[addr] > 256)
			reg[lb.rd] = 256;
		else
			reg[lb.rd] = mem[addr];

		out = decToBinary(reg[lb.rd]);
		cout << endl << "rd: " << reg[lb.rd] << "  " << out << "   ";
		decToHexa(reg[lb.rd]);
		return counter + 4;

	}

	int lh(instructions& lh, map<string, int>& reg,  map<string, int>& mem, int& counter)

	{
		int out;
		cout << endl << "operation: " << lh.operation;
		out = decToBinary(reg[lh.rs1]);
		cout << endl << "rs1: " << reg[lh.rs1] << "  " << out << "   ";
		decToHexa(reg[lh.rs1]);
		out = decToBinary(lh.off);
		cout << endl << "off: " << lh.off << "  " << out << "   ";
		decToHexa(lh.off);

		string addr;
		int add;
		if (lh.rs1.size() == 2)
			add = stoi(lh.rs1.substr(1, 1)) + (lh.off / 4);
		else
			add = stoi(lh.rs1.substr(1, 2)) + (lh.off / 4);
		addr = "x" + to_string(add);
		cout << endl << addr << endl;
		if(reg[addr] > 65535)
		reg[lh.rd] = 65535;
		else
			reg[lh.rd] = mem[addr];
		
		out = decToBinary(reg[lh.rd]);
		cout << endl << "rd: " << reg[lh.rd] << "  " << out << "   ";
		decToHexa(reg[lh.rd]);
		return counter + 4;

	}
	int lw(instructions& lw, map<string, int>& reg,  map<string, int>& mem, int counter)

	{
		
		int out;
		cout << endl << "operation: " << lw.operation;
		out = decToBinary(reg[lw.rs1]);
		cout << endl << "rs1: " << reg[lw.rs1] << "  " << out << "   ";
		decToHexa(reg[lw.rs1]);
		out = decToBinary(lw.off);
		cout << endl << "off: " << lw.off << "  " << out << "   ";
		decToHexa(lw.off);
		
		string addr;
		int add;
		if (lw.rs1.size() == 2)
			add = stoi(lw.rs1.substr(1, 1)) + (lw.off / 4);
		else
			add = stoi(lw.rs1.substr(1, 2)) + (lw.off / 4);
		addr = "x" + to_string(add);
		
		reg[lw.rd] = mem[addr];
		out = decToBinary(reg[lw.rd]);
		cout << endl << "rd: " << reg[lw.rd] << "  " << out << "   ";
		decToHexa(reg[lw.rd]);
		return counter + 4;

	}


	int sb(instructions& sb, map<string, int>& reg, map<string, int>& mem, int& counter)

	{
		int out;
		cout << endl << "operation: " << sb.operation;
		out = decToBinary(mem[sb.rs1]);
		cout << endl << "rs1: " << mem[sb.rs1] << "  " << out << "   ";
		decToHexa(mem[sb.rs1]);
		out = decToBinary(sb.off);
		cout << endl << "off: " << sb.off << "  " << out << "   ";
		decToHexa(sb.off);

		string addr;
		int add;
		if (sb.rs1.size() == 2)
			add = stoi(sb.rs1.substr(1, 1)) + (sb.off / 4);
		else
			add = stoi(sb.rs1.substr(1, 2)) + (sb.off / 4);
		addr = "x" + to_string(add);
		cout << endl << addr << endl;
		mem[sb.rd] = reg[addr];
		out = decToBinary(reg[sb.rd]);
		cout << endl << "rd: " << reg[sb.rd] << "  " << out << "   ";
		decToHexa(reg[sb.rd]);
		return counter + 4;

	}

	int sh(instructions& sh, map<string, int>& reg, map<string, int>& mem, int& counter)

	{
		int out;
		cout << endl << "operation: " << sh.operation;
		out = decToBinary(mem[sh.rs1]);
		cout << endl << "rs1: " << mem[sh.rs1] << "  " << out << "   ";
		decToHexa(mem[sh.rs1]);
		out = decToBinary(sh.off);
		cout << endl << "off: " << sh.off << "  " << out << "   ";
		decToHexa(sh.off);

		string addr;
		int add;
		if (sh.rs1.size() == 2)
			add = stoi(sh.rs1.substr(1, 1)) + (sh.off / 4);
		else
			add = stoi(sh.rs1.substr(1, 2)) + (sh.off / 4);
		addr = "x" + to_string(add);
		cout << endl << addr << endl;
		mem[sh.rd] = reg[addr];
		out = decToBinary(reg[sh.rd]);
		cout << endl << "rd: " << reg[sh.rd] << "  " << out << "   ";
		decToHexa(reg[sh.rd]);
		return counter + 4;

	}
	int sw(instructions& sw, map<string, int>& reg, map<string, int>& mem, int& counter)

	{
		int out;
		cout << endl << "operation: " << sw.operation;
		out = decToBinary(reg[sw.rs1]);
		cout << endl << "rs1: " << reg[sw.rs1] << "  " << out << "   ";
		decToHexa(reg[sw.rs1]);
		out = decToBinary(sw.off);
		cout << endl << "off: " << sw.off << "  " << out << "   ";
		decToHexa(sw.off);

		string addr;
		int add;
		if (sw.rs1.size() == 2)
			add = stoi(sw.rs1.substr(1, 1)) + (sw.off / 4);
		else
			add = stoi(sw.rs1.substr(1, 2)) + (sw.off / 4);
		addr = "x" + to_string(add);
		cout << endl << addr << endl;
		
		out = decToBinary(mem[sw.rd]);
		cout << endl << "rd: " << mem[sw.rd] << "  " << out << "   ";
		decToHexa(mem[sw.rd]);
		
		mem[sw.rd] = reg[addr];
		cout << "   " << "memory "<< sw.rd<<" " <<mem[sw.rd] << endl;
		return counter + 4;

	}


	int OR(instructions &OR, map<string, int>& reg,  int& counter) {
		int out;
		cout << endl << "operation: " << OR.operation;
		out = decToBinary(reg[OR.rs1]);
		cout << endl << "rs1: " << reg[OR.rs1] << "  " << out<<"   ";
		decToHexa(reg[OR.rs1]);
		out = decToBinary(reg[OR.rs2]);
		cout << endl << "rs2: " << reg[OR.rs2] << "  " << out<<"   ";
		decToHexa(reg[OR.rs2]);
		out = decToBinary(reg[OR.rd]);
		cout << endl << "rd: " << reg[OR.rd] << "  " << out<<"   ";
		decToHexa(reg[OR.rd]);
		reg[OR.rd] = reg[OR.rs1] | reg[OR.rs2];
		return counter + 4;
	};

	int SRLI(instructions &SRLI, map<string, int>& reg, int& counter) {
		reg[SRLI.rd] = ((unsigned int)reg[SRLI.rs1] >> reg[SRLI.rs2]);
		int out;
		cout << endl << "operation: " << SRLI.operation;
		out = decToBinary(reg[SRLI.rs1]);
		cout << endl << "rs1: " << reg[SRLI.rs1] << "  " << out << "   ";
		decToHexa(reg[SRLI.rs1]);
		out = decToBinary(reg[SRLI.rs2]);
		cout << endl << "rs2: " << reg[SRLI.rs2] << "  " << out << "   ";
		decToHexa(reg[SRLI.rs2]);
		out = decToBinary(reg[SRLI.rd]);
		cout << endl << "rd: " << reg[SRLI.rd] << "  " << out << "   ";
		decToHexa(reg[SRLI.rd]);
		return counter + 4;
	};
		
	int SRAI(instructions &SRAI, map<string, int>& reg, int& counter) {
		reg[SRAI.rd] = (reg[SRAI.rs1] >> reg[SRAI.rs2]);
		int out;
		cout << endl << "operation: " << SRAI.operation;
		out = decToBinary(reg[SRAI.rs1]);
		cout << endl << "rs1: " << reg[SRAI.rs1] << "  " << out << "   ";
		decToHexa(reg[SRAI.rs1]);
		out = decToBinary(reg[SRAI.rs2]);
		cout << endl << "rs2: " << reg[SRAI.rs2] << "  " << out << "   ";
		decToHexa(reg[SRAI.rs2]);
		out = decToBinary(reg[SRAI.rd]);
		cout << endl << "rd: " << reg[SRAI.rd] << "  " << out << "   ";
		decToHexa(reg[SRAI.rd]);
		return counter + 4;
	};

	int SLT(instructions &SLT, map<string, int>& reg, int& counter) {
		reg[SLT.rd] = reg[SLT.rs1] < reg[SLT.rs2];
		int out;
		cout << endl << "operation: " << SLT.operation;
		out = decToBinary(reg[SLT.rs1]);
		cout << endl << "rs1: " << reg[SLT.rs1] << "  " << out << "   ";
		decToHexa(reg[SLT.rs1]);
		out = decToBinary(reg[SLT.rs2]);
		cout << endl << "rs2: " << reg[SLT.rs2] << "  " << out << "   ";
		decToHexa(reg[SLT.rs2]);
		out = decToBinary(reg[SLT.rd]);
		cout << endl << "rd: " << reg[SLT.rd] << "  " << out << "   ";
		decToHexa(reg[SLT.rd]);
		return counter + 4;
	};

	int SLTU(instructions &SLTU, map<string, int>& reg, int& counter) {
		reg[SLTU.rd] = (unsigned int)reg[SLTU.rs1] < (unsigned int)reg[SLTU.rs2];
		int out;
		cout << endl << "operation: " << SLTU.operation;
		out = decToBinary(reg[SLTU.rs1]);
		cout << endl << "rs1: " << reg[SLTU.rs1] << "  " << out << "   ";
		decToHexa(reg[SLTU.rs1]);
		out = decToBinary(reg[SLTU.rs2]);
		cout << endl << "rs2: " << reg[SLTU.rs2] << "  " << out << "   ";
		decToHexa(reg[SLTU.rs2]);
		out = decToBinary(reg[SLTU.rd]);
		cout << endl << "rd: " << reg[SLTU.rd] << "  " << out << "   ";
		decToHexa(reg[SLTU.rd]);
		return counter + 4;
	};

	int SLL(instructions &SLL, map<string, int>& reg, int& counter) {
		reg[SLL.rd] = (reg[SLL.rs1] << reg[SLL.rs2]);
		int out;
		cout << endl << "operation: " << SLL.operation;
		out = decToBinary(reg[SLL.rs1]);
		cout << endl << "rs1: " << reg[SLL.rs1] << "  " << out << "   ";
		decToHexa(reg[SLL.rs1]);
		out = decToBinary(reg[SLL.rs2]);
		cout << endl << "rs2: " << reg[SLL.rs2] << "  " << out << "   ";
		decToHexa(reg[SLL.rs2]);
		out = decToBinary(reg[SLL.rd]);
		cout << endl << "rd: " << reg[SLL.rd] << "  " << out << "   ";
		decToHexa(reg[SLL.rd]);
		return counter + 4;
	};

	int SRL(instructions &SRL, map<string, int>& reg, int& counter) {
		reg[SRL.rd] = ((unsigned int)reg[SRL.rs1] >> reg[SRL.rs2]);
		int out;
		cout << endl << "operation: " << SRL.operation;
		out = decToBinary(reg[SRL.rs1]);
		cout << endl << "rs1: " << reg[SRL.rs1] << "  " << out << "   ";
		decToHexa(reg[SRL.rs1]);
		out = decToBinary(reg[SRL.rs2]);
		cout << endl << "rs2: " << reg[SRL.rs2] << "  " << out << "   ";
		decToHexa(reg[SRL.rs2]);
		out = decToBinary(reg[SRL.rd]);
		cout << endl << "rd: " << reg[SRL.rd] << "  " << out << "   ";
		decToHexa(reg[SRL.rd]);
		return counter + 4;
	};

	int SRA(instructions &SRA, map<string, int>& reg, int& counter) {
		reg[SRA.rd] = (reg[SRA.rs1] / (pow(2, reg[SRA.rs2]))) ;
		int out;
		cout << endl << "operation: " << SRA.operation;
		out = decToBinary(reg[SRA.rs1]);
		cout << endl << "rs1: " << reg[SRA.rs1] << "  " << out << "   ";
		decToHexa(reg[SRA.rs1]);
		out = decToBinary(reg[SRA.rs2]);
		cout << endl << "rs2: " << reg[SRA.rs2] << "  " << out << "   ";
		decToHexa(reg[SRA.rs2]);
		out = decToBinary(reg[SRA.rd]);
		cout << endl << "rd: " << reg[SRA.rd] << "  " << out << "   ";
		decToHexa(reg[SRA.rd]);
		return counter + 4;
	};

	int AND(instructions &AND, map<string,int> &reg, int& counter) {
		reg[AND.rd] = reg[AND.rs1] & reg[AND.rs2];
		int out;
		cout << endl << "operation: " << AND.operation;
		out = decToBinary(reg[AND.rs1]);
		cout << endl << "rs1: " << reg[AND.rs1] << "  " << out << "   ";
		decToHexa(reg[AND.rs1]);
		out = decToBinary(reg[AND.rs2]);
		cout << endl << "rs2: " << reg[AND.rs2] << "  " << out << "   ";
		decToHexa(reg[AND.rs2]);
		out = decToBinary(reg[AND.rd]);
		cout << endl << "rd: " << reg[AND.rd] << "  " << out << "   ";
		decToHexa(reg[AND.rd]);
		return counter + 4;
	};
	
	int add(instructions& add, map<string, int>& reg,int &counter)
	{
		reg[add.rd] = reg[add.rs1] + reg[add.rs2];
		int out;
		cout << endl << "operation: " << add.operation;
		out = decToBinary(reg[add.rs1]);
		cout << endl << "rs1: " << reg[add.rs1] << "  " << out << "   ";
		decToHexa(reg[add.rs1]);
		out = decToBinary(reg[add.rs2]);
		cout << endl << "rs2: " << reg[add.rs2] << "  " << out << "   ";
		decToHexa(reg[add.rs2]);
		out = decToBinary(reg[add.rd]);
		cout << endl << "rd: " << reg[add.rd] << "  " << out << "   ";
		decToHexa(reg[add.rd]);
		//cout << endl << add.pc;
		//add.pc =add.pc + 4;
		return counter + 4;
	}

	int sub(instructions& sub, map<string, int>& reg, int& counter)
	{
		int out;
		reg[sub.rd] = reg[sub.rs1] - reg[sub.rs2];
		
		cout << endl << "operation: " << sub.operation;
		out = decToBinary(reg[sub.rs1]);
		cout << endl << "rs1: " << reg[sub.rs1] << "  " << out << "   ";
		decToHexa(reg[sub.rs1]);
		out = decToBinary(reg[sub.rs2]);
		cout << endl << "rs2: " << reg[sub.rs2] << "  " << out << "   ";
		decToHexa(reg[sub.rs2]);
		out = decToBinary(reg[sub.rd]);
		cout << endl << "rd: " << reg[sub.rd] << "  " << out << "   ";
		decToHexa(reg[sub.rd]);
		//sub.pc = sub.pc + 4;
		//cout << endl << sub.pc;
		return counter + 4;
	}

	int XOR(instructions& XOR, map<string, int>& reg, int& counter)
	{
		reg[XOR.rd] = reg[XOR.rs1] ^ reg[XOR.rs2];
		int out;
		cout << endl << "operation: " << XOR.operation;
		out = decToBinary(reg[XOR.rs1]);
		cout << endl << "rs1: " << reg[XOR.rs1] << "  " << out << "   ";
		decToHexa(reg[XOR.rs1]);
		out = decToBinary(reg[XOR.rs2]);
		cout << endl << "rs2: " << reg[XOR.rs2] << "  " << out << "   ";
		decToHexa(reg[XOR.rs2]);
		out = decToBinary(reg[XOR.rd]);
		cout << endl << "rd: " << reg[XOR.rd] << "  " << out << "   ";
		decToHexa(reg[XOR.rd]);
		return counter + 4;
	}

	int XORI(instructions& XORI, map<string, int>& reg, int& counter)
	{
		reg[XORI.rd] = reg[XORI.rs1] ^ XORI.imm;
		int out;
		cout << endl << "operation: " << XORI.operation;
		out = decToBinary(reg[XORI.rs1]);
		cout << endl << "rs1: " << reg[XORI.rs1] << "  " << out << "   ";
		decToHexa(reg[XORI.rs1]);
		out = decToBinary(XORI.imm);
		cout << endl << "imm: " << XORI.imm << "  " << out << "   ";
		decToHexa(XORI.imm);
		out = decToBinary(reg[XORI.rd]);
		cout << endl << "rd: " << reg[XORI.rd] << "  " << out << "   ";
		decToHexa(reg[XORI.rd]);
		return counter + 4;
	}


	int ORI(instructions& ORI, map<string, int>& reg, int& counter)
	{
		reg[ORI.rd] = reg[ORI.rs1] ^ ORI.imm;

		int out;
		cout << endl << "operation: " << ORI.operation;
		out = decToBinary(reg[ORI.rs1]);
		cout << endl << "rs1: " << reg[ORI.rs1] << "  " << out << "   ";
		decToHexa(reg[ORI.rs1]);
		out = decToBinary(ORI.imm);
		cout << endl << "imm: " << ORI.imm << "  " << out << "   ";
		decToHexa(ORI.imm);
		out = decToBinary(reg[ORI.rd]);
		cout << endl << "rd: " << reg[ORI.rd] << "  " << out << "   ";
		decToHexa(reg[ORI.rd]);
		return counter + 4;
	}


	int SLTI(instructions& SLTI, map<string, int>& reg, int& counter)
	{
		if (reg[SLTI.rs1] < SLTI.imm)
			reg[SLTI.rd] = 1;
		else
			reg[SLTI.rd] = 0;
		int out;
		cout << endl << "operation: " << SLTI.operation;
		out = decToBinary(reg[SLTI.rs1]);
		cout << endl << "rs1: " << reg[SLTI.rs1] << "  " << out << "   ";
		decToHexa(reg[SLTI.rs1]);
		out = decToBinary(SLTI.imm);
		cout << endl << "imm: " << SLTI.imm << "  " << out << "   ";
		decToHexa(SLTI.imm);
		out = decToBinary(reg[SLTI.rd]);
		cout << endl << "rd: " << reg[SLTI.rd] << "  " << out << "   ";
		decToHexa(reg[SLTI.rd]);
		return counter + 4;
	}

	int SLTIU(instructions& SLTIU, map<string, int>& reg, int& counter)
	{
		if (reg[SLTIU.rs1] < (unsigned int)SLTIU.imm)
			reg[SLTIU.rd] = 1;
		else
			reg[SLTIU.rd] = 0;
		int out;
		cout << endl << "operation: " << SLTIU.operation;
		out = decToBinary(reg[SLTIU.rs1]);
		cout << endl << "rs1: " << reg[SLTIU.rs1] << "  " << out << "   ";
		decToHexa(reg[SLTIU.rs1]);
		out = decToBinary(SLTIU.imm);
		cout << endl << "imm: " << SLTIU.imm << "  " << out << "   ";
		decToHexa(SLTIU.imm);
		out = decToBinary(reg[SLTIU.rd]);
		cout << endl << "rd: " << reg[SLTIU.rd] << "  " << out << "   ";
		decToHexa(reg[SLTIU.rd]);
		return counter + 4;
	}

	int SLLI(instructions& SLLI, map<string, int>& reg, int& counter)
	{
		reg[SLLI.rd] = reg[SLLI.rs1] << SLLI.imm;
		int out;
		cout << endl << "operation: " << SLLI.operation;
		out = decToBinary(reg[SLLI.rs1]);
		cout << endl << "rs1: " << reg[SLLI.rs1] << "  " << out << "   ";
		decToHexa(reg[SLLI.rs1]);
		out = decToBinary(SLLI.imm);
		cout << endl << "imm: " << SLLI.imm << "  " << out << "   ";
		decToHexa(SLLI.imm);
		out = decToBinary(reg[SLLI.rd]);
		cout << endl << "rd: " << reg[SLLI.rd] << "  " << out << "   ";
		decToHexa(reg[SLLI.rd]);
		return counter + 4;
	}
	

	int ADDI(instructions& ADDI, map<string, int>& reg, int& counter)
	{
		reg[ADDI.rd] = reg[ADDI.rs1] + ADDI.imm;
		int out;
		cout << endl << "operation: " << ADDI.operation;
		out = decToBinary(reg[ADDI.rs1]);
		cout << endl << "rs1: " << reg[ADDI.rs1] << "  " << out << "   ";
		decToHexa(reg[ADDI.rs1]);
		out = decToBinary(ADDI.imm);
		cout << endl << "imm: " << ADDI.imm << "  " << out << "   ";
		decToHexa(ADDI.imm);
		out = decToBinary(reg[ADDI.rd]);
		cout << endl << "rd: " << reg[ADDI.rd] << "  " << out << "   ";
		decToHexa(reg[ADDI.rd]);
		return counter + 4;
	}

	int ANDI(instructions& ANDI, map<string, int>& reg, int& counter)
	{
		reg[ANDI.rd] = reg[ANDI.rs1] & ANDI.imm;
		int out;
		cout << endl << "operation: " << ANDI.operation;
		out = decToBinary(reg[ANDI.rs1]);
		cout << endl << "rs1: " << reg[ANDI.rs1] << "  " << out << "   ";
		decToHexa(reg[ANDI.rs1]);
		out = decToBinary(ANDI.imm);
		cout << endl << "imm: " << ANDI.imm << "  " << out << "   ";
		decToHexa(ANDI.imm);
		out = decToBinary(reg[ANDI.rd]);
		cout << endl << "rd: " << reg[ANDI.rd] << "  " << out << "   ";
		decToHexa(reg[ANDI.rd]);
		return counter + 4;
	}
	int BEQ(instructions& BEQ, map<string, int>& reg, int& counter) {
		if (reg[BEQ.rs1] == reg[BEQ.rs2])
		{
			int out;
			cout << endl << "operation: " << BEQ.operation;
			out = decToBinary(reg[BEQ.rs1]);
			cout << endl << "rs1: " << reg[BEQ.rs1] << "  " << out << "   ";
			decToHexa(reg[BEQ.rs1]);
			out = decToBinary(reg[BEQ.rs2]);
			cout << endl << "rs2: " << reg[BEQ.rs2] << "  " << out << "   ";
			decToHexa(reg[BEQ.rs2]);
			out = decToBinary(BEQ.off);
			cout << endl << "off: " << BEQ.off << "  " << out << "   ";
			decToHexa(BEQ.off);
			return counter + BEQ.off;
		}
		else
		{
			int out;
			cout << endl << "operation: " << BEQ.operation;
			out = decToBinary(reg[BEQ.rs1]);
			cout << endl << "rs1: " << reg[BEQ.rs1] << "  " << out << "   ";
			decToHexa(reg[BEQ.rs1]);
			out = decToBinary(reg[BEQ.rs2]);
			cout << endl << "rs2: " << reg[BEQ.rs2] << "  " << out << "   ";
			decToHexa(reg[BEQ.rs2]);
			out = decToBinary(BEQ.off);
			cout << endl << "off: " << BEQ.off << "  " << out << "   ";
			decToHexa(BEQ.off);
			return counter + 4;
		}
	};
	int BGE(instructions& BGE, map<string, int>& reg, int& counter) {
		if (reg[BGE.rs1] >= reg[BGE.rs2])
		{
			int out;
			cout << endl << "operation: " << BGE.operation;
			out = decToBinary(reg[BGE.rs1]);
			cout << endl << "rs1: " << reg[BGE.rs1] << "  " << out << "   ";
			decToHexa(reg[BGE.rs1]);
			out = decToBinary(reg[BGE.rs2]);
			cout << endl << "rs2: " << reg[BGE.rs2] << "  " << out << "   ";
			decToHexa(reg[BGE.rs2]);
			out = decToBinary(BGE.off);
			cout << endl << "off: " << BGE.off << "  " << out << "   ";
			decToHexa(BGE.off);
			return counter + BGE.off;
		}
		else
		{
			int out;
			cout << endl << "operation: " << BGE.operation;
			out = decToBinary(reg[BGE.rs1]);
			cout << endl << "rs1: " << reg[BGE.rs1] << "  " << out << "   ";
			decToHexa(reg[BGE.rs1]);
			out = decToBinary(reg[BGE.rs2]);
			cout << endl << "rs2: " << reg[BGE.rs2] << "  " << out << "   ";
			decToHexa(reg[BGE.rs2]);
			out = decToBinary(BGE.off);
			cout << endl << "off: " << BGE.off << "  " << out << "   ";
			decToHexa(BGE.off);
			return counter + 4;
		}

	};
	int BLT(instructions& BLT, map<string, int>& reg, int& counter) {
		if (reg[BLT.rs1] < reg[BLT.rs2])
		{
			int out;
			cout << endl << "operation: " << BLT.operation;
			out = decToBinary(reg[BLT.rs1]);
			cout << endl << "rs1: " << reg[BLT.rs1] << "  " << out << "   ";
			decToHexa(reg[BLT.rs1]);
			out = decToBinary(reg[BLT.rs2]);
			cout << endl << "rs2: " << reg[BLT.rs2] << "  " << out << "   ";
			decToHexa(reg[BLT.rs2]);
			out = decToBinary(BLT.off);
			cout << endl << "off: " << BLT.off << "  " << out << "   ";
			decToHexa(BLT.off);
			return counter + BLT.off;
		}
		else
		{
			int out;
			cout << endl << "operation: " << BLT.operation;
			out = decToBinary(reg[BLT.rs1]);
			cout << endl << "rs1: " << reg[BLT.rs1] << "  " << out << "   ";
			decToHexa(reg[BLT.rs1]);
			out = decToBinary(reg[BLT.rs2]);
			cout << endl << "rs2: " << reg[BLT.rs2] << "  " << out << "   ";
			decToHexa(reg[BLT.rs2]);
			out = decToBinary(BLT.off);
			cout << endl << "off: " << BLT.off << "  " << out << "   ";
			decToHexa(BLT.off);
			return counter + 4;
		}
	};

	int BNE(instructions& BNE, map<string, int>& reg, int& counter) {
		if (reg[BNE.rs1] != reg[BNE.rs2])
		{
			int out;
			cout << endl << "operation: " << BNE.operation;
			out = decToBinary(reg[BNE.rs1]);
			cout << endl << "rs1: " << reg[BNE.rs1] << "  " << out << "   ";
			decToHexa(reg[BNE.rs1]);
			out = decToBinary(reg[BNE.rs2]);
			cout << endl << "rs2: " << reg[BNE.rs2] << "  " << out << "   ";
			decToHexa(reg[BNE.rs2]);
			out = decToBinary(BNE.off);
			cout << endl << "off: " << BNE.off << "  " << out << "   ";
			decToHexa(BNE.off);
			return counter + BNE.off;
		}
		else
		{
			int out;
			cout << endl << "operation: " << BNE.operation;
			out = decToBinary(reg[BNE.rs1]);
			cout << endl << "rs1: " << reg[BNE.rs1] << "  " << out << "   ";
			decToHexa(reg[BNE.rs1]);
			out = decToBinary(reg[BNE.rs2]);
			cout << endl << "rs2: " << reg[BNE.rs2] << "  " << out << "   ";
			decToHexa(reg[BNE.rs2]);
			out = decToBinary(BNE.off);
			cout << endl << "off: " << BNE.off << "  " << out << "   ";
			decToHexa(BNE.off);
			return counter + 4;
		}
			
	};

	int BGEU(instructions& BGEU, map<string, int>& reg, int& counter) {
		if ((unsigned int)reg[BGEU.rs1] >= (unsigned int)reg[BGEU.rs2])
		{
			int out;
			cout << endl << "operation: " << BGEU.operation;
			out = decToBinary(reg[BGEU.rs1]);
			cout << endl << "rs1: " << reg[BGEU.rs1] << "  " << out << "   ";
			decToHexa(reg[BGEU.rs1]);
			out = decToBinary(reg[BGEU.rs2]);
			cout << endl << "rs2: " << reg[BGEU.rs2] << "  " << out << "   ";
			decToHexa(reg[BGEU.rs2]);
			out = decToBinary(BGEU.off);
			cout << endl << "off: " << BGEU.off << "  " << out << "   ";
			decToHexa(BGEU.off);
			return counter + BGEU.off;
		}
		else
		{
			int out;
			cout << endl << "operation: " << BGEU.operation;
			out = decToBinary(reg[BGEU.rs1]);
			cout << endl << "rs1: " << reg[BGEU.rs1] << "  " << out << "   ";
			decToHexa(reg[BGEU.rs1]);
			out = decToBinary(reg[BGEU.rs2]);
			cout << endl << "rs2: " << reg[BGEU.rs2] << "  " << out << "   ";
			decToHexa(reg[BGEU.rs2]);
			out = decToBinary(BGEU.off);
			cout << endl << "off: " << BGEU.off << "  " << out << "   ";
			decToHexa(BGEU.off);
			return counter + 4;
		}
	};

	int BLTU(instructions& BLTU, map<string, int>& reg, int& counter) {
		if ((unsigned int)reg[BLTU.rs1] < (unsigned int)reg[BLTU.rs2])
		{
			int out;
			cout << endl << "operation: " << BLTU.operation;
			out = decToBinary(reg[BLTU.rs1]);
			cout << endl << "rs1: " << reg[BLTU.rs1] << "  " << out << "   ";
			decToHexa(reg[BLTU.rs1]);
			out = decToBinary(reg[BLTU.rs2]);
			cout << endl << "rs2: " << reg[BLTU.rs2] << "  " << out << "   ";
			decToHexa(reg[BLTU.rs2]);
			out = decToBinary(BLTU.off);
			cout << endl << "off: " << BLTU.off << "  " << out << "   ";
			decToHexa(BLTU.off);
			return counter + BLTU.off;
		}
		else {
			int out;
			cout << endl << "operation: " << BLTU.operation;
			out = decToBinary(reg[BLTU.rs1]);
			cout << endl << "rs1: " << reg[BLTU.rs1] << "  " << out << "   ";
			decToHexa(reg[BLTU.rs1]);
			out = decToBinary(reg[BLTU.rs2]);
			cout << endl << "rs2: " << reg[BLTU.rs2] << "  " << out << "   ";
			decToHexa(reg[BLTU.rs2]);
			out = decToBinary(BLTU.off);
			cout << endl << "off: " << BLTU.off << "  " << out << "   ";
			decToHexa(BLTU.off);

			return counter + 4;
		}
	};
	int JAL(instructions& JAL, map<string, int>& reg, int& counter)
	{
		return counter + JAL.off;

	};
	int FENCE(instructions& FENCE, map<string, int>& reg, int& counter) {
		return -1;
	};
	


	int ECALL(instructions& ECALL, map<string, int>& reg, int& counter) {
		return -1;
	};

	int EBREAK(instructions& EBREAK, map<string, int>& reg, int& counter) {
		return -1;
	};

	int function_choose(instructions& func, map<string,int>& reg, map<string, int>& mem, int& counter)
	{
		if (func.operation == "add")
		{
			return add(func, reg, counter);
		}
		else if (func.operation == "ADDI")
		{
			return ADDI(func, reg, counter);
		}
		else if (func.operation == "sub")
		{
			return sub(func, reg, counter);
		}
		else if (func.operation == "OR")
		{
			return OR(func, reg, counter);
		}
		else if (func.operation == "XOR")
		{
			return XOR(func, reg, counter);
		}
		else if (func.operation == "XORI")
		{
			return XORI(func, reg, counter);
		}
		else if (func.operation == "ORI")
		{
			return ORI(func, reg, counter);
		}
		else if (func.operation == "AND")
		{
			return AND(func, reg, counter);
		}
		else if (func.operation == "ANDI")
		{
			return ANDI(func, reg, counter);
		}
		else if (func.operation == "SLT")
		{
			return SLT(func, reg, counter);
		}
		else if (func.operation == "SLTU")
		{
			return SLTU(func, reg, counter);
		}
		else if (func.operation == "SLTI")
		{
			return SLTI(func, reg, counter);
		}
		else if (func.operation == "SRA")
		{
			return SRA(func, reg, counter);
		}
		else if (func.operation == "SRAI")
		{
			return SRAI(func, reg, counter);
		}
		else if (func.operation == "SRL")
		{
			return SRL(func, reg, counter);
		}
		else if (func.operation == "SLL")
		{
			return SLL(func, reg, counter);
		}
		else if (func.operation == "SLLI")
		{
			return SLLI(func, reg, counter);
		}

		else if (func.operation == "FENCE")
		{
			FENCE(func, reg, counter);
		}
		else if (func.operation == "EBREAK")
		{
			EBREAK(func, reg, counter);
		}
		else if (func.operation == "ECALL")
		{
			ECALL(func, reg, counter);
		}
		else if (func.operation == "BEQ")
		{
			return BEQ(func, reg, counter);
		}
		else if (func.operation == "BGE")
		{
			return BGE(func, reg, counter);
		}
		else if (func.operation == "BNE")
		{
			return BNE(func, reg, counter);
		}
		else if (func.operation == "BGEU")
		{
			return BGEU(func, reg, counter);

		}
		else if (func.operation == "BLT")
		{
			return BLT(func, reg, counter);
		}
		else if (func.operation == "BLTU")
		{
			return BLTU(func, reg, counter);
		}
		else if (func.operation == "BGEBLT")
		{
			return BLT(func, reg, counter);
		}
		else if (func.operation == "lw")
		{
		return lw(func, reg, mem,counter);
		}
		else if (func.operation == "lh")
		{
		return lh(func, reg,mem,counter);
		}
		else if (func.operation == "lb")
		{
		return lb(func, reg, mem, counter);
		}
		else if (func.operation == "lhu")
		{
		return lhu(func, reg, mem, counter);
		}
		else if (func.operation == "lbu")
		{
		return lbu(func, reg, mem, counter);
		}
		else if (func.operation == "sw")
		{
		return sw(func, reg, mem, counter);
		}
		else if (func.operation == "sh")
		{
		return sh(func, reg, mem, counter);
		}
		else if (func.operation == "sb")
		{
		return sb(func, reg, mem, counter);
		}
		else if (func.operation == "JALR")
		{
		return JALR(func, reg);
		}
		else if (func.operation == "JAL")
		{
		return JAL(func, reg,counter);
		}
	}

};

int main()
{
	instructions AND;
	ifstream read,data;
	ofstream datao;
	string filename = "loop.txt";
	read.open("string copy.txt");
	data.open("data file.txt");
	int x[32];

	if (datao.fail())
	{
		cout << "*** ERROR: Cannot open " << filename << endl;
		return 1;	// failure return
	}  // end if
	for (int i = 0; i < 32; i++)
	{
		data >> x[i];
	}
	/*for (int i = 0; i < 32; i++)
	{
		cout << x[i];
	}*/
	map<string, int> reg;
	map<string, int> mem;
	cout << endl;
	cout << "Enter 32 memory locations each entry followed by enter: " << endl;
	for (int l = 0; l < 32; l++)
	{
		cin >> x[l];
	}
	// registers
	// zero
	mem["x0"] = x[0];
	//return address
	mem["x1"] = x[1];
	// stack pointer
	mem["x2"] = x[2];
	// global pointer
	mem["x3"] = x[3];
	// thread pointer
	mem["x4"] = x[4];
	// temporaries
	mem["x5"] = x[5];
	mem["x6"] = x[6];
	mem["x7"] = x[7];
	mem["x28"] = x[28];
	mem["x29"] = x[29];
	mem["x30"] = x[30];
	mem["x31"] = x[31];
	// saved
	mem["x8"] = x[8];
	mem["x9"] = x[9];
	mem["x18"] = x[18];
	mem["x19"] = x[19];
	mem["x20"] = x[20];
	mem["x21"] = x[21];
	mem["x22"] = x[22];
	mem["x23"] = x[23];
	mem["x24"] = x[24];
	mem["x25"] = x[25];
	mem["x26"] = x[26];
	mem["x27"] = x[27];
	// function arguments
	mem["x10"] = x[10];
	mem["x11"] = x[11];
	mem["x12"] = x[12];
	mem["x13"] = x[13];
	mem["x14"] = x[14];
	mem["x15"] = x[15];
	mem["x16"] = x[16];
	mem["x17"] = x[17];


	// registers
	// zero
	reg["x0"] = 0;
	//return address
	reg["x1"] = 0;
	// stack pointer
	reg["x2"] = 0;
	// global pointer
	reg["x3"] = 0;
	// thread pointer
	reg["x4"] = 0;
	// temporaries
	reg["x5"] = 0;
	reg["x6"] = 0;
	reg["x7"] = 0;
	reg["x28"] = 0;
	reg["x29"] = 0;
	reg["x30"] = 0;
	reg["x31"] = 0;
	// saved
	reg["x8"] = 0;
	reg["x9"] = 0;
	reg["x18"] = 0;
	reg["x19"] = 0;
	reg["x20"] = 0;
	reg["x21"] = 0;
	reg["x22"] = 0;
	reg["x23"] = 0;
	reg["x24"] = 0;
	reg["x25"] = 0;
	reg["x26"] = 0;
	reg["x27"] = 0;
	// function arguments
	reg["x10"] = 0;
	reg["x11"] = 0;
	reg["x12"] = 0;
	reg["x13"] = 0;
	reg["x14"] = 0;
	reg["x15"] = 0;
	reg["x16"] = 0;
	reg["x17"] = 0;
	data.close();

	instructions OR ;
	vector<instructions> allinstructions;
	map<int, instructions> program;
	string operation,rd,rs1,rs2;
	int s = 0;
	string find = "x";
	string f;
	while (!read.eof()) {
		s++;
		read >> AND.operation;
		cout << endl << AND.operation << endl;
		if (AND.operation == "ADDI" || AND.operation == "SLTI" || AND.operation == "SLTIU" || AND.operation == "XORI" || AND.operation == "ORI" || AND.operation == "ANDI" || AND.operation == "SLLI" || AND.operation == "SRLI" || AND.operation == "SRAI")
		{
			read.ignore(1);
			read >> AND.rd;
			read.ignore(2);
			read >> AND.rs1;
			read.ignore(2);
			read >> AND.imm;
			//AND.pc = counter;
		}
		else if (AND.operation == "BEQ" || AND.operation == "BGE" || AND.operation == "BLT" || AND.operation == "BNE" || AND.operation == "BGEU" || AND.operation == "BLTU")
		{
			read.ignore(1);
			read >> AND.rs1;
			read.ignore(2);
			read >> AND.rs2;
			read.ignore(2);
			read >> AND.off;
			//AND.pc = counter;
			
		}
		else if (AND.operation == "lw" || AND.operation == "lh" || AND.operation == "lb" || AND.operation == "lbu" || AND.operation == "lhu"|| AND.operation == "sw" || AND.operation == "sh" || AND.operation == "sb" )
		{
			read.ignore(1);
			read >> AND.rd;
			read.ignore(2);
			read >> AND.off;
			read.ignore(2);
			read >> AND.rs1;
			read.ignore(2);
			//AND.pc = counter;
		}
		else if (AND.operation == "sw" || AND.operation == "sh" || AND.operation == "sb"|| AND.operation == "JALR")
		{
			read.ignore(1);
			read >> AND.rs2;
			read.ignore(2);
			read >> AND.off;
			read.ignore(2);
			read >> AND.rs1;
			read.ignore(2);
			//AND.pc = counter;
		}
		else if (AND.operation == "JAL")
		{
			read.ignore(1);
			read >> AND.rd;
			read.ignore(2);
			read >> AND.off;
			read.ignore(1);
			//AND.pc = counter;
		}
		else {
			read.ignore(1);
			read >> AND.rd;
			read.ignore(2);
			read >> AND.rs1;
			read.ignore(2);
			read >> AND.rs2;
			//AND.pc = counter;
		}
		/*cout << AND.operation << endl;
		cout << AND.rd << endl;
		cout << AND.rs1 << endl;
		cout << AND.off << endl;
		cout << AND.imm << endl;*/
		allinstructions.push_back(AND);
		allinstructions.resize(s);
	
		
		//function.function_choose(AND, reg);
		/*for (int j = 0; j < s; j++)
		{
			cout << allinstructions[j].rd << endl;
			cout << allinstructions[j].rs1 << endl;
			cout << allinstructions[j].rs2 << endl;
			cout << allinstructions[j].imm << endl;
		}*/
	}
	functions function;
	int counter = 0;
	
	for (int y = 0; y < s; y++)
	{
		
		program[counter] = allinstructions[y];
		
		counter = counter + 4;
		//allinstructions[y].pc = function.function_choose(allinstructions[y - 1], reg);
	}
	//cout << program[16].operation << endl;
	int j = 0;
	/*for (int y = 0; y < s; y++)
	{
		cout << program[j].operation << endl;
		//j = function.function_choose(program[j], reg, j);
		//allinstructions[y].pc = function.function_choose(allinstructions[y - 1], reg);
	}*/
	string addr,subadd;
	//cout << program[8].operation << endl;
	cout << endl << "Enter the starting address: ";
	cin >> addr;
	subadd = addr.substr(3, addr.size());
	int p = stoi(subadd);
	cout << endl << p;
	//int p=0;
	
	while(p != -1)
	{
		cout << "pc = " << p << endl;
		
		p = function.function_choose(program[p], reg,mem,p);
		cout << "pc = "<<p << endl;
		reg["x0"] = 0;
		cout << endl;
		for (int i = 0; i < 32; i++)
		{
			
			f = find + to_string(i);
			
			cout << find << i << "  " << reg[f] << endl;
		}
		
	
		//cout <<endl<< p;
		//function.function_choose(program[pc], reg);
		
		//allinstructions[y].pc = function.function_choose(allinstructions[y - 1], reg);
	}

	int i = 0;
		//cout <<endl<< AND.rd;
	/*while (j<s)
	{
		program[AND.pc] = allinstructions[j];
		
		function.function_choose(allinstructions[j], reg);
		j++;
		//cout << AND.pc;
		//i = i + 4;
	}*/

	datao.open("data file.txt");
	
	for (int i = 0; i < 32; i++)
	{
		string out = "x";
		string regi = to_string(i);
		string regis = out + regi;
		//cout << regis;
		
		cout << mem[regis] << endl;
		datao << mem[regis] << endl;

	}
	
	datao.close();
	read.close();
	
	return 0;
}

