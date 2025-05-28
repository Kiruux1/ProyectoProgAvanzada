#ifndef ENVLOADER_H
#define ENVLOADER_H

#include <string>
#include <vector> 

namespace EnvLoader {

    struct Config {
        std::string csvFilePath;
      
    };

    Config loadEnv(); 
}

#endif 