//Librerias:
#include <Timer.h>
#include <Switches.h>
#include <Wire.h>  //direcciones I2C display
// comunicacion display mediante I2C. pines:  A4= SDA y A5= SCL
#include <LiquidCrystal_I2C.h>

//Temporizadores
TON* tVaciado;
TON* tDisplayErrores;
TON* tNivelAgua;
TON* tMaximoNivelAgua;
TON* tRemojado;
TON* tLavado;
TON* tSecado;
TON* tConfirmarPrograma;

//Entradas
Switches* sensorNivel;
Switches* pulsadorMarcha;
Switches* interruptorPrograma1;
Switches* interruptorPrograma2;
Switches* sensorFugas;
Switches* sensorPuerta;

//Pantalla
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

//Entradas Digitales
#define pMarcha 7
#define pPrograma1 8
#define pPrograma2 9
#define pResetMemoria 10
#define sNivel 11
#define sFugas 12
#define sPuerta 13

//Entradas analogicas
#define sNTC A0

//Salidas digitales
#define EV_EntradaAgua 2
#define calentador 3
#define mRecirculacion 4
#define bVaciado 5
#define aAbrillantador 6
#define regeneracionSal 7

//Flujo de programa
bool marcha;
char programa;
int seleccionPrograma = 0;
int etapa = 0;

//Variables de proceso
bool flagContadorNivel;
byte contadorNivel;

//Constantes de proceso
const byte maximoLlenados = 6;
const bool caliente = true;
const bool frio = false;
const bool invertir = true;
const bool real = false;
const bool flancoSubida = false;
const bool flancoBajada = true;
const bool activar = true;
const bool reset = false;
const bool regeneracionActivada = true;
const bool regeneracionDesactivada = false;

//Errores
byte const erroresLength = 3;
char* errores[erroresLength];
bool aparatoError = false;

//Constantes Errores
const String errorFugaAgua = "Fuga de agua";
const String errorSensorNivel = "Lavavajillas con nivel de agua";
const String errorTemperatura = "Error de temperatura NTC";
const String errorNivelAgua = "Timeout nivel de agua";

//Constantes temperatura
const float alta = 80.0;
const float media = 70.0;

void setup() {
  //Entradas digitales:
  for (byte i = 0; i <= 12; i++)
    pinMode(i, INPUT_PULLUP);
  pinMode(sPuerta, INPUT);

  //Salidas digitales:
  for (byte i = 2; i <= 7; i++)
    pinMode(i, OUTPUT);

  //Temporizadores:
  tVaciado = new TON(40000);
  tDisplayErrores = new TON(1000);
  tNivelAgua = new TON(45000);
  tMaximoNivelAgua = new TON(45000);
  tRemojado = new TON(1200000);
  tLavado = new TON(1200000);
  tSecado = new TON(1200000);
  tConfirmarPrograma = new TON(3000);

  //Switches
  sensorNivel = new Switches(50, sNivel);
  pulsadorMarcha = new Switches(50, pMarcha);
  interruptorPrograma1 = new Switches(50, pPrograma1);
  interruptorPrograma2 = new Switches(50, pPrograma2);
  sensorFugas = new Switches(50, sFugas);
  sensorPuerta = new Switches(50, sPuerta);

  //Comunicacion:
  Serial.begin(9600);

  //Pantalla:
  lcd.init();
  lcd.backlight(); //lcd.noBacklight();
  lcd.home();
  lcd.print("LAVAVAJILLAS FAGOR");
}

void loop() {

  if (pulsadorMarcha->switchMode(invertir)) {
    //TODO: recorrer menu y confirmar por duracion de pulsador
    while (pulsadorMarcha->switchMode(invertir)) {
      if (tConfirmarPrograma->IN(activar)) {
        marcha = true;
        tConfirmarPrograma->IN(reset);
      }
    }
    if(!marcha){
      seleccionPrograma++;
    }
  }
  tConfirmarPrograma->IN(reset);

  while(marcha){
    switch(seleccionPrograma){
      case 1:

      break;

      case 2:

      break;
    }
  }

  if (pulsadorMarcha->interlockButton(flancoBajada) && sensorPuerta->switchMode(real) && !aparatoError) {
    switch (etapa) {
      case 0:
        if (condicionesIniciales()) {
          etapa++;
        }

        break;

      case 1:
        if (interruptorPrograma1->switchMode(invertir)) {
          //Setea los ajustes del programa 1 y muestra por pantalla que esta seleccionado
          programa = 'E';
          etapa++;

        } else if (interruptorPrograma2->switchMode(invertir)) {
          //Setea los ajustes del programa 2 y muestra por pantalla que esta seleccionado
          programa = 'N';
          etapa++;
        }

        break;

      //CICLO 1

      case 2:
        //Llenado. Etapa2
        //        if (llenado(frio, programa)) {
        if (llenado(regeneracionDesactivada)) {
          etapa++;
        }

        break;

      case 3:
        //Empezar con el primer ciclo. Etapa3
        if (remojado()) {
          etapa++;
        }

        break;

      case 4:
        //Vaciado. Etapa4
        if (vaciado()) {
          etapa++;
        }

        break;

      //CICLO 2

      case 5:
        //Llenado. Etapa2
        //        if (llenado(frio, programa)) {
        if (llenado(regeneracionDesactivada)) {
          etapa++;
        }

        break;

      case 6:
        //Empezar con el segundo ciclo. Etapa3
        //TODO: Si el programa es el 'E' (econmomico) este lavado dura mas tiempo
        if (lavado(programa)) {
          etapa++;
        }

        break;

      case 7:
        //Vaciado. Etapa4
        if (vaciado()) {
          etapa++;
        }

        break;

      //CICLO 3

      case 8:
        //Llenado. Etapa 8
        //        if (llenado(frio, programa)) {
        if (programa == 'E') {
          etapa = 11;

          break;
        }
        if (llenado(regeneracionDesactivada)) {
          etapa++;
        }

        break;

      case 9:
        //Repetir segundo ciclo. Etapa 9
        if (lavado(programa)) {
          etapa++;
        }

        break;

      case 10:
        //Vaciado. Etapa 10
        if (vaciado()) {
          etapa++;
        }

        break;

      //CICLO SECADO

      case 11:
        //Llenado. Etapa 11
        //        if (llenado(frio, programa)) {
        if (llenado(regeneracionActivada)) {
          etapa++;
        }

        break;

      case 12:
        //Etapa 12
        if (secado(programa)) {
          etapa++;
        }

        break;

      case 13:
        //Vaciado. Etapa 13
        if (vaciado()) {
          etapa++;
        }

        break;
    }
  } else if (pulsadorMarcha->interlockButton(flancoBajada) && !sensorPuerta->switchMode(real)) {
    parar();
    //TODO:Cuando se cierre de nuevo la puerta, continuar donde estaba el programa
    //reiniciando tiempos de ciclos si es que se encuentra en alguno
  } else if (pulsadorMarcha->interlockButton(flancoBajada)) {
    //Se para todo y se devuelve el programa al E0
    if (condicionesIniciales()) {
      etapa = 0;
    }
  } else if (!pulsadorMarcha->interlockButton(flancoBajada)) {
    //Al apagar el aparato se resetean los errores
    aparatoError = false;
  }
  //Checkear errores durante todo el programa
  if (tDisplayErrores->IN(activar)) {
    checkSondaTemperatura();
    if (showErrors()) {
      aparatoError = true;
      etapa = 0;
    }
    tDisplayErrores->IN(reset);
  }
}
