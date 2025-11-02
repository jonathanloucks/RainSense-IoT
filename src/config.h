#ifndef CONFIG_H
#define CONFIG_H

// ======================
// CONFIGURACIÓN MODO
// ======================
#define MODO_SIMULACION true  // false para hardware real

// ======================
// CONFIGURACIÓN SENSORES
// ======================
#if !MODO_SIMULACION
  #define DHTPIN 7
  #define DHTTYPE DHT22
  #define BMP280_I2C_ADDRESS 0x76  // Dirección I2C del BMP280
#endif

// ======================
// CONFIGURACIÓN TIEMPOS
// ======================
const unsigned long INTERVALO_LECTURA = 5000;    // 5 segundos
const unsigned long INTERVALO_FILTRADO = 30000;  // 30 segundos
const unsigned long INTERVALO_ENVIO = 60000;     // 1 minuto

// ======================
// CONFIGURACIÓN BACKEND (CAMBIADO A extern)
// ======================
extern const char* BACKEND_URL;
extern const char* BACKEND_ENDPOINT;
extern const int BACKEND_PORT;

// ======================
// UMBRALES PREDICCIÓN MEJORADOS
// ======================
const float HUMEDAD_ALERTA = 85.0;
const float HUMEDAD_ADVERTENCIA = 75.0;
const float TENDENCIA_ALERTA = 0.3;
const float TENDENCIA_ADVERTENCIA = 0.1;

// NUEVAS CONSTANTES PARA EL SISTEMA MULTIVARIABLE
const float HUMEDAD_ALERTA_ROJA = 85.0;
const float HUMEDAD_ALERTA_AMARILLA = 75.0;
const float PRESION_BAJA_ALERTA = 1005.0;
const float PRESION_BAJA_ADVERTENCIA = 1010.0;
const float TENDENCIA_HUMEDAD_ALERTA = 0.4;
const float TENDENCIA_HUMEDAD_ADVERTENCIA = 0.2;
const float TENDENCIA_PRESION_ALERTA = -0.3;

#endif