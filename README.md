# BottleFilamentMachine

Proyecto de máquina extrusora de filamento usando un chip ATmega 328P como microprocesador.

## 📋 Descripción

Esta es una máquina extrusora de filamento 3D construida con Arduino UNO (ATmega 328P) que permite reciclar botellas de plástico PET para crear filamento de impresora 3D. El sistema incluye control de temperatura PID, control de velocidad del motor, interfaz LCD con encoder rotativo y menú interactivo.

## 🔧 Componentes Requeridos

### Hardware
- Arduino UNO (ATmega 328P)
- Display LCD 16x2 con interfaz I2C
- Encoder rotativo con botón integrado
- Motor paso a paso NEMA 17 + driver A4988
- Termistor NTC 100K
- Resistor de 100KΩ (divisor de voltaje)
- Transistor MOSFET (para control de calentador)
- Calentador de resistencia (cartridge heater)
- Fuente de alimentación 12V/5A
- Protoboard y cables de conexión

### Software
- PlatformIO IDE
- Librerías Arduino:
  - LiquidCrystal_I2C
  - TimerOne
  - Time

## 🔌 Esquema de Conexiones

### Display LCD I2C (0x27)
- VCC → 5V
- GND → GND
- SDA → A4
- SCL → A5

### Encoder Rotativo
- CLK → Pin 4
- DT → Pin 2
- SW → Pin 3
- VCC → 5V
- GND → GND

### Motor Paso a Paso (A4988)
- ENABLE → Pin 10
- DIR → Pin 11
- STEP → Pin 12
- VCC → 5V
- GND → GND
- VMOT → 12V
- GND → GND

### Termistor
- Señal → A0
- GND → GND
- VCC → 5V (a través de resistor 100K)

### Calentador
- Control → Pin 9 (PWM)
- VCC → 12V
- GND → GND

## 🚀 Instalación y Configuración

### 1. Clonar el repositorio
```bash
git clone <url-del-repositorio>
cd BottleFilamentMachine
```

### 2. Instalar dependencias
```bash
pio pkg install
```

### 3. Configurar PlatformIO
El archivo `platformio.ini` ya está configurado para Arduino UNO con las librerías necesarias.

### 4. Compilar y subir
```bash
pio run -t upload
```

## 🎛️ Uso del Sistema

### Pantalla Principal (Home Screen)
Muestra:
- Temperatura objetivo vs actual
- Velocidad del motor objetivo
- Estado del sistema

### Menú Principal
- **Motor**: Encender/apagar el motor de extrusión
- **Heater**: Encender/apagar el calentador
- **Set Temp**: Configurar temperatura objetivo (0-300°C)
- **Set Speed**: Configurar velocidad del motor (0-100%)
- **Tuning PID**: Ajustar parámetros del controlador PID
- **Save Config**: Guardar configuración actual en EEPROM
- **Exit**: Volver a pantalla principal

### Navegación
- **Girar encoder**: Navegar por menús y ajustar valores
- **Presionar encoder**: Seleccionar opción o confirmar

## 💾 Persistencia de Configuración (EEPROM)

El sistema guarda automáticamente la configuración en la memoria EEPROM del Arduino para mantener los ajustes entre reinicios.

### Datos Guardados
- Temperatura objetivo
- Velocidad del motor objetivo
- Parámetros PID (Kp, Ki, Kd)

### Valores por Defecto
- Temperatura: 200°C
- Velocidad: 50%
- Kp: 3.0
- Ki: 0.5
- Kd: 0.05

### Guardar Configuración
1. Acceder al menú principal
2. Seleccionar "Save Config"
3. La configuración se guarda automáticamente en EEPROM
4. Se muestra confirmación por puerto serial

### Carga Automática
Al iniciar el sistema, se carga automáticamente la configuración guardada. Si no hay configuración válida, se usan los valores por defecto.

## 📁 Estructura del Proyecto

```
BottleFilamentMachine/
├── include/                 # Archivos de configuración
│   └── PinConfig.h         # Definición de pines
├── lib/                    # Librerías personalizadas
│   ├── Display/            # Control del LCD
│   ├── Encoder/            # Manejo del encoder rotativo
│   ├── Menu/               # Sistema de menús
│   ├── MenuItem/           # Items del menú
│   ├── Motor/              # Control del motor paso a paso
│   ├── PIDController/      # Controlador PID
│   └── Thermistor/         # Lectura del termistor
├── src/                    # Código fuente principal
│   ├── main.cpp           # Punto de entrada Arduino
│   ├── App.h              # Declaración de la clase App
│   └── App.cpp            # Implementación de la aplicación
├── test/                   # Tests unitarios
├── platformio.ini         # Configuración PlatformIO
├── wokwi.toml            # Configuración Wokwi (simulación)
└── README.md             # Esta documentación
```

## 🔧 Troubleshooting

### Problemas comunes:

1. **LCD no muestra nada**
   - Verificar dirección I2C (0x27)
   - Comprobar conexiones SDA/SCL
   - Verificar alimentación 5V

2. **Encoder no responde**
   - Verificar pines CLK(4), DT(2), SW(3)
   - Comprobar conexiones de alimentación

3. **Motor no gira**
   - Verificar conexiones del driver A4988
   - Comprobar corriente de motor (VMOT)
   - Verificar señal ENABLE baja

4. **Configuración no se guarda**
   - Verificar que se seleccionó "Save Config" en el menú
   - Comprobar mensajes por Serial para confirmación
   - EEPROM puede tener límite de ~100,000 escrituras

5. **Valores por defecto al reiniciar**
   - EEPROM corrupta o sin configuración previa
   - Se cargan automáticamente valores por defecto
   - Guardar nueva configuración para persistir

### Debug por Serial
El sistema incluye mensajes de debug por Serial a 9600 baudios:
- Estados del menú
- Lecturas de temperatura
- Velocidad del motor
- Errores del sistema

## 🔄 Próximas Mejoras

- [x] **Guardar configuración en EEPROM** ✅ IMPLEMENTADO
- [ ] Sensor de velocidad de filamento
- [ ] Botón de emergencia (ESTOP)
- [ ] Control automático de alimentación
- [ ] Interfaz Bluetooth/WiFi
- [ ] Tests unitarios completos
- [ ] Documentación técnica detallada

## 📄 Licencia

Este proyecto es de código abierto. Consulta el archivo LICENSE para más detalles.

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor, abre un issue para discutir cambios mayores antes de enviar un pull request.

