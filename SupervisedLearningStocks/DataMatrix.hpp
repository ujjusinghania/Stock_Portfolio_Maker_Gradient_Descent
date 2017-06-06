//
//  DataMatrix.hpp
//  SupervisedLearningStocks
//
//  Created by Ujjwal Singhania on 6/6/17.
//  Copyright © 2017 Ujjwal Singhania. All rights reserved.
//

#ifndef DataMatrix_h
#define DataMatrix_h

#include <stdio.h>
#include <iostream>
#include <vector>

class DataMatrix {
    
public:
    DataMatrix(const int row, const int column);
    DataMatrix(const std::string& fileName);
    friend std::ostream& operator<<(std::ostream& outputStream, const DataMatrix& dataMatrix);
    double operator()(const int& row, const int& column);
    
private:
    std::vector<std::vector<double>> valueMatrix;
    int row;
    int column; 
    
};

#endif /* DataMatrix_h */
