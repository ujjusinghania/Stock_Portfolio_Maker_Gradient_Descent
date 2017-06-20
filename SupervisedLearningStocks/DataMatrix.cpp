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

DataMatrix::DataMatrix(const int row, const int column, const int value) : row(row), column(column), valueMatrix(row, vector<double>(column, value)) {}

// Complete this constructor.
//DataMatrix::DataMatrix(const std::string& fileName) {
//    ifstream dataFile = ifstream(fileName);
//    
//    if (!dataFile) {
//        cout << "Couldn't access the data file" << endl;
//        return;
//    }
//    
//    string value = "";
//    int matrixIndex = 0;
//    vector<double> dataVector = {};
//    while(dataFile >> value) {
//        dataVector.push_back(stod(value));
//        cout << value << "|";
//        if (value == "\n") {
//            matrixIndex++;
//            valueMatrix.push_back(dataVector);
//            dataVector = {};
//            cout << endl;
//        }
//    }
//    
//    row = valueMatrix.size();
// //   column = valueMatrix[0].size();
//    isValid = true; 
//}
//
//

DataMatrix::DataMatrix(const std::vector<std::vector<double>>& values): valueMatrix(values), row(values.size()), column(values[0].size()) {}

DataMatrix::DataMatrix(const int row, const int column, const std::vector<std::vector<double>>& values): row(row), column(column) {
    vector<vector<double>> returnValue;
    for (int i = 0; i < row; i++) {
        vector<double> addVector;
        for (int j = 0; j < column; j++) {
            addVector.push_back(values[i][j]);
        }
        returnValue.push_back(addVector);
    }
    valueMatrix = returnValue;
}

double DataMatrix::operator()(const int& row, const int& column) const {
    return valueMatrix[row][column];
}

DataMatrix DataMatrix::transpose() {
    vector<vector<double>> returnValue;
    for (int i = 0; i < column; i++) {
        vector<double> addVector;
        for (int j = 0; j < row; j++) {
            addVector.push_back((*this)(j,i));
        }
        returnValue.push_back(addVector);
    }
    return returnValue;
}

DataMatrix DataMatrix::inverse() {
    if (row != column) {
        cout << "Inverse operation could not be completed - Dimension Mismatch (Row and Column are not equal)." << endl;
        exit(92);
    }
    
    vector<vector<double>> inverseMatrix = getUnitMatrix(row).valueMatrix;
    vector<vector<double>> copyValueMatrix = valueMatrix;
    
    for (int RREFCounter = 0; RREFCounter < row; RREFCounter++) {
        double divisionNumber = copyValueMatrix[RREFCounter][RREFCounter];
        for (int divisionCounter = 0; divisionCounter < row; divisionCounter++) {
            inverseMatrix[RREFCounter][divisionCounter] = inverseMatrix[RREFCounter][divisionCounter]/divisionNumber;
            copyValueMatrix[RREFCounter][divisionCounter] = copyValueMatrix[RREFCounter][divisionCounter]/divisionNumber;
        }
        for (int inverseRowCounter = 0; inverseRowCounter < row; inverseRowCounter++) {
            if (inverseRowCounter == RREFCounter) {
                continue;
            }
            double multiplicationValue = copyValueMatrix[inverseRowCounter][RREFCounter];
            for (int inverseColumnCounter = 0; inverseColumnCounter < row; inverseColumnCounter++) {
                inverseMatrix[inverseRowCounter][inverseColumnCounter] -= inverseMatrix[RREFCounter][inverseColumnCounter] * multiplicationValue;
                copyValueMatrix[inverseRowCounter][inverseColumnCounter] -= (copyValueMatrix[RREFCounter][inverseColumnCounter] * multiplicationValue);
            }
        }
    }
    cout << DataMatrix(copyValueMatrix) << endl << endl;
    return DataMatrix(inverseMatrix);
}

DataMatrix getUnitMatrix(int size) {
    vector<vector<double>> returnValue = vector<vector<double>>(size, vector<double>(size, 0));
    for (int i = 0; i < size; ++i) {
        returnValue[i][i] = 1;
    }
    return DataMatrix(returnValue);
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

DataMatrix operator*(const DataMatrix& left, const DataMatrix& right) {
    vector<vector<double>> returnValueMatrix;
    if (left.column != right.row) {
        cout << "Multiplication operation could not be completed - Dimension Mismatch." << endl;
        exit(32);
    }

    for (int i = 0; i < left.row; i++) {
        vector<double> returnVector;
        for (int j = 0; j < right.column; j++) {
            double cellValue = 0.0;
            for (int k = 0; k < left.column; k++) {
                cellValue += left(i,k)*right(k,j);
            }
            returnVector.push_back(cellValue);
        }
        returnValueMatrix.push_back(returnVector);
    }
    
    return DataMatrix(left.row, right.column, returnValueMatrix);
}

vector<double> DataMatrix::getThetaValues() {
    vector<double> returnValue;
    for (int i = 0; i < row; i++) {
        returnValue.push_back((*this)(i,0));
    }
    return returnValue; 
}
