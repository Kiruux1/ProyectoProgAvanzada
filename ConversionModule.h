#ifndef CONVERSIONMODULE_H
#define CONVERSIONMODULE_H

#include <string>
#include <vector>
#include "Student.h" 

namespace ConversionModule {
    bool writeStudentDataToBinary(const std::string& filePath, const std::vector<Student>& students);
}

#endif