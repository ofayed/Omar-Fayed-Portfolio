#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include<vector>
#include <sstream>
#include <math.h>
#include <chrono>
using namespace std::chrono;
using namespace std;


// function that swaps two cells on the grid
void swap(int x1, int y1, vector<vector<int>>& sqgrid, int x2, int y2)
{
	int valtmp;

	valtmp = sqgrid[x1][y1];
	sqgrid[x1][y1] = sqgrid[x2][y2];

	sqgrid[x2][y2] = valtmp;
}

//function that prints the grid with the correspondinh total wire length
void print(vector<vector<int>> sqgrid, int hpwl, int x, int y)
{
	cout << "Total wire length = " << hpwl << "\n";
	for (int i = 0; i < x; i++)
	{
		for (int k = 0; k < y; k++)
		{
			if (sqgrid[i][k] == -1) cout << "1";

			else cout << "0";
			cout << "\t";
		}
		cout << "\n";
	}




}

// function that calculates hpwl of a single connection
int hpwl(int xmin, int xmax, int ymin, int ymax)
{
	return ((xmax - xmin) + (ymax - ymin));
}


// function that calculates hpwl for all connections of nets
int maxhpwl(vector<vector<int>> cellList, int nets, vector<vector<int>>  xyval, int columns, int rows)
{
	int maxy = 0, miny = rows, maxx = 0, minx = columns, currhpwl = 0, oldhpwl = 0, sum = 0;
	for (int i = 0; i < nets; i++)
	{
		//cout << "\n \n" << i;
		for (int k = 1; k < cellList[i][0]+1; k++)
		{

			if (xyval[cellList[i][k]][1] > maxx) maxx = xyval[cellList[i][k]][1];
			if (xyval[cellList[i][k]][1] < minx) minx = xyval[cellList[i][k]][1];
			if (xyval[cellList[i][k]][2] > maxy) maxy = xyval[cellList[i][k]][2];
			if (xyval[cellList[i][k]][2] < miny) miny = xyval[cellList[i][k]][2];
			
			//cout << "\n" << "x: " << xyval[cellList[i][k]][1];
		}
		//cout << "\n " << minx << " " << maxx << " " << miny << " " << maxy;
		currhpwl = hpwl(minx, maxx, miny, maxy);
		if (oldhpwl < currhpwl) oldhpwl = currhpwl;
		sum = sum + currhpwl;
	}


	return sum;
}


//function that updates the 2d vector that stores the value of each cell and its x and y value on the grid after swapping
void updatexyval(vector<vector<int>>& valxy, vector<vector<int>>& sqgrid, int x1, int y1, int x2, int y2)
{


	if (sqgrid[x1][y1] < 0)
	{

		if (sqgrid[x2][y2] < 0)
		{

		}
		else {
			valxy[sqgrid[x2][y2]][0] = sqgrid[x2][y2];
			valxy[sqgrid[x2][y2]][1] = x2;
			valxy[sqgrid[x2][y2]][2] = y2;


		}
	}
	else {
		if (sqgrid[x2][y2] < 0)
		{
			valxy[sqgrid[x1][y1]][0] = sqgrid[x1][y1];
			valxy[sqgrid[x1][y1]][1] = x1;
			valxy[sqgrid[x1][y1]][2] = y1;


		}
		else {
			valxy[sqgrid[x2][y2]][0] = sqgrid[x2][y2];
			valxy[sqgrid[x2][y2]][1] = x2;
			valxy[sqgrid[x2][y2]][2] = y2;

			valxy[sqgrid[x1][y1]][0] = sqgrid[x1][y1];
			valxy[sqgrid[x1][y1]][1] = x1;
			valxy[sqgrid[x1][y1]][2] = y1;

		}


	}






}

// function moved to main for debugging purposes
 /*void anneal(){

	int initialcost;
	initialcost = maxhpwl(cellList, connections, valxy, columns, rows);
	print(sqgrid, initialcost, rows, columns);
	double cost, bestcost, oldcost, gain;
	double initialtemp, currtemp, ftemp, moveptemp;




	cost = maxhpwl(cellList, connections, valxy, columns, rows);
	//Initial Placement
	initialtemp = 500 * cost;
	currtemp = initialtemp;
	bestcost = cost;
	ftemp = 0.000005 * (cost / connections);
	while (currtemp > ftemp)
	{
		srand((unsigned)time(NULL));
		for (int i = 0; i < 10*cells; i++)
		{
			oldcost = cost;


			int rn1 = (rand() % rows);
			int rn2 = (rand() % columns);
			int rn3 = (rand() % rows);
			int rn4 = (rand() % columns);
			//cout << "\n" << rn1 << "\t" << rn2 << "\t" << rn3 << "\t" << rn4 << "\n";
			swap(rn1, rn2, sqgrid, rn3, rn4);

			updatexyval(valxy, sqgrid);

			cost = maxhpwl(cellList, connections, valxy, columns, rows);
			//cout << "\n" << cost;
			//cost = hpwl(xmin, xmax, ymin, ymax);
			gain = cost - oldcost;
			if (gain < 0)
			{
				srand((unsigned)time(0));

				float prob = (rand() % 1);
				if (prob >= exp(gain / currtemp)) swap(rn1, rn2, sqgrid, rn3, rn4);
				else if (cost < bestcost) bestcost = cost;
			}
		}
		currtemp = currtemp * 0.95;
		//cout << "Currtemp " << currtemp << "    ftemp" << ftemp << "\n \n \n";
	}
  }
 */



void outfile(vector<float> temps, vector<int> wirelength)
{
	ofstream graphs;
	graphs.open("SAgraph.csv");
	if (graphs.is_open() == false) cout << "could not open file";
	for (int i = 0; i < temps.size(); i++)
	{
		graphs << temps[i];
		graphs << ", ";
	}
	graphs << "\n";
	for (int i = 0; i < wirelength.size(); i++)
	{
		graphs << wirelength[i];
		graphs << ", ";
	}
	

}
int main()
{
	// parcing input file
	ifstream netlist;
	vector<vector<int>> cellList;
	vector<vector<int>> sqgrid;

	int cells, connections, rows, columns;
	netlist.open("test2.txt");

	netlist >> cells;
	netlist >> connections;
	netlist >> rows;
	netlist >> columns;
	cout << cells << "\t" << connections << "\t" << rows << "\t" << columns << "\n";
	int numberofcon;

	cellList.resize(connections);
	for (int i = 0; i < connections; i++)
		cellList[i].resize(cells + 1);

	//cout << "\n" << cellList.size();
	for (int i = 0; i < connections; i++)
	{

		//getline(netList,test);
		netlist >> numberofcon;


		//cout << "\n" << numberofcon;


		//cout << "\n" << cellList[i].size();
		for (int j = 1; j < numberofcon + 1; j++)
		{
			cellList[i][0] = numberofcon;
			netlist >> cellList[i][j];
		}

	}



	netlist.close();
	// parcing ends

	//printing iput file
	for (int i = 0; i < connections; i++)
	{
		for (int j = 0; j < cells; j++)
		{
			if (cellList[i][j] == 0)
			{
			}
			else {
				cout << cellList[i][j] << "\t";
			}


		}
		cout << "\n";
	}
	//cout << "\n"<<cellList[0][0] << cellList[1][0] << cellList[2][0];


	// initial placement of cells and instantiating the 2d vector xyval the stores each cell with its corresponding x and y value on the grid
	vector<float> temps;
	vector<int> wirelength;
	int xmin = rows, ymin = columns;
	int xmax = 0, ymax = 0;
	bool rejected = false;

	//Declaring a 2D-vector of size: x * y
	sqgrid.resize(rows);

	for (int i = 0; i < rows; i++)
		sqgrid[i].resize(columns);

	//Filling the 2D-vector with empty cells
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			sqgrid[i][j] = -1;
		}
	}
	vector<vector<int>> valxy;
	valxy.resize(cells);
	for (int i = 0; i < cells; i++)
		valxy[i].resize(3);
	//Initial Placement
	srand((unsigned)time(0));
	for (int i = 0; i < cells + 1; i++)
	{
		if (rejected == false && i == cells) break;
		if (rejected)
			i--;

		int rn1 = (rand() % rows);
		int rn2 = (rand() % columns);

		if (sqgrid[rn1][rn2] == -1)
		{
			sqgrid[rn1][rn2] = i;
			valxy[i][0] = i;
			valxy[i][1] = rn1;
			valxy[i][2] = rn2;


			rejected = false;
		}
		else
			rejected = true;
	}

	// Calculating the hpwl of all nets using simple annealing 

	int initialcost;
	initialcost = maxhpwl(cellList, connections, valxy, columns, rows);
	print(sqgrid, initialcost, rows, columns);
	double cost, bestcost, oldcost, gain;
	double initialtemp, currtemp, ftemp, moveptemp;




	cost = maxhpwl(cellList, connections, valxy, columns, rows);
	//Initial Placement
	initialtemp = 500 * cost;
	currtemp = initialtemp;

	bestcost = cost;
	ftemp = 0.000005 * (cost / connections);
	while (currtemp > ftemp)
	{
		wirelength.push_back(cost);
		temps.push_back(currtemp);
		srand((unsigned)time(NULL));
		for (int i = 0; i < 10 * cells; i++)
		{
			oldcost = cost;


			int rn1 = (rand() % rows);
			int rn2 = (rand() % columns);
			int rn3 = (rand() % rows);
			int rn4 = (rand() % columns);
			//cout << "\n" << rn1 << "\t" << rn2 << "\t" << rn3 << "\t" << rn4 << "\n";
			swap(rn1, rn2, sqgrid, rn3, rn4);

			updatexyval(valxy, sqgrid,rn1,rn2,rn3,rn4);
			
			
			
			cost = maxhpwl(cellList, connections, valxy, columns, rows);
		
			//cout << "\n net3: ";
		
			//cout << "\n" << cost;
			//cost = hpwl(xmin, xmax, ymin, ymax);
			gain = oldcost - cost;
			if (gain < 0)
			{
				//srand((unsigned)time(0));
				float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				//float prob = (rand() % 1);
				if (r >= exp(gain / currtemp)) {
					swap(rn1, rn2, sqgrid, rn3, rn4);
					updatexyval(valxy, sqgrid, rn1, rn2, rn3, rn4);
					cost = oldcost;
				}
				else  bestcost = cost;
			}
			else bestcost = cost;
			
		}
		currtemp = currtemp * 0.95;
		//cout << "Currtemp " << currtemp << "    ftemp" << ftemp << "\n \n \n";
	}
	// printing grid after finishing the algorithm
	print(sqgrid, bestcost, rows, columns);
	//outfile(temps, wirelength);

	return 0;
}