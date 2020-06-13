//Librerias:
#include <Timer.h>
#include <Switches.h>
#include <Wire.h>  //direcciones I2C display
// comunicacion display mediante I2C. pines:  A4= SDA y A5= SCL
#include <LiquidCrystal_I2C.h>

//Temporizadores
TON* tVaciado;
TON* tDisplayErrores;

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
#define Calentador 3
#define mRecirculacion 4
#define bVaciado 5
#define aAbrillantador 6
#define regeneracionSal 7

//Flujo de programa
bool E0; //Condiciones iniciales
bool E1; //Seleccion del programa
bool E2; //Primer ciclo

//Variables de proceso
byte contadorNivel;
bool flagContadorNivel;
int etapa = 0;

//Errores
byte const erroresLength = 3;
char* errores[erroresLength];

//Constantes
const String errorFugaAgua = "Fuga de agua";
const String errorSensorNivel = "Lavavajillas con nivel de agua";
const String errorTemperatura = "Error de temperatura NTC";

void setup() {

  //Entradas digitales:
  for (byte i = 0; i <= 12; i++)
    pinMode(i, INPUT_PULLUP);
  pinMode(sPuerta, INPUT);

  //Salidas digitales:
  for (byte i = 2; i <= 7; i++)
    pinMode(i, OUTPUT);

  //Temporizadores:
  tVaciado = new TON(60000);
  tDisplayErrores = new TON(1000);

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
  if (pulsadorMarcha->interlockButton(true) && sensorPuerta->switchMode(false)) {
    switch (etapa) {
      case 0:
        if (condicionesIniciales()) {
          etapa++;
        }
        break;

      case 1:
        if (interruptorPrograma1->switchMode(true)) {
          //Setea los ajustes del programa 1 y muestra por pantalla que esta seleccionado
          etapa++;

        } else if (interruptorPrograma2->switchMode(true)) {
          //Setea los ajustes del programa 2 y muestra por pantalla que esta seleccionado
          etapa++;
        }
        break;

      case 2:
        //TODO: Empezar con el primer ciclo. Etapa2
        break;
    }
  } else if (pulsadorMarcha->interlockButton(true) && !sensorPuerta->switchMode(false)) {
    //Parar programa.
    //Cuando se cierre de nuevo la puerta, continuar donde estaba el programa
  } else if (pulsadorMarcha->interlockButton(true)) {
    //Se para todo y se devuelve el programa al E0
  }

  showErrors();
}
