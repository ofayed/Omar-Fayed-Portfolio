#include "ReservationStation.h"
#include "RegStatus.h"
#include "Instruction.h"
#include<vector>
#include<string>
#include<sstream>
#include <fstream>

//methods

//omar's code
vector<Instruction> openFile(string filename) {
	ifstream code;
	code.open(filename);

	if (!code.is_open())
	{
		cout << "could not open file" << "\n";
	}
	int size = 0;
	string inst, r1, r2, r3;
	vector<string> instruction;
	vector<int> rd, rs1, rs2;


	while (code >> inst)
	{
		size++;

		instruction.push_back(inst);
		if (inst == "ADD" || inst == "ADDI" || inst == "NOR" || inst == "MUL" || inst == "BEQ")
		{
			code >> r1 >> r2 >> r3;
			r1.erase(remove(r1.begin(), r1.end(), 'R'), r1.end());
			r2.erase(remove(r2.begin(), r2.end(), 'R'), r2.end());
			r3.erase(remove(r3.begin(), r3.end(), 'R'), r3.end());
			rd.push_back(stoi(r1));
			rs1.push_back(stoi(r2));
			rs2.push_back(stoi(r3));
		}
		else if (inst == "LOAD" || inst == "STORE")
		{
			code >> r1 >> r2 >> r3;
			r1.erase(remove(r1.begin(), r1.end(), 'R'), r1.end());
			r2.erase(remove(r2.begin(), r2.end(), 'R'), r2.end());
			r3.erase(remove(r3.begin(), r3.end(), 'R'), r3.end());
			r3.erase(remove(r3.begin(), r3.end(), ')'), r3.end());
			r3.erase(remove(r3.begin(), r3.end(), '('), r3.end());
			rd.push_back(stoi(r1));
			rs1.push_back(stoi(r2));
			rs2.push_back(stoi(r3));
		}
		else if (inst == "JAL")
		{

			code >> r1;
			rd.push_back(stoi(r1));
			rs1.resize(size);
			rs2.resize(size);
		}
		else if (inst == "NEG")
		{

			code >> r1;
			code >> r2;
			r1.erase(remove(r1.begin(), r1.end(), 'R'), r1.end());
			r2.erase(remove(r2.begin(), r2.end(), 'R'), r2.end());
			rd.push_back(stoi(r1));
			rs1.push_back(stoi(r2));

			rs2.resize(size);
		}
		else {
			rs1.resize(size);
			rs2.resize(size);
			rd.resize(size);

		}

	}


	vector<Instruction> in(rd.size());
	for (int i = 0; i < rd.size(); i++)
	{
		/*cout << instruction[i] << " " << rd[i] << " " << rs1[i] << " " << rs2[i] << "\n";*/

		if (instruction[i] == "LOAD" || instruction[i] == "STORE")
		{
			in[i].OP = instruction[i];
			in[i].rA = rd[i];
			in[i].rB = rs2[i];
			in[i].rC = rs1[i];
		}
		else {
			in[i].OP = instruction[i];
			in[i].rA = rd[i];
			in[i].rB = rs1[i];
			in[i].rC = rs2[i];
		}

	}

	return in;

}

void CalcInst(string inst, int rs1, int rs2, int& rs3) {
	if (inst == "ADD" || inst == "ADDI" || inst == "LOAD" || inst == "STORE") rs3 = rs1 + rs2;
	else if (inst == "MUL") rs3 = rs1 * rs2;
	else if (inst == "NOR")
	{
		int OR;
		OR = rs1 | rs2;
		rs3 = ~OR;
	}
	else if (inst == "NEG") {
		string rb, ra;
		rb = to_string(rs1);
		ra = rb;
		for (int i = rb.size() - 1; i >= 0; i--)
		{
			if (rb[i] == '1')
				ra[i] = '0';
			else
			{
				ra[i] = '1';
				break;
			}
		}
		rs3 = stoi(rb);
	}
	else if (inst == "BEQ") rs3 = rs1 + rs2 + 1;
}

void print(vector<Instruction> table, float ipc, float mis, int total)
{
	cout << "Issued  \t \t" << "Started \t\t" << "Finished \t\t " << "Written";
	for (int i = 0; i < table.size(); i++)
	{
		cout << "\n" << table[i].begIssue << " \t \t  \t" << table[i].begExec << " \t \t  \t" << table[i].endExec << " \t \t  \t" << table[i].begWB;
	}
	cout << "\n" << "Total Execution Time (number of clock cycles): " << total;
	cout << "\n" << "IPC : " << ipc;
	cout << "\n" << "Branch Misprediction Percentatge : " << mis;

}

vector<int> MEM(50,0);


//Karim's code
int ISSUE(vector<Instruction>& inst, vector<RegStatus>& regStatus, vector<ReservationStation>& RS, vector<int>& Regs);

void EXECUTE(vector<Instruction>& inst, vector<RegStatus>& regStatus, vector<ReservationStation>& RS, vector<int>& Regs);

void WRITERESULT(vector<Instruction>& inst, vector<RegStatus>& regStatus, vector<ReservationStation>& RS, vector<int>& Regs);


//Defines
const int NUM_RS_Load = 2;
const int NUM_RS_Store = 2;
const int NUM_RS_Beq = 1;
const int NUM_RS_Jal_Ret = 1;
const int NUM_RS_ADD_ADDI = 3;
const int NUM_RS_NEG = 1;
const int NUM_RS_NOR = 1;
const int NUM_RS_Mult = 1;

//Clock Cycle
const int Load_Cycle = 4;
const int Store_Cycle = 3;
const int Beq_Cycle = 1;
const int JAL_RET_Cycle = 1;
const int Add_Cycle = 2;
const int Neg_Cycle = 1;
const int Nor_Cycle = 1;
const int Mult_Cycle = 8;

const int Issue_Cycle = 1;
const int WB_Cycle = 1;


int Clock = 0;
bool Done = true;
int PC=0;

int totalWB = 0;

const int ZERO_REG = 0;
const int RegStatEmpty = 1000;
const int operandA = 1001;
const int OperandInit = 1002;


int ISSUE(vector<Instruction>& inst, vector<RegStatus>& regStatus, vector<ReservationStation>& RS, vector<int>& Regs) {




	int r = 0;
	bool RS_Free = false;

	if (PC >= inst.size()) {
		return 0;
	}

	Instruction in = inst[PC];
	

	/*vector<ReservationStation> RS = { Load1, Load2,
		Store1, Store2, Beq, Jal_Ret, ADD1, ADD2, ADD3,
		Neg, NOR, MULT };*/
		//first check if there is reservation station that is empty
	if (in.OP == "LOAD") {
		for (int i = 0; i < 2; i++) {
			if (!RS[i].busy) {
				r = i;
				PC++;
				RS[i].Op = in.OP;
				RS_Free = true;
				break;
			}
		}

		if (!RS_Free) {
			return 1;
		}

	}
	else if (in.OP == "STORE") {
		for (int i = 2; i < 4; i++) {
			if (!RS[i].busy) {
				r = i;
				PC++;
				RS[i].Op = in.OP;
				RS_Free = true;
				break;
			}
		}
		if (!RS_Free) {
			return 1;
		}

	}
	else if (in.OP == "BEQ") {
		int i = 4;
		if (!RS[i].busy) {
			r = i;
			PC++;
			RS[i].Op = in.OP;
			RS_Free = true;
		}

		if (!RS_Free) {
			return 1;
		}

	}
	else if (in.OP == "JAL" || in.OP == "RET") {
		int i = 5;
		if (!RS[i].busy) {
			r = i;
			PC++;
			RS[i].Op = in.OP;
			RS_Free = true;
		}

		if (!RS_Free) {
			return 1;
		}
	}
	else if (in.OP == "ADD" || in.OP == "ADDI") {
		//cout << "enterd";
		for (int i = 6; i < 9; i++) {

			if (!RS[i].busy) {
				//cout << "entered";
				r = i;
				PC++;
				RS[i].Op = in.OP;
				RS_Free = true;
				break;
			}
		}

		if (!RS_Free) {
			return 1;
		}
	}
	else if (in.OP == "NEG") {
		int i = 9;
		if (!RS[i].busy) {
			r = i;
			PC++;
			RS[i].Op = in.OP;
			RS_Free = true;
		}

		if (!RS_Free) {
			return 1;
		}
	}
	else if (in.OP == "NOR") {
		int i = 10;
		if (!RS[i].busy) {
			r = i;
			PC++;
			RS[i].Op = in.OP;
			RS_Free = true;
		}

		if (!RS_Free) {
			return 1;
		}
	}
	else if (in.OP == "MUL") {
		int i = 11;
		if (!RS[i].busy) {
			r = i;
			PC++;
			RS[i].Op = in.OP;
			RS_Free = true;
		}

		if (!RS_Free) {
			return 1;
		}

	}

	//LOAD rA, offset(rB)
	if (in.OP == "LOAD") {

		if (regStatus[in.rB].Qi != (RegStatEmpty))
		{
			RS[r].Qj = regStatus[in.rB].Qi;
		}
		else {
			RS[r].Vj = Regs[in.rB];
			RS[r].Qj = operandA;
		}

		RS[r].A = in.rC;
		RS[r].busy = true;
		regStatus[in.rA].Qi = r; //destination
	}
	//STORE rA, offset(rB)
	else if (in.OP == "STORE") {

		if (regStatus[in.rB].Qi != (RegStatEmpty)) {
			RS[r].Qj = regStatus[in.rB].Qi;
		}
		else {
			RS[r].Vj = Regs[in.rB];
			RS[r].Qj = operandA;
		}
		RS[r].A = in.rC;
		RS[r].busy = true;

		if (regStatus[in.rA].Qi != (RegStatEmpty)) {
			RS[r].Qk = regStatus[in.rA].Qi;
		}
		else {
			RS[r].Vk = Regs[in.rA];
			RS[r].Qk = operandA;
		}

	}
	//JAL label
	else if (in.OP == "JAL") {
		RS[r].A = in.rA;
		RS[r].busy = true;
	}
	//BEQ rA, rB, offset
	else if (in.OP == "BEQ") {
		if (regStatus[in.rA].Qi != (RegStatEmpty)) {
			RS[r].Qj = regStatus[in.rA].Qi;
		}
		else {
			RS[r].Vj = Regs[in.rA];
			RS[r].Qj = operandA;
		}


		if (regStatus[in.rB].Qi != RegStatEmpty) {
			RS[r].Qk = regStatus[in.rB].Qi;
		}
		else {
			RS[r].Vk = Regs[in.rB];
			RS[r].Qk = operandA;
		}
		RS[r].busy = true;
		RS[r].A = in.rC;

	}
	//ADDI rA, rB, imm
	else if (in.OP == "ADDI") {

		if (regStatus[in.rB].Qi != (RegStatEmpty)) {
			RS[r].Qj = regStatus[in.rB].Qi;
		}
		else {
			RS[r].Vj = Regs[in.rB];
			RS[r].Qj = operandA;
		}

		RS[r].A = in.rC;

		RS[r].busy = true;
		regStatus[in.rA].Qi = r;
	}
	else if (in.OP == "NEG") {

		if (regStatus[in.rB].Qi != (RegStatEmpty)) {
			RS[r].Qj = regStatus[in.rB].Qi;
		}
		else {
			RS[r].Vj = Regs[in.rB];
			RS[r].Qj = operandA;
		}

		RS[r].busy = true;
		regStatus[in.rA].Qi = r;

	}
	//add, nor, mul
	else {

		if (regStatus[in.rB].Qi != (RegStatEmpty)) {
			RS[r].Qj = regStatus[in.rB].Qi;
		}
		else {
			RS[r].Vj = Regs[in.rB];
			RS[r].Qj = operandA;
		}


		if (regStatus[in.rC].Qi != (RegStatEmpty)) {
			RS[r].Qk = regStatus[in.rC].Qi;
		}
		else {
			RS[r].Vk = Regs[in.rC];
			RS[r].Qk = operandA;
		}

		RS[r].busy = true;
		regStatus[in.rA].Qi = r;
	}

	inst[PC - 1].begIssue = Clock;
	RS[r].indexOfInst = PC - 1;
	RS[r].IssueCycle = 0;

	return 2;
}

void EXECUTE(vector<Instruction>& inst, vector<RegStatus>& regStatus, vector<ReservationStation>& RS, vector<int>& Regs) {


	vector<string> load_store;
	
	for (int r = 0; r < RS.size(); r++) {

		if (RS[r].busy == true) {
			//cout << "enteredif";
			if (RS[r].IssueCycle >= Issue_Cycle) {
				
				//LOAD rA, offset(rB)
				if (RS[r].Op == "LOAD") {
					load_store.push_back(RS[r].Op);
					if (RS[r].Qj == operandA && load_store[0] == "LOAD") {

						if (inst[RS[r].indexOfInst].begExec == 0) {
							inst[RS[r].indexOfInst].begExec = Clock;
						}

						RS[r].ExecuteCycle++;

						if (RS[r].ExecuteCycle == Load_Cycle) {

							//create MEM vector
							RS[r].A = RS[r].Vj + RS[r].A; //compute address
							RS[r].result = MEM[RS[r].A]; //compute result
							RS[r].resultReady = true;
							inst[RS[r].indexOfInst].endExec = Clock;
							RS[r].ExecuteCycle = 0;
							RS[r].IssueCycle = 0;
							load_store.erase(load_store.begin());

						}
					}

				}
				//STORE rA, offset(rB)
				else if (RS[r].Op == "STORE") {

					load_store.push_back(RS[r].Op);
					if (RS[r].Qj == operandA && load_store[0] == "STORE") {

						//Qj is rb and Qk is ra
						if (inst[RS[r].indexOfInst].begExec == 0) {
							inst[RS[r].indexOfInst].begExec = Clock;
						}

						RS[r].ExecuteCycle++;

						if (RS[r].ExecuteCycle == Store_Cycle) {

							//create MEM vector
							RS[r].A = RS[r].Vj + RS[r].A; //compute address
							RS[r].resultReady = true;
							inst[RS[r].indexOfInst].endExec = Clock;
							RS[r].ExecuteCycle = 0;
							RS[r].IssueCycle = 0;
							load_store.erase(load_store.begin());

						}

					}

				}
				//JAL label
				else if (RS[r].Op == "JAL") {

					if (inst[RS[r].indexOfInst].begExec == 0) {
						
						inst[RS[r].indexOfInst].begExec = Clock;
					}

					RS[r].ExecuteCycle++;

					if (RS[r].ExecuteCycle == JAL_RET_Cycle) {
						
						//create MEM vector
						RS[r].result = PC + 1;
						PC = RS[r].A;
						//update PC in WB
						RS[r].resultReady = true;
						inst[RS[r].indexOfInst].endExec = Clock;
						
						RS[r].ExecuteCycle = 0;
						RS[r].IssueCycle = 0;
						
						
					}
				}
				else if (RS[r].Op == "RET") {
					if (inst[RS[r].indexOfInst].begExec == 0) {
						inst[RS[r].indexOfInst].begExec = Clock;
					}

					RS[r].ExecuteCycle++;

					if (RS[r].ExecuteCycle == JAL_RET_Cycle) {

						//create MEM vector

						PC = Regs[1];
						//update PC in WB
						RS[r].resultReady = true;
						inst[RS[r].indexOfInst].endExec = Clock;
						RS[r].ExecuteCycle = 0;
						RS[r].IssueCycle = 0;
						load_store.erase(load_store.begin());

					}
				}
				//BEQ rA, rB, offset
				else if (RS[r].Op == "BEQ") {
				
					if (RS[r].Qj == operandA && RS[r].Qk == operandA) {

						
						if (inst[RS[r].indexOfInst].begExec == 0) {
							inst[RS[r].indexOfInst].begExec = Clock;
						}

						RS[r].ExecuteCycle++;

						if (RS[r].ExecuteCycle == Beq_Cycle) {
							if (RS[r].Vj == RS[r].Vk) {
								PC = PC + 1 + RS[r].A;
							}

							RS[r].resultReady = true;
							inst[RS[r].indexOfInst].endExec = Clock;
							RS[r].ExecuteCycle = 0;
							RS[r].IssueCycle = 0;
							
						}

					}

				}
				//ADDI rA, rB, imm
				else if (RS[r].Op == "ADDI") {

					if (RS[r].Qj == operandA) {

						if (inst[RS[r].indexOfInst].begExec == 0) {
							inst[RS[r].indexOfInst].begExec = Clock;
						}

						RS[r].ExecuteCycle++;

						if (RS[r].ExecuteCycle == Add_Cycle) {

							RS[r].result = RS[r].Vj + RS[r].A;
							RS[r].resultReady = true;
							inst[RS[r].indexOfInst].endExec = Clock;
							RS[r].ExecuteCycle = 0;
							RS[r].IssueCycle = 0;
						}
					}
				}
				else if (RS[r].Op == "NEG") {

					if (RS[r].Qj == operandA) {

						if (inst[RS[r].indexOfInst].begExec == 0) {
							inst[RS[r].indexOfInst].begExec = Clock;
						}

						RS[r].ExecuteCycle++;
						if (RS[r].ExecuteCycle == Neg_Cycle) {

							RS[r].result = ~(RS[r].Vj);
							RS[r].resultReady = true;
							inst[RS[r].indexOfInst].endExec = Clock;
							RS[r].ExecuteCycle = 0;
							RS[r].IssueCycle = 0;
						}

					}

				}
				//add, nor, mul
				else if (RS[r].Op == "ADD") {
				//cout << "entered";
					if (RS[r].Qj == operandA && RS[r].Qk == operandA) {
						if (inst[RS[r].indexOfInst].begExec == 0) {
							inst[RS[r].indexOfInst].begExec = Clock;
						}

						RS[r].ExecuteCycle++;
						//cout << "Ex cycyle" << RS[r].ExecuteCycle;
						if (RS[r].ExecuteCycle == Add_Cycle) {
							//cout << "enteredif";

							RS[r].result = RS[r].Vj + RS[r].Vk;
							RS[r].resultReady = true;
							inst[RS[r].indexOfInst].endExec = Clock;
							RS[r].ExecuteCycle = 0;
							RS[r].IssueCycle = 0;
						}

					}
				}
				else if (RS[r].Op == "NOR") {

					if (RS[r].Qj == operandA && RS[r].Qk == operandA) {
						if (inst[RS[r].indexOfInst].begExec == 0) {
							inst[RS[r].indexOfInst].begExec = Clock;
						}

						RS[r].ExecuteCycle++;

						if (RS[r].ExecuteCycle == Nor_Cycle) {

							RS[r].result = ~(RS[r].Vj | RS[r].Vk);
							RS[r].resultReady = true;
							inst[RS[r].indexOfInst].endExec = Clock;
							RS[r].ExecuteCycle = 0;
							RS[r].IssueCycle = 0;
						}

					}
				}
				else if (RS[r].Op == "MUL") {
				
					if (RS[r].Qj == operandA && RS[r].Qk == operandA) {
						if (inst[RS[r].indexOfInst].begExec == 0) {
							inst[RS[r].indexOfInst].begExec = Clock;
						}

						RS[r].ExecuteCycle++;

						if (RS[r].ExecuteCycle == Mult_Cycle) {
							//cout << "check";
							RS[r].result = RS[r].Vj * RS[r].Vk;
						
							RS[r].resultReady = true;
							inst[RS[r].indexOfInst].endExec = Clock;
							RS[r].ExecuteCycle = 0;
							RS[r].IssueCycle = 0;
						}

					}

				}
			}
			else {
			//cout << "here";
			RS[r].IssueCycle++;
		}
		}

		
	}
}

void WRITERESULT(vector<Instruction>& inst, vector<RegStatus>& regStatus, vector<ReservationStation>& RS, vector<int>& Regs) {

	for (int r = 0; r < RS.size(); r++) {
		if (RS[r].resultReady) {
			//cout << "WB_cycle:" << WB_Cycle << "\n WriteBackCycle" << RS[r].WriteBackCycle<<"\n";
			if (RS[r].WriteBackCycle == WB_Cycle) {
				if (inst[RS[r].indexOfInst].begWB == 0)
					inst[RS[r].indexOfInst].begWB = Clock;

				for (int i = 0; i < inst.size(); i++)
					if (inst[i].OP == "STORE") {
						//cout << "memory1 \n";
						//cout << RS[r].A;
						MEM[RS[r].A] = RS[r].Vk;
						//cout << "memory2 \n";
						RS[r].busy = false;
					}

					else
					{
						
						for (int x = 0; x < Regs.size(); x++)
						{
							if (regStatus[x].Qi == r) {
								Regs[x] = RS[r].result;
								regStatus[x].Qi = RegStatEmpty;
							}
						}

						for (int x = 0; x < RS.size(); x++) {
							if (RS[x].Qj == r) {
								RS[x].Vj = RS[r].result;
								RS[x].Qj = operandA;
							}

							if (RS[x].Qk == r) {
								RS[x].Vk = RS[r].result;
								RS[x].Qk = operandA;
							}
						}

						RS[r].busy = false;
					}
				//cout << "entered";
				totalWB++;

				//RS reset
				RS[r].Qj = 0;
				RS[r].Qk = 0;
				RS[r].Vj = 0;
				RS[r].Vk = 0;
				RS[r].WriteBackCycle = 0;
				RS[r].resultReady = false;
				RS[r].busy = false;
			}

			else
				RS[r].WriteBackCycle++;

		}

	}
}
int main() {
	//Section for asking user to input instructions or from file but commented for faster testing

	/*int address, choice;
	//cout << "Enter starting address";
	//cin >> address;
	cout << "\n";
	//openfile("testcode.txt");
	cout << "Choose Whether to input instructions from file or from terminal \n" << " (1) From File \n" << " (2) From Terminal \n";
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		string filename;
		cout << "Enter File Name: ";
		cin >> filename;
		openfile(filename);
	}
	case 2:
	{
		bool check = true;
		string inst;
		vector<string> allinst;
		cout << " Please Enter the instructions below. Each instruction followed by Enter. Enter a BREAK instruction to stop the instructions";
		cout << "\n";
		while (check == true)
		{
			cin >> inst;
			if (inst[0] == 'B' && inst[1] == 'R' && inst[2] == 'E' && inst[3] == 'A' && inst[4] == 'K') { check = false; break; }
			else {
				allinst.push_back(inst);
			}
		}
		ofstream writeinst;
		writeinst.open("inputcode.txt");
		for (int i = 0; i < allinst.size(); i++)
		{
			writeinst << allinst[i];
			writeinst << "\n";

		}
		writeinst.close();
		openfile("inputcode.txt");
	}
	default:
		break;
	}
*/
	int initialPC;
	cout << "Enter starting PC: ";
	cin >> initialPC;
	cout << "\n";
	PC = PC + initialPC;
	vector<Instruction> instruction = openFile("testcode.txt");
	for (int i = 0; i < instruction.size(); i++) {
		cout << instruction[i].OP << " " << instruction[i].rA << " " << instruction[i].rB << " " << instruction[i].rC << "\n";
	}
	ReservationStation Load1("LOAD", OperandInit), Load2("LOAD", OperandInit);
	ReservationStation Store1("STORE", OperandInit), Store2("STORE", OperandInit);
	ReservationStation Beq("BEQ", OperandInit);
	ReservationStation Jal_Ret("JAL_RET", OperandInit);
	ReservationStation ADD1("ADD", OperandInit), ADD2("ADD", OperandInit), ADD3("ADD", OperandInit);
	ReservationStation Neg("NEG", OperandInit);
	ReservationStation NOR("NOR", OperandInit);
	ReservationStation MUL("MUL", OperandInit);
	
	vector<ReservationStation> RS = { Load1, Load2,
		Store1, Store2, Beq, Jal_Ret, ADD1, ADD2, ADD3,
		Neg, NOR, MUL };

	
	RegStatus F0(RegStatEmpty), F1(RegStatEmpty), F2(RegStatEmpty), F3(RegStatEmpty), F4(RegStatEmpty), F5(RegStatEmpty), F6(RegStatEmpty), F7(RegStatEmpty);

	vector<RegStatus> regStatus = { F0,F1, F2, F3, F4, F5, F6, F7 };

	//RO-R7, where R0 is always 0
	vector<int> Regs = { ZERO_REG,1,2,3,4,5,6,7 };
	
	do {
		Clock++;

		ISSUE(instruction, regStatus, RS, Regs);
		//cout << "issue \n";
		EXECUTE(instruction, regStatus, RS, Regs);
		//cout << "ex \n";
		WRITERESULT(instruction, regStatus, RS, Regs);
		//cout << "wr \n";
		//print function

		Done = false;
		//cout << totalWB;
		if (totalWB == instruction.size()-initialPC)
			Done = true;

	}

	while (!Done);
	
	print(instruction, (float)instruction.size() / Clock, 0, Clock);
}
