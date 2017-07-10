//
//  HelperFunctions.h
//  SupervisedLearningStocks
//
//  Created by Ujjwal Singhania on 7/7/17.
//  Copyright © 2017 Ujjwal Singhania. All rights reserved.
//

#ifndef HelperFunctions_h
#define HelperFunctions_h

#include "CompanyForecast.hpp"
#include "DataMatrix.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::vector<double>> readDataFromFile(const std::string& fileName);
void showStockPortofolioPicks(std::vector<std::string>& companyNames, std::vector<double>& values);
std::vector<std::vector<double>> predictFutureValues(const std::string& fileName);

#endif /* HelperFunctions_h */
