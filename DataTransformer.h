#ifndef DATATRANSFORMER_H
#define DATATRANSFORMER_H

#include <string>
#include <vector>
#include "Student.h" 

namespace DataTransformer {
   
    std::vector<Student> readCSV(const std::string& filePath);

   
}

#endif 