#include <stdio.h>
#include <iostream>
#include <boost/numeric/odeint.hpp>
#include <boost/multi_array.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <cassert>
#include <cmath>
#include <ostream>
#include <fstream>
#include <vector>
#include <boost/random/detail/config.hpp>
#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/include/vector_fwd.hpp>
#include <omp.h>
#include <string>
#include <algorithm>
#include <boost/math/distributions/skew_normal.hpp>
#include "BetaCell.h"

int main( int argc , char **argv )
{

	if (!remove(O1info)) perror("Error");
	if (!remove(O2info)) perror("Error"); 
	if (!remove(C1info)) perror("Error");
	if (!remove(C2info)) perror("Error");
	if (!remove(potentialname)) perror("Error");
	if (!remove(timename)) perror("Error");
	if (!remove(calciuminfo)) perror("Error");
	if (!remove(sodiuminfo)) perror("Error");
	if (!remove(potassiuminfo)) perror("Error");
	if (!remove(caerinfo)) perror("Error");
	if (!remove(atpinfo)) perror("Error");
	if (!remove(adpinfo)) perror("Error");
	if (!remove(PPinfo)) perror("Error");
	if (!remove(IRPinfo)) perror("Error");
	if (!remove(DPinfo)) perror("Error");
	if (!remove(FIPinfo)) perror("Error");
	if (!remove(RIPinfo)) perror("Error");
	if (!remove(Capinfo)) perror("Error");
	if (!remove(Noiseinfo)) perror("Error");

	vector_type x1(cellNumber*30);
	vector_type dxdt(cellNumber*30);
	
	ifstream myFile ("vars5exo.txt");
	if (myFile.is_open())
	{
		for (int i=0;i<30*cellNumber;i++)
		{
			myFile>>x1[i];
		}

		myFile.close();
	}

	ifstream NNfile("NN10A.txt");
	for (int i=0;i<cellNumber;i++)
	{
		for (int j=0;j<15;j++)
		{
			NNfile>>NN[i][j];
		}
	}

	ifstream cFile("XYZpos.txt");
	if(cFile.is_open())
	{
		for (int i=0; i<cellNumber;i++)
		{
			for (int j=0;j<3;j++)
			{
				cFile>>cellPos[i][j];
				cout<<cellPos[i][j];
			}
			cout<<endl;
		}
	}
	
	ifstream randomVar("RandomVars.txt");
	double RandomVarMat[cellNumber][12];
	for(int i=0;i<cellNumber;i++)
	{
		randomVar >> gKATPar[i];
		randomVar >> gCoup[i];
		randomVar >> gKtoar[i];
		randomVar >> PCaERar[i];
		randomVar >> gKCaBKar[i];
		randomVar >> PNACAar[i];
		randomVar >> Prelar[i];
		randomVar >> Popar[i];
		randomVar >> ATPar[i];
		randomVar >> KRev[i];
		randomVar >> RandomSeed[i];
		randomVar >> gChR2[i];
	}

	tMax=2000.00;
	totalnodes=1;
	BetaSolver(x1,dxdt,0.18);

	return 0;
}

