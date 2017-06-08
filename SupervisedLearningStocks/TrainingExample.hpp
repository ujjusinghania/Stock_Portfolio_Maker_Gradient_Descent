//
//  TrainingExample.hpp
//  SupervisedLearningStocks
//
//  Created by Ujjwal Singhania on 6/8/17.
//  Copyright © 2017 Ujjwal Singhania. All rights reserved.
//

#ifndef TrainingExample_hpp
#define TrainingExample_hpp

#include <stdio.h>
#include <vector>

class TrainingExample {
    
    std::vector<double> featureList;
    double yValue;
    
public:
    
    TrainingExample(const std::vector<double>& features, double tar);
    double getFeatureValue(int index) const;
    std::vector<double>& getAllFeatures();
    double getYValue() const;
    friend std::ostream& operator<<(std::ostream& outputStream, const TrainingExample& trainingData);
    
};

#endif /* TrainingExample_hpp */
