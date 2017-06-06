//
//  DataMatrix.cpp
//  SupervisedLearningStocks
//
//  Created by Ujjwal Singhania on 6/6/17.
//  Copyright © 2017 Ujjwal Singhania. All rights reserved.
//

#include "DataMatrix.hpp"
#include <iostream>
#include <vector>
using namespace std;

DataMatrix::DataMatrix(const int row, const int column) : row(row), column(column), valueMatrix(row, vector<double>(column)) {}

// Complete this constructor.
DataMatrix::DataMatrix(const std::string& fileName) {}

ostream& operator<<(ostream& outputStream, const DataMatrix& dataMatrix) {
    for (int row = 0; row < dataMatrix.valueMatrix.size(); ++row) {
        for(int column = 0; column < dataMatrix.valueMatrix[0].size(); ++column) {
            outputStream << dataMatrix.valueMatrix[row][column] << " ";
        }
        outputStream << endl;
    }
    return outputStream;
}

double DataMatrix::operator()(const int& row, const int& column) {
    return valueMatrix[row][column];
}
