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
#include "HelperFunctions.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

double getCostFunction(const vector<double>& temporaryThetaValues, const vector<vector<double>>& testExamples) {
    
    if (temporaryThetaValues.size() - testExamples[0].size() != -1) {
        cout << "Dimension Mismatch - Function getCostFunction(): Size of Theta Values: " << temporaryThetaValues.size() << " Size of testExamples: " << testExamples[0].size() << endl;
        exit(12);
    }
    
    double sum = 0.0;
    
    for (int index = 0; index < testExamples.size(); index++) {
        double multiplySum = 0.0;
        for (int multiplyIndex = 0; multiplyIndex < testExamples[0].size()-1; multiplyIndex++) {
            multiplySum += temporaryThetaValues[multiplyIndex] * testExamples[index][multiplyIndex];
        }
        sum += (testExamples[index][testExamples[0].size()-1] - multiplySum) * (testExamples[index][testExamples[0].size()-1] - multiplySum);
    }
    
    return sum;
}

vector<double> returnBestThetaValues(const DataMatrix& X, const DataMatrix& Y, const vector<vector<double>>& testExamples) {
    Data constantValues;
    double costFunctionValue = -1;
    vector<double> thetaValues = vector<double>(X.getColumns()); // Insert number of factors.
    for (int index = 0; index < constantValues.PermutationsValues.size(); index++) {
        
        vector<vector<double>> permutedX = {};
        
        for (int rows = 0; rows < X.getRows(); rows++) {
            vector<double> rowValues;
            for (int permutationIndex = 0; permutationIndex < constantValues.PermutationsValues[index].size(); permutationIndex++) {
                rowValues.push_back(X(rows, constantValues.PermutationsValues[index][permutationIndex]));
            }
            permutedX.push_back(rowValues);
        }
        
        DataMatrix newX = DataMatrix(permutedX);
        vector<double> temporaryValue = (((newX.transpose() * newX).inverse() * newX.transpose()) * Y).getThetaValues();
        
        vector<double> temporaryThetaValues = vector<double>(X.getColumns());
        for (int permutationIndex = 0; permutationIndex < constantValues.PermutationsValues[index].size(); permutationIndex++) {
            temporaryThetaValues[constantValues.PermutationsValues[index][permutationIndex]] = temporaryValue[permutationIndex];
        }
        
        double newCostFunction = getCostFunction(temporaryThetaValues, testExamples);
        
        if (costFunctionValue == -1) {
            cout << "Cost Function reduced from " << costFunctionValue << " to " << newCostFunction << endl;
            costFunctionValue = newCostFunction;
            thetaValues = temporaryThetaValues;
        }
        else if (costFunctionValue > newCostFunction) {
            cout << "Cost Function reduced from " << costFunctionValue << " to " << newCostFunction << endl;
            costFunctionValue = newCostFunction;
            thetaValues = temporaryThetaValues;
        }
    }
    
    vector<vector<double>> printCheck;
    printCheck.push_back(thetaValues);
    cout << DataMatrix(printCheck) << "Cost: " << costFunctionValue << endl << endl;
    return thetaValues;
}


int main() {
    
    Data values;
    vector<string> fileNames = values.CSVNames;
    vector<CompanyForecast> listOfCompanies;
    
    for (int loopCounter = 0; loopCounter < fileNames.size(); loopCounter++) {
        vector<vector<double>> dataForPredictionModel = readDataFromFile(fileNames[loopCounter]); // readDataFromFile("Magic Number");
        vector<vector<double>> yValues;
        
        for (int i = 0; i < dataForPredictionModel.size(); i++) {
            vector<double> test;
            test.push_back(dataForPredictionModel[i].back());
            dataForPredictionModel[i].pop_back();
            yValues.push_back(test);
        }
        
//        DataMatrix y = DataMatrix(yValues);
//        DataMatrix x = DataMatrix(dataForPredictionModel);
//
//        listOfCompanies.push_back(CompanyForecast((((x.transpose() * x).inverse() * x.transpose()) * y).getThetaValues(), fileNames[loopCounter]));
        
        cout << "Company Name: " << fileNames[loopCounter] << endl;
        
        listOfCompanies.push_back(CompanyForecast(returnBestThetaValues(dataForPredictionModel, yValues, readDataFromFile(fileNames[loopCounter]+" Test")), fileNames[loopCounter]));
        
    }
    
    vector<vector<double>> predictionData = readDataFromFile(values.predictionDataCSV);
    vector<double> predictedValues;
    
    for (int forecastIndex = 0; forecastIndex < fileNames.size(); forecastIndex++) {
        predictedValues.push_back(listOfCompanies[forecastIndex].returnCompanyForecast(predictionData[forecastIndex]));
    }
    
    showStockPortofolioPicks(fileNames, predictedValues);
}
