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
#include <fstream>
using namespace std;

DataMatrix::DataMatrix(bool valid) : row(0), column(0), isValid(valid) {}

DataMatrix::DataMatrix(const int row, const int column) : row(row), column(column), valueMatrix(row, vector<double>(column)) {
    if (row > 0 && column >0) {
        isValid = true;
    }
    else {
        isValid = false;
    }
}

DataMatrix::DataMatrix(const int row, const int column, const int value) : row(row), column(column), valueMatrix(row, vector<double>(column, value)) {
    if (row > 0 && column >0) {
        isValid = true;
    }
    else {
        isValid = false;
    }
}

// Complete this constructor.
DataMatrix::DataMatrix(const std::string& fileName) {
    ifstream dataFile = ifstream(fileName);
    
    if (!dataFile) {
        cout << "Couldn't access the data file" << endl;
        return;
    }
    
    string value = "";
    int matrixIndex = 0;
    vector<double> dataVector = {};
    while(dataFile >> value) {
        dataVector.push_back(stod(value));
        cout << value << "|";
        if (value == "\n") {
            matrixIndex++;
            valueMatrix.push_back(dataVector);
            dataVector = {};
            cout << endl;
        }
    }
    
    row = valueMatrix.size();
 //   column = valueMatrix[0].size();
    isValid = true; 
}

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

/*
DataMatrix& DataMatrix::operator+=(const DataMatrix& right) {
    if (row == right.row && column = right.column) {
        return *this;
    }
    else {
        cout << "Operation cannot be completed - dimension mismatch." << endl;
        return nullptr;
    }
}

DataMatrix operator+(const DataMatrix& left, const DataMatrix& right) {
    
}

DataMatrix& DataMatrix::operator-=(const DataMatrix& right) {
    
}

DataMatrix operator-(const DataMatrix& left, const DataMatrix& right) {
    
}
*/
