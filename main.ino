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
TON* tRefrescoDisplay;
TON* tRegeneracion;

//Entradas
Switches* sensorNivel;
Switches* pulsadorMarcha;
Switches* sensorFugas;
Switches* sensorPuerta;
Switches* sensorSal;

//Pantalla
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

//Entradas digitales
#define pMarcha 8
#define sPuerta 9
#define sNivel 10
#define sFugas 11
#define sSal 12

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
const String LINEA_VACIA = "                ";

//Errores
byte const erroresLength = 3;
char* errores[] = {0, 0, 0, 0};
bool aparatoError = false;

const char CHAR_ERROR_FUGA_AGUA = 'A';
const char CHAR_ERROR_SENSOR_NIVEL = 'B';
const char CHAR_ERROR_TEMPERATURA_SONDA = 'C';
const char CHAR_ERROR_NIVEL_AGUA = 'D';

//Constantes mensajes error
//OJO:No pueden tener mas de 16 caracteres
const String ERROR_FUGA_AGUA = "Fuga de agua";
const String ERROR_SENSOR_NIVEL = "Nivel agua ALTO";
const String ERROR_TEMPERATURA_SONDA = "Error NTC";
const String ERROR_NIVEL_AGUA = "Timeout llenado";

//Constantes mensajes proceso
const String PROGRAMA_ECO = "PRG ECO";
const String PROGRAMA_NORMAL = "PRG NORMAL";
const String PROGRAMA_STRONG = "PRG STRONG";
const String PROGRAMA_RAPIDO = "PRG RAPIDO";
const String PROGRAMA_DELICADO = "PRG DELICADO";
const String PROGRAMA_ESPERA = "ESPERA PRG";
const String PROGRAMA_FINALIZADO = "FIN PROGRAMA";
const String TEMP_ACTUAL = "Temperatura: ";
const String FALTA_SAL = "Falta Sal";
const String CICLO_LLENANDO = "LLENANDO";
const String CICLO_VACIANDO = "VACIANDO";
const String CICLO_REMOJANDO = "REMOJANDO";
const String CICLO_LAVANDO = "LAVANDO";
const String CICLO_ABRILLANTANDO = "ABRILLANTANDO";
const String CICLO_SECANDO = "SECANDO";
const String EST_PARADO = "PARADO";

String lastTextL1;
String lastTextL2;

//Constantes temperatura
const float TEMP_LAV_PRG_NORMAL = 55.0;
const float TEMP_LAV_PRG_ECO = 50.0;
const float TEMP_LAV_PRG_STRONG = 60.0;
const float TEMP_LAV_PRG_RAPIDO = 45.0;
const float TEMP_LAV_PRG_DELICADO = 45.0;
const float TEMP_ABR_PRG_NORMAL = 65.0;
const float TEMP_ABR_PRG_ECO = 50.0;
const float TEMP_ABR_PRG_STRONG = 70.0;
const float TEMP_ABR_PRG_RAPIDO = 60.0;
const float TEMP_ABR_PRG_DELICADO = 55.0;
const float TEMP_OFFSET = 2.5;

//Constantes tiempos
const long TIME_REM_PRG_NORMAL = 420000; //7min
const long TIME_REM_PRG_ECO = 600000; //10min
const long TIME_REM_PRG_STRONG = 420000; //7min
const long TIME_REM_PRG_DELICADO = 480000; //8min
const long TIME_LAV_PRG_NORMAL = 1200000; //20min
const long TIME_LAV_PRG_ECO = 2100000;//35min //2700000; //45min
const long TIME_LAV_PRG_STRONG = 1200000; //20min
const long TIME_LAV_PRG_RAPIDO = 600000; //10min
const long TIME_LAV_PRG_DELICADO = 1200000; //20min
const long TIME_ABR_PRG_NORMAL = 900000;//15min
const long TIME_ABR_PRG_ECO = 1200000;//20min
const long TIME_ABR_PRG_STRONG = 900000;//15min
const long TIME_ABR_PRG_RAPIDO = 900000;//15min
const long TIME_ABR_PRG_DELICADO = 1200000;//20min
const long TIME_SEC_PRG_NORMAL = 1200000;//20min
const long TIME_SEC_PRG_ECO = 1200000;//20min
const long TIME_SEC_PRG_STRONG = 1200000;//20min
const long TIME_SEC_PRG_DELICADO = 1200000;//20min
const long TIME_VACIADO_SECADO = 10000;//10s
const long TIME_LAV_STOP_HEAT = 600000; //10min
const long TIME_ABR_STOP_HEAT = 300000; //5min
const long TIME_ESP = 300000; //5min

//Constantes programas
const char PRG_ECO = 'E';
const char PRG_NORMAL = 'N';
const char PRG_STRONG = 'S';
const char PRG_RAPIDO = 'R';

void setup() {
  //Entradas digitales:
  for (byte i = 10; i <= 12; i++)
    pinMode(i, INPUT_PULLUP);
  pinMode(pMarcha, INPUT_PULLUP);
  pinMode(sPuerta, INPUT);

  //Salidas digitales:
  for (byte i = 2; i <= 7; i++)
    pinMode(i, OUTPUT);

  parar();

  //Temporizadores:
  tVaciado = new TON(30000);
  tDisplayErrores = new TON(3000);
  tNivelAgua = new TON(60000);
  tMaximoNivelAgua = new TON(600000);
  tActivoNivelAgua = new TON(45000);
  tCiclo = new TON(1200000);
  tConfirmarPrograma = new TON(2000);
  tRefrescoDisplay = new TON(1000);
  tRegeneracion = new TON(10000);

  //Switches
  sensorNivel = new Switches(500, sNivel);
  pulsadorMarcha = new Switches(50, pMarcha);
  sensorFugas = new Switches(50, sFugas);
  sensorPuerta = new Switches(50, sPuerta);
  sensorSal = new Switches(50, sSal);

  //Comunicacion:
  Serial.begin(9600);

  //Pantalla:
  lcd.init();
  lcd.backlight(); //lcd.noBacklight();
  lcd.home();
  lcd.print("FAGOR");
  while (!Serial);
  clearErrors();

  checkNivelSal();

  while(!condicionesIniciales());
}

void loop() {
  if (!marcha && condicionesIniciales() && pulsadorMarcha->buttonMode(invertir) && !aparatoError) {
    while (pulsadorMarcha->buttonMode(invertir)) {
      if (tConfirmarPrograma->IN(activar)) {
        marcha = true;
        tConfirmarPrograma->IN(resetTimer);
        Serial.println("Confirmando programa");
      }
    }
    if (!marcha) {
      seleccionPrograma++;
      Serial.println("Seleccionar programa");
    }
  }
  tConfirmarPrograma->IN(resetTimer);

  switch (seleccionPrograma) {
    case 1:
      printLine(PROGRAMA_ECO, PRIMERA_LINEA);
      break;
    case 2:
      printLine(PROGRAMA_NORMAL, PRIMERA_LINEA);
      break;
    default:
      printLine(PROGRAMA_ESPERA, PRIMERA_LINEA);
      seleccionPrograma = 0;
      break;
  }

  if (marcha && sensorPuerta->switchMode(real) && !aparatoError) {
    switch (seleccionPrograma) {
      case 1:
        finPrograma = prgLavado(PRG_ECO);
        break;

      case 2:

        break;
    }

  } else if (marcha && !sensorPuerta->switchMode(real)) {
    parar();
    resetTimers();
  }

  if (finPrograma) {
    marcha = false;
    printLine(PROGRAMA_FINALIZADO, SEGUNDA_LINEA);
  }

  //Checkear errores durante todo el programa
  if (tDisplayErrores->IN(activar)) {
    checkSondaTemperatura();
    checkFugas();
    //checkNivelSal();

    if (showErrors()) {
      Serial.println("Hay errores");
      parar();
      aparatoError = true;
      etapa = 0;
    } else {
      aparatoError = false;
    }

    tDisplayErrores->IN(resetTimer);
  }
}
