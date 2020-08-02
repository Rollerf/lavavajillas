bool prgLavado(char programaSeleccionado) {
  unsigned long tiempoRemojado;
  unsigned long tiempoLavado;
  unsigned long tiempoAbrillantado;
  unsigned long tiempoSecado;
  unsigned long tiempoEspera;
  float temperaturaLavado;
  float temperaturaAbrillantado;

  switch (programaSeleccionado) {
    case 'E':
      tiempoRemojado = TIME_REM_PRG_ECO;
      tiempoLavado = TIME_LAV_PRG_ECO;
      tiempoAbrillantado = TIME_ABR_PRG_ECO;
      tiempoSecado = TIME_SEC_PRG_ECO;
      temperaturaLavado = TEMP_LAV_PRG_ECO;
      temperaturaAbrillantado = TEMP_ABR_PRG_ECO;
      tiempoEspera = TEMP_ESP;

      break;

    case 'N':
      tiempoRemojado = TIME_REM_PRG_NORMAL;
      tiempoLavado = TIME_LAV_PRG_NORMAL;
      tiempoAbrillantado = TIME_ABR_PRG_NORMAL;
      tiempoSecado = TIME_SEC_PRG_NORMAL;
      temperaturaLavado = TEMP_LAV_PRG_NORMAL;
      temperaturaAbrillantado = TEMP_ABR_PRG_NORMAL;
      tiempoEspera = TEMP_ESP;

      break;

    case 'S':
      tiempoRemojado = TIME_REM_PRG_STRONG;
      tiempoLavado = TIME_LAV_PRG_STRONG;
      tiempoAbrillantado = TIME_ABR_PRG_STRONG;
      tiempoSecado = TIME_SEC_PRG_STRONG;
      temperaturaLavado = TEMP_LAV_PRG_STRONG;
      temperaturaAbrillantado = TEMP_ABR_PRG_STRONG;
      tiempoEspera = TEMP_ESP;

      break;

    case 'R':
      tiempoRemojado = 0;
      tiempoLavado = TIME_LAV_PRG_RAPIDO;
      tiempoAbrillantado = TIME_ABR_PRG_RAPIDO;
      tiempoSecado = 0;
      temperaturaLavado = TEMP_LAV_PRG_RAPIDO;
      temperaturaAbrillantado = TEMP_ABR_PRG_RAPIDO;
      tiempoEspera = TEMP_ESP;

      break;

    case 'D':
      tiempoRemojado = TIME_REM_PRG_DELICADO;
      tiempoLavado = TIME_LAV_PRG_DELICADO;
      tiempoAbrillantado = TIME_ABR_PRG_DELICADO;
      tiempoSecado = TIME_SEC_PRG_DELICADO;
      temperaturaLavado = TEMP_LAV_PRG_DELICADO;
      temperaturaAbrillantado = TEMP_ABR_PRG_DELICADO;
      tiempoEspera = TEMP_ESP;

      break;
  }

  switch (etapa) {
    //Condiciones iniciales
    case 0:
      if (condicionesIniciales()) {
        etapa++;
        Serial.println("Condiciones iniciales cumplidas");
      }

      return false;

    //Ciclo de remojado
    case 1:
      if (programaSeleccionado == PRG_RAPIDO) {
        etapa = 5;

      } else if (llenado(regeneracionDesactivada)) { //Llenado. Etapa2
        tCiclo->setSetPoint(tiempoRemojado);
        Serial.println("Llenado completo");
        etapa++;
      }

      return false;

    case 2:
      //Empezar con el primer ciclo. Etapa 2
      if (remojado()) {
        Serial.println("Remojado completo");
        etapa++;
        tCiclo->setSetPoint(tiempoEspera);
      }

      return false;

    case 3:
      //Espera
      if (espera()) {
        etapa++;
      }

      return false;

    case 4:
      //Vaciado. Etapa 4
      if (vaciado()) {
        etapa++;
        Serial.println("Vacio");
      }

      return false;

    //Ciclo lavado

    case 5:
      //Llenado. Etapa 5
      if (llenado(regeneracionDesactivada)) {
        tCiclo->setSetPoint(tiempoLavado);

        etapa++;
        Serial.println("Llenado, segundo ciclo");
      }

      return false;

    case 6:
      //Empezar con el segundo ciclo. Etapa 6
      if (lavado(temperaturaLavado)) {
        etapa++;
        tCiclo->setSetPoint(tiempoEspera);
        Serial.println("Lavado completo");
      }

      return false;

    case 7:
      //Espera
      if (espera()) {
        etapa++;
      }

      return false;

    case 8:
      //Vaciado. Etapa 8
      if (vaciado()) {
        etapa++;
        Serial.println("Vacio");
      }

      return false;

    //Ciclo abrillantado

    case 9:
      //Llenado. Etapa 9
      if (llenado(regeneracionDesactivada)) {
        tCiclo->setSetPoint(tiempoAbrillantado);

        etapa++;
        Serial.println("Llenado, tercer ciclo");
      }

      return false;

    case 10:
      //Etapa 10
      if (abrillantado(temperaturaAbrillantado)) {
        etapa++;
        tCiclo->setSetPoint(tiempoEspera);
        Serial.println("Abrillantado completo");
      }

      return false;

    case 11:
      //Espera
      if (espera()) {
        etapa++;
      }

      return false;

    case 12:
      //Vaciado. Etapa 12
      if (vaciado()) {
        etapa++;
        Serial.println("Vacio");
      }

      return false;

    //Ciclo secado

    case 13:
      if (programaSeleccionado == PRG_RAPIDO) {
        etapa = 20;
      } else { // Etapa 13
        tCiclo->setSetPoint(tiempoSecado);

        etapa++;
      }

      return false;

    case 14:
      //Etapa 14
      if (secado()) {
        tVaciado->setSetPoint(TIME_VACIADO_SECADO);

        etapa++;
        Serial.println("Secado completo");
      }

      return false;

    case 15:
      //Vaciado. Etapa 15
      if (vaciado()) {
        etapa++;
      }

      return false;

    //Fin del programa
    default:
      etapa = 0;

      return true;
  }
}
