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
#include "BetaCell.h"

int main( int argc , char **argv )
{
	
	/* Delete old output files. Shoddy error implementation, but this is
		temporary. Long term, outputs will be automatically distributed
		into unique folders. - WLF
	*/
	if (remove(O1Output)) perror("Error 1");
	if (remove(O2Output)) perror("Error 2"); 
	if (remove(C1Output)) perror("Error 3");
	if (remove(C2Output)) perror("Error 4");
	if (remove(potentialOutput)) perror("Error 5");
	if (remove(timeOutput)) perror("Error 6");
	if (remove(calciumOutput)) perror("Error 7");
	if (remove(sodiumOutput)) perror("Error 8");
	if (remove(potassiumOutput)) perror("Error 9");
	if (remove(caerOutput)) perror("Error 10");
	if (remove(atpOutput)) perror("Error 11");
	if (remove(adpOutput)) perror("Error 12");
	if (remove(PPOutput)) perror("Error 13");
	if (remove(IRPOutput)) perror("Error 14");
	if (remove(DPOutput)) perror("Error 15");
	if (remove(FIPOutput)) perror("Error 16");
	if (remove(RIPOutput)) perror("Error 17");
	if (remove(capOutput)) perror("Error 18");
	if (remove(noiseOutput)) perror("Error 19");

	vector_type x1(cellNumber*30);
	vector_type dxdt(cellNumber*30);
		
	/*	The following populate variables from data files for use in 
	    future calculations. The varsFile contains initial values
		for each cells properties; NNFile lists adjacent cells for each
		cell in the islet; cellFile lists coordinates for each cell (which 
		don't seem to be used at all in this or BetaCell.h); RVFile
		pulls the output from the RandomVariables program, which
		includes randomly generated cellular attributes. - WLF
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

	double tMax=2000.00;
	double tStep = 0.18;
	BetaSolver(x1,dxdt,tStep, tMax);

	return 0;
}

