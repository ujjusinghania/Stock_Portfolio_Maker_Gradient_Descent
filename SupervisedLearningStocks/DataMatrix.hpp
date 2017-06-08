//
//  DataMatrix.hpp
//  SupervisedLearningStocks
//
//  Created by Ujjwal Singhania on 6/6/17.
//  Copyright © 2017 Ujjwal Singhania. All rights reserved.
//

#ifndef DataMatrix_hpp
#define DataMatrix_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

class DataMatrix {
    
public:
    DataMatrix(bool valid);
    DataMatrix(const int row, const int column);
    // Add a constructor that initialises the value of each element to be equal to x
    DataMatrix(const int row, const int column, const int value);
    DataMatrix(const std::string& fileName);
    friend std::ostream& operator<<(std::ostream& outputStream, const DataMatrix& dataMatrix);
    double operator()(const int& row, const int& column);
    
    // Add + operator, += operator, - operator, -= operator
    // Check if rows and colums are equal before performing any calculation.
    
     DataMatrix& operator+=(const DataMatrix& right);
     friend DataMatrix operator+(const DataMatrix& left, const DataMatrix& right);
     DataMatrix& operator-=(const DataMatrix& right);
     friend DataMatrix operator-(const DataMatrix& left, const DataMatrix& right);
     
    
private:
    std::vector<std::vector<double>> valueMatrix;
    int row;
    int column;
    bool isValid;
    
};

#endif /* DataMatrix_hpp */
