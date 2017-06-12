//
//  CompanyForecast.cpp
//  SupervisedLearningStocks
//
//  Created by Ujjwal Singhania on 6/12/17.
//  Copyright © 2017 Ujjwal Singhania. All rights reserved.
//

#include "CompanyForecast.hpp"
#include <vector> 
#include <iostream>
using namespace std;

CompanyForecast::CompanyForecast(const vector<double>& thetaVal, const string& company) : thetaValues(thetaVal), companyName(company) {}

double CompanyForecast::returnCompanyForecast(const vector<double>& predictionValues) {
    double predictionPercentage = -100.0;
    if (predictionValues.size() == thetaValues.size()) {
        predictionPercentage = 0.0;
        for (size_t n = 0; n < thetaValues.size(); n++) {
            predictionPercentage += predictionValues[n] * thetaValues[n];
        }
    }
    return predictionPercentage;
}

string CompanyForecast::getCompanyName() const {
    return companyName; 
}
