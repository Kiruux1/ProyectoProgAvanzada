#include "ConversionModule.h"
#include <fstream>
#include <iostream>

namespace ConversionModule {

    bool writeStudentDataToBinary(const std::string& filePath, const std::vector<Student>& students) {
        std::ofstream outFile(filePath, std::ios::binary | std::ios::trunc);

        if (!outFile.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo binario para escritura: " << filePath << std::endl;
            return false;
        }

       
        uint32_t numRecords = static_cast<uint32_t>(students.size()); 
        outFile.write(reinterpret_cast<const char*>(&numRecords), sizeof(numRecords));

        
        for (const auto& student : students) {
            
            outFile << student; 
            if (!outFile) { 
                std::cerr << "Error: Fallo al escribir el registro del estudiante al archivo binario (Serial No: " << student.serialNo << ")" << std::endl;
                outFile.close();
                return false;
            }
        }

        outFile.close();
        if (outFile.fail()) { 
             std::cerr << "Error: Fallo al cerrar correctamente el archivo binario: " << filePath << std::endl;
             return false;
        }

        std::cout << "ConversionModule: Escritos exitosamente " << numRecords << " registros al archivo binario: " << filePath << std::endl;
        return true;
    }
}