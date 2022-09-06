#include "squareMatrix.h"
#include <random>
#include <algorithm>
#include <functional>
#include <iostream>
#include <tuple>
#include <iomanip>
#include <functional>

squareMatrix::squareMatrix(int size):dimension(size),matrix(size) {
	fillMatrix(90, 105);
}//Constructor for a given n size. No range was given defualt set from 90 - 105.

squareMatrix::squareMatrix(int size, std::tuple<int, int> inputRangeInc) :dimension(size), matrix(size), rangeInclusive({std::get<0>(inputRangeInc),std::get<1>(inputRangeInc)}) {
	fillMatrix(std::get<0>(rangeInclusive), std::get<1>(rangeInclusive));
}

void squareMatrix::fillMatrix(int start, int end){
	std::uniform_int_distribution<unsigned> u(start, end);
	std::uniform_int_distribution<unsigned> decimal(0, 99);
	std::default_random_engine engine;
	std::default_random_engine decEngine;
	for (int row = 0; row < dimension; row++) {
		for (int col = 0; col < dimension; col++) {
			matrix.at(row).push_back(u(engine) + ((decimal(decEngine) / 100.00)));
		}
	}
}


double squareMatrix::averagePrice_Estimate() {
	double average = 0.00;
	for (int i = 0; i < matrix.size();i++) {
		average+=matrix.at(i).at(i);
	}
	average /= dimension;
	return average;
}

double squareMatrix::averagePrice_Exact(){
	double average = 0.00;
	for (auto row : matrix) {
		for (auto colVal : row) {
			average += colVal;
		}
	}
	average /= (dimension * dimension);
	return average;
}

void squareMatrix::sortRows() {
	for (int row = 0; row < matrix.size();row++) {
		std::sort(matrix.at(row).begin(), matrix.at(row).end(),std::less<double>());
	}
}


void squareMatrix::print() {
	for (int row = 0; row < dimension;row++) {
		for (int col = 0; col < dimension;col++) {
			std::cout << matrix.at(row).at(col) <<" ";
		}
		std::cout << "\n";
	}
}

double squareMatrix::row1Avg() {
	double row1Avg=0;
	for (int col = 0; col < dimension; col++) {
		row1Avg += matrix.at(0).at(col);
	}
	row1Avg /= dimension;
	return row1Avg;
}; 