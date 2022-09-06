#pragma once
#include "squareMatrix.h"
#include <vector>
#include <iostream>
#include <cmath>

class Tests {
private:
	double rangeStart = 0.0, rangeEnd = 0.0, spread = 0.0, sizeOfMatrix = 0.0, mid = 0.0;
	double rawExactAvg = 0.0, rawEstimateAvg = 0.0;
	double rawDifference = 0.0;
	double sortedExactAvg = 0.0, sortedEstimateAvg = 0.0;
	double sortedDifference = 0.0;
	bool currentCorrect = false;
	std::vector<double> rawEstimatesVec;
	std::vector<double> rawExactVec;
	std::vector<double> sortedEstimatesVec;
	std::vector<double> sortedExactVec;
	std::vector<double> differencesVec;
	double correct = 0.0;
	double wrong = 0.0;
	squareMatrix* sqm;

public:

	Tests(double rangestart, double rangeend, double matrixdimension) :rangeStart(rangestart), rangeEnd(rangeend), spread(rangeend - rangestart), sizeOfMatrix(matrixdimension), mid((rangeStart + rangeend) / 2) {
		sqm = new squareMatrix(sizeOfMatrix, { rangeStart,rangeEnd });
		rawExactAvg = sqm->averagePrice_Exact();
		rawEstimateAvg = sqm->averagePrice_Estimate();
		rawDifference = rawEstimateAvg - rawExactAvg;
	}

	~Tests() {
		std::cout << "~Tests\n";
		delete sqm;
	}

	void setNewMatrix(int rangestart, int rangeend, int matrixdimension) {
		std::cout << "\n";
		if (sqm != nullptr) {
			delete sqm;
		}
		sqm = new squareMatrix(matrixdimension, { rangestart,rangeend });
		rangeStart = rangestart;
		rangeEnd = rangeend;
		spread = rangeEnd - rangeStart;
		sizeOfMatrix = matrixdimension;
	}

	void sortRows() {
		sqm->sortRows();
	}

	void print2() {
		std::cout << "**********************************\n\n";
		sqm->print();
		printCurrentAverages();
		//double firstRowAvg = sqm->row1Avg();
		//std::cout << "\nRow 1 Avg: " << firstRowAvg << "\n"; 
	}

	void printOnlyResults() {
		std::string results = std::to_string(mid)+",";//Midpoint of range
		results+= stringAveragesResultsOnly(); //Appends estimated average followed by actual average
		results+= stringCorrectAndIncorrectStats();//Appends the count of correct, wrong, and percent correct in that order.
		results+= std::to_string(spread)+",";//Apends spread
		results += std::to_string(getStandardDeviation());//Appends standard deviation
		std::cout << results<<'\n';
	}

	void printSortRowsprint() {
		std::cout << "Raw Data:\n";
		sqm->print();
		printRawAverages();
		std::cout << "\nSorted Data:\n";
		sqm->sortRows();
		sqm->print();
		printCurrentAverages();
		std::cout << "\n";
	}

	void printRawAverages() {
		std::cout << "Estimated Average (raw): " << rawEstimateAvg << "\n";
		std::cout << "Exact Average     (raw): " << rawExactAvg << "\n";
		std::cout << "Difference        (raw): " << rawDifference << "\n";
	}

	void printCurrentAverages() {
		double estimate = sqm->averagePrice_Estimate();
		double exact = sqm->averagePrice_Exact();
		differencesVec.push_back(estimate - exact);
		if ((estimate >= mid && exact >= mid) || (estimate < mid && exact < mid)) {
			correct++;
		}
		else {
			wrong++;
		}
		std::cout << "Estimated Average O(n)   (current): " << estimate << "\n";
		std::cout << "Exact Average     O(n^2) (current): " << exact << "\n";
		std::cout << "Difference               (current): " << estimate-exact << "\n";
	}

	std::string stringAveragesResultsOnly() {
		double estimate = sqm->averagePrice_Estimate();
		double exact = sqm->averagePrice_Exact();
		differencesVec.push_back(estimate - exact);
		if ((estimate >= mid && exact >= mid) || (estimate < mid && exact < mid)) {
			correct++;
			currentCorrect = true;
		}
		else {
			wrong++;
		}
		return (std::to_string(estimate)+","+ std::to_string(exact)+",");
	}


	/*
	Uses the vector of the differnces between the Actual Average value - Estmiated Value on 
	*/
	double getStandardDeviation() {
		if (differencesVec.size() <= 1) { return -1; }
		double X = 0.0;
		double mean = 0.0;
		for (double value : differencesVec) {
			X += value;
		}
		mean = (X / differencesVec.size());
		double sum=0.0;
		double temp = 0.0;
		for (double value : differencesVec) {
			temp = (value - mean);
			sum += (temp * temp);
		}
		temp = (sum / (differencesVec.size() - 1));
		return std::sqrt(temp);
	}

	std::vector<double> getDiffVec() {
		return differencesVec;
	}

	void percentCorrect() {
		if (differencesVec.size() <= 0) {
			std::cout << "N/A\n";
			return;
		}
		
		std::cout << "mid =" << mid<<"\n";
		std::cout << "Total Correct: " << correct << "\nTotal Wrong: " << wrong << "\n";
		std::cout << "Total Attempts: " << differencesVec.size() << "\n";
		std::cout << "Precent Correct " << (correct / (correct + wrong)) * 100 << "%\n";
	}
	std::string stringCorrectAndIncorrectStats() {
		if (differencesVec.size() <= 0) {
			return "N/A";
		}
		
		return std::to_string(correct) + "," + std::to_string(wrong) +"," + std::to_string((correct / (correct + wrong)) * 100) + ",";
	}



};