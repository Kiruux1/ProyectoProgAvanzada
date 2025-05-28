#include <iostream>
#include <vector>
#include <string>
#include <limits> 

#include "EnvLoader.h"
#include "SFTPClient.h" 
#include "DataTransformer.h"
#include "AnalysisModule.h"
#include "ConversionModule.h"
#include "Student.h" 

void displayMenu() {
    std::cout << "\n--- Menú del Pipeline ETL ---" << std::endl;
    std::cout << "1. Cargar y Procesar Datos (desde CSV local)" << std::endl;
    std::cout << "2. Mostrar Estadísticas Generales" << std::endl;
    std::cout << "3. Mostrar Estadísticas Descriptivas" << std::endl;
    std::cout << "4. Mostrar Análisis de Correlación" << std::endl;
    std::cout << "5. Generar Informe de Análisis (analysis_report.txt)" << std::endl;
    std::cout << "6. Generar Archivo Binario de Estudiantes (students.dat)" << std::endl;
    std::cout << "7. Salir" << std::endl;
    std::cout << "Ingrese su opción: ";
}

int main() {
    EnvLoader::Config config = EnvLoader::loadEnv();

    
    SFTPClient::downloadFile(config.csvFilePath); 

    std::vector<Student> studentsData;
    bool dataLoaded = false;

    int choice;
    do {
        displayMenu();
        std::cin >> choice;

       
        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Entrada inválida. Por favor, ingrese un número." << std::endl;
            choice = 0; 
        } else {
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }


        switch (choice) {
            case 1:
                std::cout << "\n--- Cargando y Procesando Datos ---" << std::endl;
                studentsData = DataTransformer::readCSV(config.csvFilePath);
                if (!studentsData.empty()) {
                    std::cout << "Datos cargados exitosamente. " << studentsData.size() << " registros." << std::endl;
                    dataLoaded = true;
                } else {
                    std::cout << "Fallo al cargar datos o el archivo de datos está vacío." << std::endl;
                    dataLoaded = false;
                }
                break;
            case 2:
                if (dataLoaded) {
                    AnalysisModule::displayGeneralStatistics(studentsData, std::cout);
                } else {
                    std::cout << "No hay datos cargados. Por favor, cargue los datos primero (Opción 1)." << std::endl;
                }
                break;
            case 3:
                if (dataLoaded) {
                    AnalysisModule::displayDescriptiveStatistics(studentsData, std::cout);
                } else {
                    std::cout << "No hay datos cargados. Por favor, cargue los datos primero (Opción 1)." << std::endl;
                }
                break;
            case 4:
                if (dataLoaded) {
                    AnalysisModule::displayCorrelationAnalysis(studentsData, std::cout);
                } else {
                    std::cout << "No hay datos cargados. Por favor, cargue los datos primero (Opción 1)." << std::endl;
                }
                break;
            case 5:
                if (dataLoaded) {
                    if (AnalysisModule::generateAnalysisReport("analysis_report.txt", studentsData)) {
                        std::cout << "Informe de análisis generado: analysis_report.txt" << std::endl;
                    } else {
                        std::cout << "Fallo al generar el informe de análisis." << std::endl;
                    }
                } else {
                    std::cout << "No hay datos cargados. Por favor, cargue los datos primero (Opción 1)." << std::endl;
                }
                break;
            case 6:
                if (dataLoaded) {
                    if (ConversionModule::writeStudentDataToBinary("students.dat", studentsData)) {
                        std::cout << "Archivo binario de estudiantes generado: students.dat" << std::endl;
                    } else {
                        std::cout << "Fallo al generar el archivo binario de estudiantes." << std::endl;
                    }
                } else {
                    std::cout << "No hay datos cargados. Por favor, cargue los datos primero (Opción 1)." << std::endl;
                }
                break;
            case 7:
                std::cout << "Saliendo del pipeline. ¡Adiós!" << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Por favor, intente de nuevo." << std::endl;
        }
    } while (choice != 7);

    return 0;
}