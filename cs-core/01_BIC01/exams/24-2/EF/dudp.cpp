#include <iostream>
#include <string>

int main() {
    // ejemplos
    std::string registros[] = {
        "[2024-10-27 10:30:00] ERROR Conexión fallida al servidor.",
        "[2024-10-27 10:31:00] WARNING Disco casi lleno.",
        "[2024-10-27 10:32:00] INFO Sistema operativo iniciado correctamente.",
        "[2024-10-27 10:33:00] ERROR Error crítico en el módulo X.",
        "[2024-10-27 10:34:00] WARNING Posible fuga de memoria.",
        "[2024-10-27 10:35:00] INFO Proceso completado.",
        "[2024-10-27 10:36:00] UNKNOWN Mensaje desconocido."
    };

    int contadorError = 0;
    int contadorWarning = 0;
    int contadorInfo = 0;
    int contadorUnknown = 0;

    std::cout << "Mensajes de ERROR:\n";

    // revisar
    for (const auto& registro : registros) {
        if (registro.find("ERROR") != std::string::npos) {
            std::size_t pos = registro.find("ERROR") + 6;
            std::cout << " " << registro.substr(pos) << std::endl;
            contadorError++;

        } else if (registro.find("WARNING") != std::string::npos) {
            
            contadorWarning++;
        } else if (registro.find("INFO") != std::string::npos) {
            
            contadorInfo++;
        } else if (registro.find("UNKNOWN") != std::string::npos) {
            
            contadorUnknown++;
        }

    }

    std::cout << "Cantidad de mensajes por tipo:\n";
    std::cout << "ERROR: " << contadorError << std::endl;
    std::cout << "WARNING: " << contadorWarning << std::endl;
    std::cout << "INFO: " << contadorInfo << std::endl;
    std::cout << "UNKNOWN: " << contadorUnknown << std::endl;

    return 0;
}
