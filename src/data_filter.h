#ifndef DATA_FILTER_H
#define DATA_FILTER_H

#include <Arduino.h>
#include "config.h"

struct FilteredData {
  float temperatura;
  float humedad;
  float presion;
};

class DataFilter {
private:
  float historialTemperatura[20];
  float historialHumedad[20];
  float historialPresion[20];
  int indice = 0;
  int contador = 0;

public:
  void addData(float temp, float hum, float pres) {
    historialTemperatura[indice] = temp;
    historialHumedad[indice] = hum;
    historialPresion[indice] = pres;
    indice = (indice + 1) % 20;
    if (contador < 20) contador++;
  }

  FilteredData filter() {
    FilteredData result = {0, 0, 0};
    float sumaTemp = 0, sumaHum = 0, sumaPres = 0;
    int count = min(contador, 20);

    if (count == 0) return result;

    for (int i = 0; i < count; i++) {
      sumaTemp += historialTemperatura[i];
      sumaHum += historialHumedad[i];
      sumaPres += historialPresion[i];
    }

    result.temperatura = sumaTemp / count;
    result.humedad = sumaHum / count;
    result.presion = sumaPres / count;

    Serial.print("FILTRADO - T:");
    Serial.print(result.temperatura, 1);
    Serial.print("C H:");
    Serial.print(result.humedad, 1);
    Serial.print("% P:");
    Serial.print(result.presion, 1);
    Serial.println("hPa");

    return result;
  }

  float calculateHumidityTrend() {
    return calculateTrend(historialHumedad, contador);
  }

  float calculatePressureTrend() {
    return calculateTrend(historialPresion, contador);
  }

private:
  float calculateTrend(float* historial, int totalDatos) {
    if (totalDatos < 2) return 0;
    
    float sumaX = 0, sumaY = 0, sumaXY = 0, sumaX2 = 0;
    int puntos = min(totalDatos, 20);

    for (int i = 0; i < puntos; i++) {
      float x = i;
      float y = historial[i];
      sumaX += x;
      sumaY += y;
      sumaXY += x * y;
      sumaX2 += x * x;
    }

    return (puntos * sumaXY - sumaX * sumaY) / (puntos * sumaX2 - sumaX * sumaX);
  }
};

#endif