//
//  main.cpp
//  SupervisedLearningStocks
//
//  Created by Ujjwal Singhania on 6/6/17.
//  Copyright © 2017 Ujjwal Singhania. All rights reserved.
//

#include "Hypothesis.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

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

int main() {
    vector<TrainingExample> trainingExamples = readDataFromFile("mockData.csv");
    Hypothesis companyA = Hypothesis(trainingExamples);
    cout << endl << endl << companyA << endl << endl;
    vector<double> theta = companyA.performGradientDescent();
    for (size_t thetaIndex = 0; thetaIndex < theta.size(); thetaIndex++) {
        cout << "theta[" << thetaIndex << "] = " << theta[thetaIndex] << endl;
    }
}
