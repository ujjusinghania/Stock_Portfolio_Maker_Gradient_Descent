//
//  CompanyForecast.hpp
//  SupervisedLearningStocks
//
//  Created by Ujjwal Singhania on 6/12/17.
//  Copyright © 2017 Ujjwal Singhania. All rights reserved.
//

#ifndef CompanyForecast_hpp
#define CompanyForecast_hpp

#include <stdio.h>
#include <vector>
#include <iostream>

class CompanyForecast {
    
    std::vector<double> thetaValues;
    std::string companyName;
    
public:
    
    CompanyForecast(const std::vector<double>& thetaVal, const std::string& company);
    double returnCompanyForecast(const std::vector<double>& predictionValues);
    std::string getCompanyName() const;
    friend std::ostream& operator<<(std::ostream& outputStream, const CompanyForecast& company);
    
};

#endif /* CompanyForecast_hpp */
