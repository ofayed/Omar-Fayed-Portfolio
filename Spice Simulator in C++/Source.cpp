/*#include <stdlib.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>


using namespace std;
/*

void get_brackets(vector< vector<char> > in)
{

	vector<char> brackets;
	int size = 0;
	//for (int i = 0; i < in.size(); i++)
	//{
	int j = 0;
	cout << in[0][j] << endl;
			if (in[0][j] == '(')
			{
				j++;
				while (in[0][j] !=')') 
				{
					
					size++;
					brackets.resize(size);
					brackets[size - 1] = in[0][j];
					j++;

				}
			}
			else {
				cout << j << endl;
				j++;
		}
	//}
	for (int k = 0; k < brackets.size(); k++)
	{
		cout << brackets[k] << " ";
	}
}*/
/*

struct mosfet
{
	string drain;
	string gate;
	string source= "vdd";
	string body;
	string type;
	int wire = 0;
};


int MOSFET_NUM = 1;
int wire = 1;
//drain, gate, source, body 

void NOT(char a, mosfet negate) {
	cout << 'M' << MOSFET_NUM << '/t' << out << '/t' << a << '/t' << "VDD" << '/t' << "VDD" << '/t' << "PMOS";
	cout << 'M' << MOSFET_NUM++ << '/t' << out << '/t' << a << '/t' << '0' << '/t' << '0' << '/t' << "NMOS";
}

void AND(char a, char b, mosfet AND) {
	cout << 'M' << MOSFET_NUM++ << '/t' << "W" << wire << '/t' << a << "VDD" << '/t' << "VDD" << '/t' << "PMOS";
	cout << 'M' << MOSFET_NUM++ << '/t' << "W" << wire << '/t' << b << "VDD" << '/t' << "VDD" << '/t' << "PMOS";

	cout << 'M' << MOSFET_NUM++ << '/t' << "W" << wire << '/t' << b << "W" << wire++ << '/t' << "W" << wire++ << '/t' << "NMOS";
	cout << 'M' << MOSFET_NUM++ << '/t' << "W" << wire++ << '/t' << a << '0' << '/t' << '0' << '/t' << "NMOS";

	cout << 'M' << MOSFET_NUM++ << '/t' << out << '/t' << "W" << wire << '/t' << "VDD" << '/t' << "VDD" << '/t' << "PMOS";
	cout << 'M' << MOSFET_NUM++ << '/t' << out << '/t' << "W" << wire << '/t' << '0' << '/t' << "0" << '/t' << "NMOS";

	//return NOT(wire);
}

void OR(char a, char b) {
	cout << 'M' << MOSFET_NUM++ << '/t' << "W" << wire << '/t' << a << "VDD" << '/t' << "VDD" << '/t' << "PMOS";
	cout << 'M' << MOSFET_NUM++ << '/t' << "W" << wire++ << '/t' << b << "W" << wire << '/t' << "W" << wire << '/t' << "PMOS";

	cout << 'M' << MOSFET_NUM++ << '/t' << "W" << wire++ << '/t' << b << '0' << '/t' << '0' << '/t' << "NMOS";
	cout << 'M' << MOSFET_NUM++ << '/t' << "W" << wire++ << '/t' << a << '0' << '/t' << '0' << '/t' << "NMOS";

	cout << 'M' << MOSFET_NUM++ << '/t' << out << '/t' << "W" << wire++ << '/t' << "VDD" << '/t' << "VDD" << '/t' << "PMOS";
	cout << 'M' << MOSFET_NUM++ << '/t' << out << '/t' << "W" << wire++ << '/t' << '0' << '/t' << "0" << '/t' << "NMOS";

	//return NOT(wire++);
}*/


/*

void checksign(vector<char> in)
{
	for (int i = 0; i < in.size(); i++)
	{
		if (in[i] == '&')
		{
			
			vector<char> anding(2);
			anding[0] = in[i-1];
			anding[1] = in[i+1];
	
		}
		if (in[i] == '|')
		{

			vector<char> oring(2);
			oring[0] = in[i - 1];
			oring[1] = in[i + 1];

		}
		if (in[i] == '`')
		{

			vector<char> negating(1);
			negating[0] = in[i - 1];
			

		}

	}
}


void not_gate(vector<char> in)
{
	for (int i = 0; i < in.size(); i++)
	{
		if (in[i] == '`')
		{
			char negated = in[i];
		}
		else{}
	}
}


int main()
{
	ifstream read;
	string filename = "input.txt";
	read.open("input.txt");
	char a,b,c,d,sign1,sign2,sign3;
	vector<char> singlein(30);
	vector< vector<char> > in(15, vector<char>(30));
	if (read.fail())
	{
		cout << "*** ERROR: Cannot open " << filename << endl;
		return 1;	// failure return
	}  // end if
	int n = 1;
	int x = 0;
	string line;
	//getline(read,line);
	//cout << line<<endl;
	
	while (!read.eof()) {
		read >> in[n-1][x];
		
		if (in[n - 1][x] == ';')
		{
			
			n++;

			x = 0;
			
			
		}
		else {
			if (in[n - 1][x] == ' ' || in[n - 1][x] == 'y' || in[n - 1][x] == '=')
			{

			}
			else
			{
				x++;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		int s = in[i].size();
		for (int j = 0; j < s; j++)
		{
			cout << in[i][j] << "  ";
		}
		cout << endl;
	}
	for (int i = 0; i < n; i++)
	{
		int s = in[i].size();
		for (int j = 1; j < s; j++)
		{
			if(in[i][0] == in[i][j])
			cout << in[i][j] << "incorrect input";
		}
		cout << endl;
	}
	
	/*
		cout<< a<<endl;
		cout << sign1<<endl;
		cout << b<<endl;
		cout << sign2<<endl;
		cout << c<<endl;
		cout << sign3<<endl;
	*/
	//get_brackets(in);
//	return 0;
//}*/