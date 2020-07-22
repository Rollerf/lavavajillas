#include <Arduino.h>
#include <math.h>

// configurar el pin utilizado para la medicion de voltaje del divisor resistivo del NTC
#define CONFIG_THERMISTOR_ADC_PIN A0
// configurar el valor de la resistencia que va en serie con el termistor NTC en ohms
#define CONFIG_THERMISTOR_RESISTOR 4700
//Numero de muestras para hacer la media
#define NUMERO_MUESTRAS 30

const float A = 1.11492089e-3;
const float B = 2.372075385e-4;
const float C = 6.954079529e-8;
const float K = 2.5; //factor de disipacion en mW/C
const int Vcc = 5;

float calculoNTC()
{
  float raw;
  float V;
  float sumaResistencias;

  for (int i = 0; i <= NUMERO_MUESTRAS; i++) {
    float raw = analogRead(CONFIG_THERMISTOR_ADC_PIN);
    float V =  raw / 1024 * Vcc;
    float R = (CONFIG_THERMISTOR_RESISTOR * V ) / (Vcc - V);

    sumaResistencias += R;
  }

  float R = sumaResistencias / NUMERO_MUESTRAS;

  float logR  = log(R);
  float R_th = 1.0 / (A + B * logR + C * logR * logR * logR );
  float kelvin = R_th - V * V / (K * R) * 1000;

  return kelvin - 273.15;
}
