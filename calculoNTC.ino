/**
   GeekFactory - "INNOVATING TOGETHER"
   Distribucion de materiales para el desarrollo e innovacion tecnologica
   www.geekfactory.mx

   EJEMPLO SENCILLO PARA LECTURA DE TEMPERATURA CON TERMISTOR NTC. EL PROGRAMA
   ESTÁ DISENADO PARA TERMISTORES NTC DE 10K NOMINALES A 25 GRADOS CENTIGRADOS.
   EL TERMISTOR DEBE SER CONECTADO A LA ENTRADA DEL ADC MEDIANTE UN ARREGLO DE
   DIVISOR RESISTIVO REALIZADO CON RESISTENCIA DE 10K Y EL TERMISTOR EN SERIE.
   EL ALGORITMO UTILIZADO PARA OBTENER LA TEMPERATURA A PARTIR DE LA RESISTENCIA
   DEL TERMISTOR ES UNA IMPLEMENTACIÓN DE LA ECUACIÓN DE STEINHART-HART
*/
#include <Arduino.h>
#include <math.h>

// configurar el pin utilizado para la medicion de voltaje del divisor resistivo del NTC
#define CONFIG_THERMISTOR_ADC_PIN A0
// configurar el valor de la resistencia que va en serie con el termistor NTC en ohms
#define CONFIG_THERMISTOR_RESISTOR 9900l

/**
   @brief Obtiene la resistencia del termistor resolviendo el divisor resistivo.

   @param adcval Valor medido por el convertidor analógico a digital.
   @return int32_t Resistencia electrica del termistor.
*/
int32_t thermistor_get_resistance(uint16_t adcval)
{
  // calculamos la resistencia del NTC a partir del valor del ADC
  return (CONFIG_THERMISTOR_RESISTOR * ((1023.0 / adcval) - 1));
}

/**
   @brief Obtiene la temperatura en grados centigrados a partir de la resistencia
   actual del componente.

   @param resistance Resistencia actual del termistor.
   @return float Temperatura en grados centigrados.
*/
float thermistor_get_temperature(int32_t resistance)
{
  // variable de almacenamiento temporal, evita realizar varias veces el calculo de log
  float temp;

  // calculamos logaritmo natural, se almacena en variable para varios calculos
  temp = log(resistance);

  // resolvemos la ecuacion de STEINHART-HART
  // http://en.wikipedia.org/wiki/Steinhart–Hart_equation
  temp = 1 / (0.001129148 + (0.000234125 * temp) + (0.0000000876741 * temp * temp * temp));

  // convertir el resultado de kelvin a centigrados y retornar
  return temp - 273.15;
}

float calculoNTC()
{
  // variable para almacenar la temperatura y resistencia
  float sumaTemperaturas;
  const byte numeroMuestras = 30;
  float temperaturaMedia;

  for (int i = 0; i <= numeroMuestras; i++) {
    // calcular la resistencia electrica del termistor usando la lectura del ADC
    uint32_t resistencia = thermistor_get_resistance(analogRead(CONFIG_THERMISTOR_ADC_PIN));
    // luego calcular la temperatura segun dicha resistencia
    float temperatura = thermistor_get_temperature(resistencia);

    sumaTemperaturas += temperatura;
  }

  temperaturaMedia = sumaTemperaturas / numeroMuestras;
  return temperaturaMedia;

  // imprimir resistencia y temperatura al monitor serial
  /*Serial.print(F("Resistencia del NTC: "));
    Serial.print(resistencia);
    Serial.print(" Temperatura: ");
    Serial.println(temperatura, 1);

    // esperar 5 segundos entre las lecturas
    delay(5000);*/


}
