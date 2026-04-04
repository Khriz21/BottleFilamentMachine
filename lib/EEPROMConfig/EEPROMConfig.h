#ifndef EEPROM_CONFIG_H
#define EEPROM_CONFIG_H

#include <Arduino.h>
#include <EEPROM.h>

// Estructura para almacenar la configuración en EEPROM
struct ConfigData {
    uint8_t targetTemperature;
    uint8_t targetSpeed;
    float kp;
    float ki;
    float kd;
    uint16_t checksum; // Para verificar integridad de datos
};

// Direcciones de memoria EEPROM
#define EEPROM_CONFIG_ADDRESS 0
#define EEPROM_CONFIG_SIZE sizeof(ConfigData)

// Valor por defecto para checksum
#define CONFIG_CHECKSUM_SEED 0xABCD

class EEPROMConfig {
private:
    static uint16_t calculateChecksum(const ConfigData& data);
    static bool validateChecksum(const ConfigData& data);

public:
    // Cargar configuración desde EEPROM
    static bool loadConfig(ConfigData& config);

    // Guardar configuración en EEPROM
    static bool saveConfig(const ConfigData& config);

    // Cargar valores por defecto
    static void loadDefaults(ConfigData& config);

    // Verificar si hay configuración válida en EEPROM
    static bool hasValidConfig();
};

#endif