#include "DataTransformer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept> 

namespace DataTransformer {

   
    std::string trim(const std::string& str) {
        const std::string whitespace = " \t\n\r\f\v";
        size_t start = str.find_first_not_of(whitespace);
        if (start == std::string::npos) return "";
        size_t end = str.find_last_not_of(whitespace);
        return str.substr(start, end - start + 1);
    }

    std::vector<Student> readCSV(const std::string& filePath) {
        std::vector<Student> students;
        std::ifstream file(filePath);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo CSV: " << filePath << std::endl;
            return students; 
        }

        
        if (!std::getline(file, line)) {
            std::cerr << "Error: El archivo CSV está vacío o el encabezado no se pudo leer." << std::endl;
            return students;
        }

        
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string field;
            Student student;
            std::vector<std::string> fields;

            while(std::getline(ss, field, ',')) {
                fields.push_back(trim(field));
            }

            if (fields.size() == 9) { 
                try {
                    student.serialNo = std::stoi(fields[0]);
                    student.greScore = std::stoi(fields[1]);
                    student.toeflScore = std::stoi(fields[2]);
                    student.universityRating = std::stoi(fields[3]);
                    student.sop = std::stof(fields[4]);
                    student.lor = std::stof(fields[5]); 
                    student.cgpa = std::stof(fields[6]);
                    student.research = std::stoi(fields[7]);
                    student.chanceOfAdmit = std::stof(fields[8]); 
                    students.push_back(student);
                } catch (const std::invalid_argument& ia) {
                    std::cerr << "Advertencia: Formato de datos inválido en línea CSV, omitiendo: " << line << " (" << ia.what() << ")" << std::endl;
                } catch (const std::out_of_range& oor) {
                    std::cerr << "Advertencia: Dato fuera de rango en línea CSV, omitiendo: " << line << " (" << oor.what() << ")" << std::endl;
                }
            } else {
                if (!line.empty()) { 
                     std::cerr << "Advertencia: Número incorrecto de campos en línea CSV, omitiendo: " << line << " (Esperados 9, Obtenidos " << fields.size() << ")" << std::endl;
                }
            }
        }
        file.close();
        std::cout << "DataTransformer: Leídos exitosamente " << students.size() << " registros de " << filePath << std::endl;
        return students;
    }
}