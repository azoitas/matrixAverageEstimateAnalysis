#pragma once
#include <tuple>
#include <algorithm>
#include <math.h>
#include <vector>
#include <iostream>
#include <windows.h> 
#include "squareMatrix.h"
#include "Tests.cpp"


int main()
{	
	int start_range = 1706;
	int end_range = 1730; 
	int midpoint = (start_range + end_range) / 2;
	int dimension = 5;

	Tests matrixObj(start_range, end_range, dimension);

	/*With each iteration the start and end points converge towards the midpoint. This is done to produce different Values by the random number generator.*/
	for (int i = start_range; i < midpoint; i++) {
		matrixObj.sortRows();
		matrixObj.print2();
		//matrixObj.printOnlyResults(); 
		start_range++;
		end_range--;
		matrixObj.setNewMatrix((start_range),(end_range),5);
	}
	start_range++;
	end_range++;
	matrixObj.setNewMatrix((start_range), (end_range), 5); //special case to handle a spread of 1
	matrixObj.printOnlyResults();					 			

	std::cout << "\nStandard Deviation: " << matrixObj.getStandardDeviation() << "\n";
	matrixObj.percentCorrect();
}



