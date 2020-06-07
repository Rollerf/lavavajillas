//Librerias:
#include <Timer.h>
#include <Switches.h>

//Temporizadores
TON* tVaciado;

//Entradas
Switches* sensorNivel;
Switches* pulsadorMarcha;
Switches* interruptorPrograma1;
Switches* interruptorPrograma2;
Switches* sensorFuga;

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
#define alSonora 6

//Variables de proceso
byte contadorNivel;
bool flagContadorNivel;

void setup() {

  //Entradas digitales:
  for (byte i = 0; i <= 12; i++)
    pinMode(i, INPUT_PULLUP);
  pinMode(sPuerta, INPUT);

  //Salidas digitales:
  for (byte i = 2; i <= 6; i++)
    pinMode(i, OUTPUT);

  //Temporizadores:
  tVaciado = new TON(60000);

  //Switches
  sensorNivel = new Switches(50, sNivel);
  pulsadorMarcha = new Switches(50, pMarcha);
  interruptorPrograma1 = new Switches(50, pPrograma1);
  interruptorPrograma2 = new Switches(50, pPrograma2);
  sensorFugas = new Switches(50, sFugas);

  //Comunicacion:
  Serial.begin(9600);

}

void loop() {
  if (pulsadorMarcha->interlockButton(false)) {
    if (check) {
      if (interruptorPrograma1->switchMode()) {
        
      } else if (interruptorPrograma2->switchMode()) {

      }
    }
  }
}
