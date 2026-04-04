#include "EEPROMConfig.h"

uint16_t EEPROMConfig::calculateChecksum(const ConfigData& data) {
    uint16_t checksum = CONFIG_CHECKSUM_SEED;
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&data);

    // Calcular checksum de todos los bytes excepto el campo checksum
    for (size_t i = 0; i < sizeof(ConfigData) - sizeof(uint16_t); ++i) {
        checksum ^= bytes[i];
        checksum = (checksum << 1) | (checksum >> 15); // Rotación
    }

    return checksum;
}

bool EEPROMConfig::validateChecksum(const ConfigData& data) {
    return data.checksum == calculateChecksum(data);
}

bool EEPROMConfig::loadConfig(ConfigData& config) {
    // Leer datos desde EEPROM
    EEPROM.get(EEPROM_CONFIG_ADDRESS, config);

    // Verificar checksum
    if (!validateChecksum(config)) {
        Serial.println(F("EEPROM: Checksum invalido, cargando valores por defecto"));
        loadDefaults(config);
        return false;
    }

    Serial.println(F("EEPROM: Configuracion cargada correctamente"));
    return true;
}

bool EEPROMConfig::saveConfig(const ConfigData& config) {
    ConfigData dataToSave = config;
    dataToSave.checksum = calculateChecksum(config);

    // Guardar en EEPROM
    EEPROM.put(EEPROM_CONFIG_ADDRESS, dataToSave);

    // Verificar que se guardó correctamente
    ConfigData verifyData;
    EEPROM.get(EEPROM_CONFIG_ADDRESS, verifyData);

    if (validateChecksum(verifyData) &&
        memcmp(&dataToSave, &verifyData, sizeof(ConfigData) - sizeof(uint16_t)) == 0) {
        Serial.println(F("EEPROM: Configuracion guardada correctamente"));
        return true;
    } else {
        Serial.println(F("EEPROM: Error al guardar configuracion"));
        return false;
    }
}

void EEPROMConfig::loadDefaults(ConfigData& config) {
    config.targetTemperature = 200;  // 200°C por defecto
    config.targetSpeed = 50;         // 50% velocidad por defecto
    config.kp = 3.0f;                // Valores PID por defecto
    config.ki = 0.5f;
    config.kd = 0.05f;
    config.checksum = 0;             // Se calculará al guardar
}

bool EEPROMConfig::hasValidConfig() {
    ConfigData tempConfig;
    EEPROM.get(EEPROM_CONFIG_ADDRESS, tempConfig);
    return validateChecksum(tempConfig);
}