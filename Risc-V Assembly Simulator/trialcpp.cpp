/*
#pragma warning(disable : 4996)
using namespace std;

struct instructions {
public:
	int regFile[31];
	string operation;
	int rd, rs1, rs2, imm, pc;
	//void shamt(int rs1);

};



string signextend16(string extend)
{
	string zero = "0000000000000000";
	string one = "1111111111111111";
	
	if (extend[0] == '0')
	{
		return zero + extend;
	}

	else {
		return one + extend;
	}
}

string zeroextend16(string extend)
{
	string zero = "0000000000000000";
	return zero + extend;
}


string signextend12(string extend)
{
	string zero = "00000000000000000000";
	string one = "11111111111111111111";

	if (extend[0] == '0')
	{
		return zero + extend;
	}

	else {
		return one + extend;
	}
}
void cal_addrss(string offset)
{
	//string newoffset = signextend12(offset);
	string newoffset = "100001";
	long x = stoi(newoffset);
	cout << x;

}


int main()
{
	char str[32];
	 int i=5;
	 
	 _itoa(15,str, 2);
	cout << str<<endl;
	int x = stoi(str);
	cout << x;
	return 0;
}*/