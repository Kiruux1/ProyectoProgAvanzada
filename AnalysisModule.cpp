#include "AnalysisModule.h"
#include <iostream>
#include <fstream>
#include <numeric>   
#include <algorithm>  
#include <cmath>     
#include <iomanip>    

namespace AnalysisModule {

    void displayGeneralStatistics(const std::vector<Student>& students, std::ostream& out) {
        out << "--- Estadísticas Generales ---" << std::endl;
        out << "Número total de registros de estudiantes: " << students.size() << std::endl;
        if (!students.empty()) {
            out << "Número de características por registro: 9" << std::endl; 
        }
        out << "----------------------------" << std::endl << std::endl;
    }

    ColumnStats calculateDescriptiveStatistics(const std::vector<double>& data) {
        ColumnStats stats;
        if (data.empty()) {
            return stats; 
        }

        
        stats.min = *std::min_element(data.begin(), data.end());
        stats.max = *std::max_element(data.begin(), data.end());

 
        stats.mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();

  
        std::vector<double> sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());
        if (sortedData.size() % 2 == 0) {
            stats.median = (sortedData[sortedData.size() / 2 - 1] + sortedData[sortedData.size() / 2]) / 2.0;
        } else {
            stats.median = sortedData[sortedData.size() / 2];
        }

        
        double sumSqDiff = 0.0;
        for (double val : data) {
            sumSqDiff += std::pow(val - stats.mean, 2);
        }
        stats.stddev = std::sqrt(sumSqDiff / data.size());

        return stats;
    }

 
    std::vector<double> getColumnData(const std::vector<Student>& students, const std::string& columnName) {
        std::vector<double> column;
        for (const auto& s : students) {
            if (columnName == "GRE Score") column.push_back(static_cast<double>(s.greScore));
            else if (columnName == "TOEFL Score") column.push_back(static_cast<double>(s.toeflScore));
            else if (columnName == "University Rating") column.push_back(static_cast<double>(s.universityRating));
            else if (columnName == "SOP") column.push_back(s.sop);
            else if (columnName == "LOR") column.push_back(s.lor); 
            else if (columnName == "CGPA") column.push_back(s.cgpa);
            else if (columnName == "Research") column.push_back(static_cast<double>(s.research));
            else if (columnName == "Chance of Admit") column.push_back(s.chanceOfAdmit); 
        }
        return column;
    }

    void displayDescriptiveStatistics(const std::vector<Student>& students, std::ostream& out) {
        out << "--- Estadísticas Descriptivas ---" << std::endl;
        out << std::fixed << std::setprecision(2);

        std::vector<std::string> columns = {"GRE Score", "TOEFL Score", "University Rating", "SOP", "LOR", "CGPA", "Chance of Admit"};

        if (students.empty()) {
            out << "No hay datos disponibles para calcular estadísticas descriptivas." << std::endl;
            out << "-------------------------------" << std::endl << std::endl;
            return;
        }

        for (const auto& colName : columns) {
            std::vector<double> data = getColumnData(students, colName);
            if (data.empty() && colName != "Research") {
                 out << "La columna '" << colName << "' no tiene datos o no es numérica." << std::endl;
                 continue;
            }
         
            ColumnStats stats = calculateDescriptiveStatistics(data);
            out << "Columna: " << colName << std::endl;
            out << "  Media:    " << stats.mean << std::endl;
            out << "  Mediana:  " << stats.median << std::endl;
            out << "  DesvEst:  " << stats.stddev << std::endl;
            out << "  Mín:      " << stats.min << std::endl;
            out << "  Máx:      " << stats.max << std::endl;
            out << std::endl;
        }
        out << "-------------------------------" << std::endl << std::endl;
    }

    double calculateCorrelation(const std::vector<double>& data1, const std::vector<double>& data2) {
        if (data1.size() != data2.size() || data1.empty()) {
            return 0.0;
        }

        size_t n = data1.size();
        double sumX = std::accumulate(data1.begin(), data1.end(), 0.0);
        double sumY = std::accumulate(data2.begin(), data2.end(), 0.0);
        double sumXY = std::inner_product(data1.begin(), data1.end(), data2.begin(), 0.0);
        double sumX2 = std::inner_product(data1.begin(), data1.end(), data1.begin(), 0.0);
        double sumY2 = std::inner_product(data2.begin(), data2.end(), data2.begin(), 0.0);

        double numerator = n * sumXY - sumX * sumY;
        double denominator = std::sqrt((n * sumX2 - sumX * sumX) * (n * sumY2 - sumY * sumY));

        if (denominator == 0) {
            return 0.0;
        }
        return numerator / denominator;
    }

    void displayCorrelationAnalysis(const std::vector<Student>& students, std::ostream& out) {
        out << "--- Análisis de Correlación (Pearson) ---" << std::endl;
        out << std::fixed << std::setprecision(4);

        if (students.empty()) {
            out << "No hay datos disponibles para calcular correlaciones." << std::endl;
            out << "---------------------------------------" << std::endl << std::endl;
            return;
        }

      
        std::vector<std::pair<std::string, std::string>> pairsToCorrelate = {
            {"GRE Score", "Chance of Admit"},
            {"TOEFL Score", "Chance of Admit"},
            {"CGPA", "Chance of Admit"},
            {"University Rating", "Chance of Admit"},
            {"SOP", "Chance of Admit"},
            {"LOR", "Chance of Admit"},
            {"Research", "Chance of Admit"},
            {"GRE Score", "CGPA"}
        };

        for (const auto& p : pairsToCorrelate) {
            std::vector<double> data1 = getColumnData(students, p.first);
            std::vector<double> data2 = getColumnData(students, p.second);

            if(data1.empty() || data2.empty()){
                out << "No se pudo calcular la correlación para: " << p.first << " y " << p.second << " (datos vacíos)" << std::endl;
                continue;
            }

            double corr = calculateCorrelation(data1, data2);
            out << "Correlación entre '" << p.first << "' y '" << p.second << "': " << corr << std::endl;
        }
        out << "---------------------------------------" << std::endl << std::endl;
    }

    bool generateAnalysisReport(const std::string& filePath, const std::vector<Student>& students) {
        std::ofstream reportFile(filePath);
        if (!reportFile.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo de informe para escritura: " << filePath << std::endl;
            return false;
        }

        reportFile << "===================================" << std::endl;
        reportFile << "    ANÁLISIS DE ADMISIÓN DE ESTUDIANTES     " << std::endl;
        reportFile << "===================================" << std::endl << std::endl;

        displayGeneralStatistics(students, reportFile);
        displayDescriptiveStatistics(students, reportFile);
        displayCorrelationAnalysis(students, reportFile);

        reportFile.close();
        std::cout << "AnalysisModule: Informe de análisis generado exitosamente en " << filePath << std::endl;
        return true;
    }
}