//
//  PortfolioValues.h
//  SupervisedLearningStocks
//
//  Created by Ujjwal Singhania on 6/12/17.
//  Copyright © 2017 Ujjwal Singhania. All rights reserved.
//

#ifndef PortfolioValues_h
#define PortfolioValues_h

#include <string>

struct Data {
    
    std::vector<std::string> CSVNames = {
        "BharatPetroleum",
        "AbanOffshore",
        "CoalIndia",
        "GujaratMineral",
        "HindustanPetroleum",
        "IndianOil",
        "OilIndia",
        "OilNaturalGasCorp",
        "RelianceIndustries"
    };
    
    std::string predictionDataCSV = "PredictionData.csv";
    
};

#endif /* PortfolioValues_h */
