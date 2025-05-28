#ifndef ANALYSISMODULE_H
#define ANALYSISMODULE_H

#include <vector>
#include <string>
#include <map>
#include <ostream> 
#include "Student.h" 

namespace AnalysisModule {

    struct ColumnStats {
        double mean = 0.0;
        double median = 0.0;
        double stddev = 0.0;
        double min = 0.0;
        double max = 0.0;
       
    };

  
    void displayGeneralStatistics(const std::vector<Student>& students, std::ostream& out);

    
    ColumnStats calculateDescriptiveStatistics(const std::vector<double>& data);

    void displayDescriptiveStatistics(const std::vector<Student>& students, std::ostream& out);

 
    double calculateCorrelation(const std::vector<double>& data1, const std::vector<double>& data2);
    void displayCorrelationAnalysis(const std::vector<Student>& students, std::ostream& out);

   
    bool generateAnalysisReport(const std::string& filePath, const std::vector<Student>& students);
}

#endif 