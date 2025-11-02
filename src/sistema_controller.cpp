#include "sistema_controller.h"
#include "config.h"

// ======================
// DEFINICIONES DE CONFIG BACKEND
// ======================
const char* BACKEND_URL = "http://tu-backend.com";
const char* BACKEND_ENDPOINT = "/api/datos-climaticos";
const int BACKEND_PORT = 80;

// ======================
// VARIABLES GLOBALES
// ======================
FilteredData datosFiltrados;
unsigned long ultimaLectura = 0;
unsigned long ultimoFiltrado = 0;
unsigned long ultimoEnvio = 0;

// ======================
// VARIABLES ETHERNET
// ======================
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 177);
EthernetClient ethClient;
HttpClient httpClient = HttpClient(ethClient, BACKEND_URL, BACKEND_PORT);

// ======================
// INSTANCIAS GLOBALES
// ======================
SensorController sensorController;
DataFilter dataFilter;
PredictionEngine predictionEngine;
HttpClientBackend httpBackend;

// ======================
// IMPLEMENTACIÓN DE FUNCIONES
// ======================
void leerSensores() {
  SensorData datos = sensorController.readSensors();
  
  // Validar datos antes de agregarlos al filtro
  if (datos.temperatura > -40 && datos.temperatura < 85 && 
      datos.humedad >= 0 && datos.humedad <= 100 &&
      datos.presion > 800 && datos.presion < 1100) {
    dataFilter.addData(datos.temperatura, datos.humedad, datos.presion);
  } else {
    Serial.println("Datos de sensores invalidos - descartados");
  }
}

void filtrarDatos() {
  datosFiltrados = dataFilter.filter();
  
  if (datosFiltrados.humedad > 0) {
    float tendenciaHumedad = dataFilter.calculateHumidityTrend();
    float tendenciaPresion = dataFilter.calculatePressureTrend();
    
    Serial.print("Tendencia Humedad: ");
    Serial.println(tendenciaHumedad, 4);
    Serial.print("Tendencia Presion: ");
    Serial.println(tendenciaPresion, 4);
    
    predictionEngine.predict(datosFiltrados.temperatura, datosFiltrados.humedad, 
                           datosFiltrados.presion, tendenciaHumedad, tendenciaPresion);
  }
}

void enviarAlBackend() {
  if (datosFiltrados.humedad > 0) {
    float tendenciaHumedad = dataFilter.calculateHumidityTrend();
    float tendenciaPresion = dataFilter.calculatePressureTrend();
    int alerta = predictionEngine.predict(datosFiltrados.temperatura, datosFiltrados.humedad, 
                                        datosFiltrados.presion, tendenciaHumedad, tendenciaPresion);
    
    bool exito = httpBackend.sendData(
      datosFiltrados.temperatura,
      datosFiltrados.humedad, 
      datosFiltrados.presion,
      alerta
    );
    
    if (exito) {
      Serial.println("Datos enviados correctamente");
    } else {
      Serial.println("Error enviando datos");
    }
    
    // Información del estado de los sensores
    #if !MODO_SIMULACION
      Serial.print("BMP280 Disponible: ");
      Serial.println(sensorController.isBMP280Available() ? "SI" : "NO");
    #endif
    
    Serial.println("------------------------------------");
  }
}