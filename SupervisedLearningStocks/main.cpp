//
//  main.cpp
//  SupervisedLearningStocks
//
//  Created by Ujjwal Singhania on 6/6/17.
//  Copyright © 2017 Ujjwal Singhania. All rights reserved.
//

#include "Hypothesis.hpp"
#include "CompanyForecast.hpp"
#include "PortfolioValues.h"
#include "DataMatrix.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

/*
 
 Function that assists Batch Gradient Descent.
 
 Allows the user to pass in a .csv filename - the function reads data from the .csv file
 and converts it into a vector<TrainingExample>, which can then be converted into a
 Hypothesis.
 
 */

vector<TrainingExample> readDataFromFile(const string& fileName) {
    ifstream fileInput (fileName);
    
    if (!fileInput) {
        cout << "Data from the file could not be read." << endl;
        exit(1);
    }
    
    vector<TrainingExample> hypothesisData;
    vector<double> dataValues;
    string value = "";
    
    // To check for Byte Order Mark (BOM).
    
    char bomCheck[4] = {0};
    fileInput.read(bomCheck, 3);
    if (strcmp(bomCheck, "\xEF\xBB\xBF") != 0) {
        fileInput.seekg(0);
    }
    
    while (fileInput >> value) {
        value = value + ",end,";
        string tableValue;
        stringstream ss = stringstream(value);
        while (getline(ss, tableValue, ',')) {
            if (tableValue == "end") {
                double target = dataValues.back();
                dataValues.pop_back();
                TrainingExample dataExample = TrainingExample(dataValues, target);
                hypothesisData.push_back(dataExample);
                dataValues = {};
                continue;
            }
            
            try {
                dataValues.push_back(stod(tableValue));
            }
            catch (invalid_argument) {
                cout << "Invalid";
                continue;
            }
        }
    }
    return hypothesisData;
}

vector<vector<double>> readPredictionDataFromFile() {
    ifstream fileInput ("PredictionData.csv");
    
    if (!fileInput) {
        cout << "Data from the file could not be read." << endl;
        exit(1);
    }
    
    vector<vector<double>> predictionData;
    vector<double> dataValues;
    string value = "";
    
    // To check for Byte Order Mark (BOM).
    
    char bomCheck[4] = {0};
    fileInput.read(bomCheck, 3);
    if (strcmp(bomCheck, "\xEF\xBB\xBF") != 0) {
        fileInput.seekg(0);
    }
    
    while (fileInput >> value) {
        value = value + ",end,";
        string tableValue;
        stringstream ss = stringstream(value);
        while (getline(ss, tableValue, ',')) {
            if (tableValue == "end") {
                predictionData.push_back(dataValues);
                dataValues = {};
                continue;
            }
            
            try {
                dataValues.push_back(stod(tableValue));
            }
            catch (invalid_argument) {
                cout << "Invalid";
                continue;
            }
        }
    }
    return predictionData;
}


int main() {
//    Data excelSheetNames;
//    vector<CompanyForecast> listOfCompanies;
//    for (size_t index = 0; index < excelSheetNames.CSVNames.size(); index++) {
//        vector<TrainingExample> trainingExamples = readDataFromFile(excelSheetNames.CSVNames[index]+".csv");
//        Hypothesis mockCompany = Hypothesis(trainingExamples);
//        cout << endl << endl << mockCompany << endl << endl;
//        vector<double> theta = mockCompany.performGradientDescent();
//        cout << endl << endl << endl;
//    
//        /*
//        for (size_t thetaIndex = 0; thetaIndex < theta.size(); thetaIndex++) {
//            cout << showpos << theta[thetaIndex] << noshowpos << " * ";
//        }
//        */
//        
//        listOfCompanies.push_back(CompanyForecast(theta, excelSheetNames.CSVNames[index]));
//    }
//    
//    vector<vector<double>> predictionData = readPredictionDataFromFile();
//    
//    for (size_t printIndex = 0; printIndex < listOfCompanies.size(); printIndex++) {
//        cout << listOfCompanies[printIndex] << endl << endl;
//        cout << "Predicted Value: " << listOfCompanies[printIndex].returnCompanyForecast(predictionData[printIndex]);
//        cout << "----------------------------------------" << endl << endl;
//    }
    
    DataMatrix test = DataMatrix({{2,2}});
    DataMatrix test2 = DataMatrix({{3}, {3}});
    
    cout << test << endl << endl << test2 << endl << endl << test * test2 << endl;
}
