#ifndef SENSOR_CONTROLLER_H
#define SENSOR_CONTROLLER_H

#include <DHT.h>
#include "config.h"

#if !MODO_SIMULACION
  #include <Adafruit_BMP280.h>
  DHT dht(DHTPIN, DHTTYPE);
  Adafruit_BMP280 bmp; // I2C
#endif

struct SensorData {
  float temperatura;
  float humedad;
  float presion;
  unsigned long timestamp;
};

class SensorController {
private:
  bool bmp280Disponible = false;

public:
  void begin() {
    #if !MODO_SIMULACION
      dht.begin();
      
      // Inicializar BMP280
      if (bmp.begin(BMP280_I2C_ADDRESS)) {
        bmp280Disponible = true;
        Serial.println("BMP280 inicializado correctamente");
      } else {
        bmp280Disponible = false;
        Serial.println("ERROR: No se pudo encontrar el BMP280");
      }
    #endif
  }

  SensorData readSensors() {
    SensorData data;
    data.timestamp = millis();
    
    #ifdef MODO_SIMULACION
      // SIMULACION MEJORADA CON CORRELACION
      float baseHumedad = 40 + random(6000) / 100.0;  // 40.0 - 100.0%
      
      // Correlacion realista entre variables
      if (baseHumedad > 80) {
        data.presion = 1000.0 + random(1500) / 100.0;  // 1000.0 - 1015.0 hPa
        data.temperatura = 18.0 + random(1500) / 100.0; // 18.0 - 33.0°C
      } else if (baseHumedad > 60) {
        data.presion = 1010.0 + random(1500) / 100.0;  // 1010.0 - 1025.0 hPa
        data.temperatura = 22.0 + random(1800) / 100.0; // 22.0 - 40.0°C
      } else {
        data.presion = 1015.0 + random(1500) / 100.0;  // 1015.0 - 1030.0 hPa
        data.temperatura = 25.0 + random(2000) / 100.0; // 25.0 - 45.0°C
      }
      
      data.humedad = max(30.0f, min(100.0f, baseHumedad));
      
      Serial.print("SIMULACION - ");
    #else
      // MODO REAL - LECTURA DE SENSORES FISICOS
      
      // Leer DHT22 (Temperatura y Humedad)
      data.temperatura = dht.readTemperature();
      data.humedad = dht.readHumidity();
      
      if (isnan(data.temperatura) || isnan(data.humedad)) {
        Serial.println("Error leyendo DHT22 fisico");
        data.temperatura = -1;
        data.humedad = -1;
        data.presion = -1;
        return data;
      }
      
      // Leer BMP280 (Presion y temperatura alternativa)
      if (bmp280Disponible) {
        data.presion = bmp.readPressure() / 100.0; // Convertir Pa a hPa
        float tempBMP = bmp.readTemperature();
        
        // Usar promedio de temperaturas si ambas están disponibles
        if (!isnan(tempBMP) && tempBMP > -40 && tempBMP < 85) {
          data.temperatura = (data.temperatura + tempBMP) / 2.0;
        }
      } else {
        // Fallback si BMP280 no está disponible
        data.presion = 1013.0; // Presión estándar
        Serial.println("AVISO: Usando presion por defecto - BMP280 no disponible");
      }
      
      Serial.print("REAL - ");
    #endif

    Serial.print("T:");
    Serial.print(data.temperatura, 1);
    Serial.print("C H:");
    Serial.print(data.humedad, 1);
    Serial.print("% P:");
    Serial.print(data.presion, 1);
    Serial.println("hPa");

    return data;
  }

  bool isBMP280Available() {
    #if !MODO_SIMULACION
      return bmp280Disponible;
    #else
      return true; // En simulación siempre está "disponible"
    #endif
  }
};

#endif