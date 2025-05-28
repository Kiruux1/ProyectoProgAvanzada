#include "SFTPClient.h"
#include <iostream>

namespace SFTPClient {
    bool downloadFile(const std::string& localPath) {
        std::cout << "SFTPClient: Operando en modo local. Descarga de archivo omitida." << std::endl;
        std::cout << "SFTPClient: Asegúrese de que '" << localPath << "' esté disponible localmente." << std::endl;
        return true; 
    }
}