#include <stdio.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include <ostream>
#include <fstream>
#include <vector>
#include <omp.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <boost/random/detail/config.hpp>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/include/vector_fwd.hpp>
#include <boost/math/distributions/skew_normal.hpp>
#include <boost/numeric/odeint.hpp>
#include <boost/multi_array.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
//#include <boost/filesystem/operations.hpp>
//#include <boost/filesystem/path.hpp>
//#include <boost/progress.hpp>
#include "BetaCell.h"

int main( int argc , char **argv )
{
	if (remove(O1Output)) perror("Error 1");
	if (remove(O2Output)) perror("Error 2"); 
	if (remove(C1Output)) perror("Error 3");
	if (remove(C2Output)) perror("Error4");
	if (remove(potentialOutput)) perror("Error5");
	if (remove(timeOutput)) perror("Error6");
	if (remove(calciumOutput)) perror("Error7");
	if (remove(sodiumOutput)) perror("Error8");
	if (remove(potassiumOutput)) perror("Error9");
	if (remove(caerOutput)) perror("Error10");
	if (remove(atpOutput)) perror("Error11");
	if (remove(adpOutput)) perror("Error12");
	if (remove(PPOutput)) perror("Error13");
	if (remove(IRPOutput)) perror("Error14");
	if (remove(DPOutput)) perror("Error15");
	if (remove(FIPOutput)) perror("Error16");
	if (remove(RIPOutput)) perror("Error17");
	if (remove(capOutput)) perror("Error18");
	if (remove(noiseOutput)) perror("Error19");

	vector_type x1(cellNumber*30);
	vector_type dxdt(cellNumber*30);
	
	/* The following is a general implementation for pulling in a series 
		of user defined variable values from an imput file. Not yet 
		implemented for variable assignment. So it doesn't do anything
		useful yet.
 	*/
	string userVarMatrix[2][5];
	ifstream userVarFile;
	userVarFile.open("UserDefinedVars.txt");
	int i=0;
	
	while(!userVarFile.eof())
	{	
		char buffer[20];
		userVarFile.getline(buffer, 20);
		stringstream varStream;
		varStream << buffer;
		varStream.getline(buffer, 10, '=');
		string strBuffer(buffer);
		userVarMatrix[0][i] = strBuffer;
		cout << userVarMatrix[0][i] << " = ";
		i++;
		varStream.getline(buffer, 10, ';');
		strBuffer.assign(buffer);
		userVarMatrix[1][i] = strBuffer;
		cout << userVarMatrix[1][i] << ";" << endl;
	}
	
	/*	The following populate variables from data files for use in 
	    future calculations. The varsFile contains initial values
		for each cells properties; NNFile lists adjacent cells for each
		cell in the islet; cellFile lists coordinates for each cell (which 
		don't seem to be used at all in this or BetaCell.h); RVFile
		pulls the output from the RandomVariables program, which
		includes randomly generated cellular attributes.
	*/
	
	ifstream varsFile ("vars5exo.txt");
	if (varsFile.is_open())
	{
		for (int i=0;i<30*cellNumber;i++)
		{
			varsFile>>x1[i];
		}
		varsFile.close();
	}

	ifstream NNFile("NN10A.txt");
	if(NNFile.is_open())
	{
		for (int i=0;i<cellNumber;i++)
		{		
			for (int j=0;j<15;j++)
			{
				NNFile>>NN[i][j];
			}
		}
		NNFile.close();
	}
		
	ifstream cellFile("XYZpos.txt");
	if(cellFile.is_open())
	{
		for (int i=0; i<cellNumber;i++)
		{
			for (int j=0;j<3;j++)
			{
				cellFile>>cellPos[i][j];
			}
		}
		cellFile.close();
	}
	
	ifstream RVFile("RandomVars.txt");
	if(RVFile.is_open())
	{
		for(int i=0;i<cellNumber;i++)
		{
			RVFile >> gKATPar[i];
			RVFile >> gCoup[i];
			RVFile >> gKtoar[i];
			RVFile >> PCaERar[i];
			RVFile >> gKCaBKar[i];
			RVFile >> PNACAar[i];
			RVFile >> Prelar[i];
			RVFile >> Popar[i];
			RVFile >> ATPar[i];
			RVFile >> KRev[i];
			RVFile >> RandomSeed[i];
			RVFile >> gChR2[i];
		}
		RVFile.close();
	}

	/* Set the time in milliseconds and run the BetaSolver.
	
	*/
	double tMax=2000.00;
	double tStep = 0.18;
	BetaSolver(x1,dxdt,tStep, tMax);

	return 0;
}

