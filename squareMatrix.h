#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<tuple>
#include <functional>
#include <algorithm>

class squareMatrix
{
private:
	int dimension;
	std::vector<std::vector<double>> matrix;
	std::tuple<int, int> rangeInclusive;

	void fillMatrix(int start, int end);
	

public:
	squareMatrix(int size);
	squareMatrix(int size, std::tuple<int,int> rangeInc);
	
	double averagePrice_Estimate();

	double averagePrice_Exact();
	
	void print();

	double row1Avg();

	void sortRows();
};

