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
TON* tConfirmarPrograma;
TON* tActivoNivelAgua;
TON* tCiclo;

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
#define pMarcha 9
#define sNivel 10
#define sFugas 11
#define sSal 12
#define sPuerta 8

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
bool finPrograma;
char programa;
int seleccionPrograma = 0;
int etapa = 0;

//Variables de proceso
bool flagActivoNivel;
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
const bool resetTimer = false;
const bool regeneracionActivada = true;
const bool regeneracionDesactivada = false;
const byte PRIMERA_LINEA = 0;
const byte SEGUNDA_LINEA = 1;

//Errores
byte const erroresLength = 3;
char* errores[erroresLength];
bool aparatoError = false;

//Constantes mensajes error
const String ERROR_FUGA_AGUA = "Fuga de agua";
const String ERROR_SENSOR_NIVEL = "Lavavajillas con nivel de agua";
const String ERROR_TEMPERATURA_SONDA = "Error de temperatura NTC";
const String ERROR_NIVEL_AGUA = "Timeout nivel de agua";

//Constantes mensajes proceso
const String PROGRAMA_ECO = "PROGRAMA ECO";
const String PROGRAMA_FINALIZADO = "FIN DEL PROGRAMA";

//Constantes temperatura
const float SEVENTY = 70.0;
const float SIXTY = 60.0;
const float FIFTY = 50.0;
const float FORTY_FIVE = 45.0;

void setup() {
  //Entradas digitales:
  for (byte i = 9; i <= 12; i++)
    pinMode(i, INPUT_PULLUP);
  pinMode(sPuerta, INPUT);

  //Salidas digitales:
  for (byte i = 2; i <= 7; i++)
    pinMode(i, OUTPUT);

  //Temporizadores:
  tVaciado = new TON(40000);
  tDisplayErrores = new TON(1000);
  tNivelAgua = new TON(45000);
  tMaximoNivelAgua = new TON(300000);
  tActivoNivelAgua = new TON(3000);
  tCiclo = new TON(1200000);
  tConfirmarPrograma = new TON(3000);

  //Switches
  sensorNivel = new Switches(50, sNivel);
  pulsadorMarcha = new Switches(50, pMarcha);
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

  if (!marcha && pulsadorMarcha->switchMode(invertir)) {
    while (pulsadorMarcha->switchMode(invertir)) {
      if (tConfirmarPrograma->IN(activar)) {
        marcha = true;
        tConfirmarPrograma->IN(resetTimer);
      }
    }
    if (!marcha) {
      seleccionPrograma++;
    }
  }
  tConfirmarPrograma->IN(resetTimer);

  if (marcha && sensorPuerta->buttonMode(real) && !aparatoError) {
    //TODO: Acabar el resto de programas
    //TODO: Hacer seguridades y acciones de si se abre la puerta
    //TODO: Checkear que estan todos los ciclos
    //TODO: Modificar nombre de constantes por nombres en mayuscula separados con _
    //TODO: Poner falses para poder probar el programa por partes
    switch (seleccionPrograma) {
      case 1:
        finPrograma = eco();
        printLine(PROGRAMA_ECO, PRIMERA_LINEA);
        break;

      case 2:

        break;
    }

    if (finPrograma) {
      marcha = false;
      printLine(PROGRAMA_FINALIZADO, PRIMERA_LINEA);
    }

  } else if (marcha && !sensorPuerta->buttonMode(real)) {
    parar();
    //TODO:Cuando se cierre de nuevo la puerta, continuar donde estaba el programa
    //reiniciando tiempos de ciclos si es que se encuentra en alguno
  }
  //Checkear errores durante todo el programa
  if (tDisplayErrores->IN(activar)) {
    checkSondaTemperatura();
    if (showErrors()) {
      aparatoError = true;
      etapa = 0;
    }
    tDisplayErrores->IN(resetTimer);
  }
}
