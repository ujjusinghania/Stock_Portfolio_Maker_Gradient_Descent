//
//  Hypothesis.cpp
//  SupervisedLearningStocks
//
//  Created by Ujjwal Singhania on 6/8/17.
//  Copyright © 2017 Ujjwal Singhania. All rights reserved.
//

#include "Hypothesis.hpp"
#include "TrainingExample.hpp"
#include "ConstantValues.hpp"
#include <math.h>
using namespace std;

// To get computed Y - multiplication between theta and respective features of a given training example -> (h(theta, x(i) [i'th training example])

double Hypothesis::getComputedY(const std::vector<double>& newThetaValues, const std::vector<double>& featureList) {
    double sum = 0.0;
    for (size_t n = 0; n < numberOfFeatures; n++) {
        sum += newThetaValues[n] * featureList[n];
    }
    return sum;
}

/* To get the square sum of (actual y - computed y) - aka the costFunction.
 
 ∑((h(theta, x(i) [i'th training example]) - y(i) [y value of i'th training example]) * x(i, j) [j'th feature of i'th training example]) -> from i = 0 to numberOfTrainingExamples;
 
*/

double Hypothesis::costFunction(int thetaNumber, const std::vector<double>& newThetaValues) {
    double sum = 0.0;
    for (size_t i = 0; i < numberOfTrainingExamples; i++) {
        sum += (getComputedY(newThetaValues, trainingExamples[i].getAllFeatures()) - trainingExamples[i].getYValue()) * trainingExamples[i].getAllFeatures()[thetaNumber];
    }
  //  cout << sum << endl;
    return sum;
}

/* 
 
 To simultaneously update all the theta values.
 
 theta(j) [j'th thetaValue] = theta(j) [j'th thetaValue] - (alpha/numberOfTrainingExamples) * costFunction(int, vector<double>&)
 
 */

void Hypothesis::updateThetaValues(vector<double>& newThetaValues) {
    for (int thetaNumber = 0; thetaNumber < numberOfFeatures; thetaNumber++) {
        newThetaValues[thetaNumber] -= (constantValues.alpha/numberOfTrainingExamples) * costFunction(thetaNumber, thetaValues);
    }
}

Hypothesis::Hypothesis(std::vector<TrainingExample>& trainingData): trainingExamples(trainingData), numberOfTrainingExamples(trainingData.size()) {
    if (numberOfTrainingExamples > 0) {
        numberOfFeatures = trainingExamples[0].getAllFeatures().size();
    }
    thetaValues = vector<double>(numberOfFeatures, constantValues.thetaValue);
}

std::vector<double> Hypothesis::performGradientDescent() {
    bool costFunctionMinimized = false;
    vector<double> newThetaValues = thetaValues;
    while (!costFunctionMinimized) {
        updateThetaValues(newThetaValues);
        costFunctionMinimized = true;
        for (size_t thetaIndex = 0; thetaIndex < numberOfFeatures; thetaIndex++) {
            double absValue = fabs(thetaValues[thetaIndex] - newThetaValues[thetaIndex]);
            costFunctionMinimized = costFunctionMinimized && absValue < constantValues.benchmark;
            cout << absValue << " ";
        }
        cout << endl;
        thetaValues = newThetaValues;
    }
    return thetaValues;
}

ostream& operator<<(ostream& outputStream, const Hypothesis& hypothesis) {
    for (int m = 0; m < hypothesis.numberOfTrainingExamples; ++m) {
        for (int n = 0; n < hypothesis.numberOfFeatures; ++n) {
            outputStream << hypothesis.trainingExamples[m].getFeatureValue(n) << " ";
        }
        outputStream << hypothesis.trainingExamples[m].getYValue() << endl;
    }
    return outputStream;
}
