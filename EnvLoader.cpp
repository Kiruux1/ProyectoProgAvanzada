#include "EnvLoader.h"
#include <iostream>

namespace EnvLoader {
    Config loadEnv() {
        Config config;
     
        config.csvFilePath = "Admission_Predict.csv"; 

   
        std::cout << "EnvLoader: Usando archivo CSV local: " << config.csvFilePath << std::endl;
        return config;
    }
}