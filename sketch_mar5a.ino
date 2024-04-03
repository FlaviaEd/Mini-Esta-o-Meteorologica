#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SPI.h>
#include <SD.h>

BH1750 medidorDeLuz;
Adafruit_BME280 bme; // I2C

#define PRESSAO_NIVEL_DO_MAR_HPA (1013.25)
const int pinoSensorUV = A0;
const int chipSelect = D8;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  medidorDeLuz.begin();
  
  if (!bme.begin(0x76)) {
    Serial.println("Não foi possível encontrar um sensor BME280 válido, verifique a fiação!");
    while (1);
  }
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Falha ao inicializar o cartão SD.");
    return;
  }
  Serial.println("Cartão SD inicializado com sucesso.");
}

void loop() {
  float lux = medidorDeLuz.readLightLevel();
  Serial.print("Luz: ");
  Serial.print(lux);
  Serial.println(" lx");

  Serial.print("Temperatura = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  Serial.print("Pressão = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Altitude Aprox. = ");
  Serial.print(bme.readAltitude(PRESSAO_NIVEL_DO_MAR_HPA));
  Serial.println(" m");

  Serial.print("Umidade = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  int valorSensor = analogRead(pinoSensorUV);
  float voltagem = valorSensor * (3.3 / 1023.0);
  float intensidadeUV = voltagem * 307.0;

  Serial.print("Intensidade UV: ");
  Serial.print(intensidadeUV);
  Serial.println(" mW/cm^2");

  delay(1000);

  // Se tudo estiver ok, escrevemos os dados a serem armazenados em uma String  
}

