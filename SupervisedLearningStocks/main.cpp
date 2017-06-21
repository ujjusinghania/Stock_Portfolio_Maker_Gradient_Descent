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


vector<vector<double>> readDataFromFile(const string& fileName) {
    ifstream fileInput (fileName);
    
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

void showStockPortofolioPicks(vector<string>& companyNames, vector<double>& values) {
    if (companyNames.size() != values.size()) {
        cout << "Size of 'Company Names' Vector and 'Predicted Values' Vector is not the same - Size Mismatch." << endl << "Cannot perform portfolio operations on provided dataset vectors.";
        return;
    }
    for (int i = 0; i < values.size()-1; i++) {
        for (int j = 0; j < values.size()-1; j++) {
            if (values[j] < values[j+1]) {
                swap(values[j], values[j+1]);
                swap(companyNames[j], companyNames[j+1]);
            }
        }
    }
    
    for (int i = 0; i < values.size(); i++) {
        cout << companyNames[i] << ":   " << values[i] << endl;
    }
}

int main() {
    
    Data values;
    vector<string> fileNames = values.CSVNames;
    vector<CompanyForecast> listOfCompanies;
    
    for (int loopCounter = 0; loopCounter < fileNames.size(); loopCounter++) {
        vector<vector<double>> dataForPredictionModel = readDataFromFile(fileNames[loopCounter]+".csv");
        vector<vector<double>> yValues;
        for (int i = 0; i < dataForPredictionModel.size(); i++) {
            vector<double> test;
            test.push_back(dataForPredictionModel[i].back());
            dataForPredictionModel[i].pop_back();
            yValues.push_back(test);
        }
        
        DataMatrix y = DataMatrix(yValues);
        DataMatrix x = DataMatrix(dataForPredictionModel);
        
        listOfCompanies.push_back(CompanyForecast((((x.transpose() * x).inverse() * x.transpose()) * y).getThetaValues(), fileNames[loopCounter]));
    }
    
    vector<vector<double>> predictionData = readDataFromFile(values.predictionDataCSV);
    vector<double> predictedValues;
    
    for (int forecastIndex = 0; forecastIndex < fileNames.size(); forecastIndex++) {
        predictedValues.push_back(listOfCompanies[forecastIndex].returnCompanyForecast(predictionData[forecastIndex]));
    }
    
    showStockPortofolioPicks(fileNames, predictedValues);
    
}
