bool prgLavado(char programaSeleccionado) {
  unsigned long tiempoRemojado;
  unsigned long tiempoLavado;
  unsigned long tiempoAbrillantado;
  unsigned long tiempoSecado;
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

      break;

    case 'N':
      tiempoRemojado = TIME_REM_PRG_NORMAL;
      tiempoLavado = TIME_LAV_PRG_NORMAL;
      tiempoAbrillantado = TIME_ABR_PRG_NORMAL;
      tiempoSecado = TIME_SEC_PRG_NORMAL;
      temperaturaLavado = TEMP_LAV_PRG_NORMAL;
      temperaturaAbrillantado = TEMP_ABR_PRG_NORMAL;

      break;

    case 'S':
      tiempoRemojado = TIME_REM_PRG_STRONG;
      tiempoLavado = TIME_LAV_PRG_STRONG;
      tiempoAbrillantado = TIME_ABR_PRG_STRONG;
      tiempoSecado = TIME_SEC_PRG_STRONG;
      temperaturaLavado = TEMP_LAV_PRG_STRONG;
      temperaturaAbrillantado = TEMP_ABR_PRG_STRONG;

      break;

    case 'R':
      tiempoRemojado = 0;
      tiempoLavado = TIME_LAV_PRG_RAPIDO;
      tiempoAbrillantado = TIME_ABR_PRG_RAPIDO;
      tiempoSecado = 0;
      temperaturaLavado = TEMP_LAV_PRG_RAPIDO;
      temperaturaAbrillantado = TEMP_ABR_PRG_RAPIDO;

      break;

    case 'D':
      tiempoRemojado = TIME_REM_PRG_DELICADO;
      tiempoLavado = TIME_LAV_PRG_DELICADO;
      tiempoAbrillantado = TIME_ABR_PRG_DELICADO;
      tiempoSecado = TIME_SEC_PRG_DELICADO;
      temperaturaLavado = TEMP_LAV_PRG_DELICADO;
      temperaturaAbrillantado = TEMP_ABR_PRG_DELICADO;

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
        etapa = 4;

      } else if (llenado(regeneracionDesactivada)) { //Llenado. Etapa2
        tCiclo->setSetPoint(tiempoRemojado);
        Serial.println("Llenado, primer ciclo");

        etapa++;
      }

      return false;

    case 2:
      //Empezar con el primer ciclo. Etapa 2
      if (remojado()) {
        etapa++;
        Serial.println("Remojado completo");
      }

      return false;

    case 3:
      //Vaciado. Etapa 3
      if (vaciado()) {
        //Se modifica para probar hasta aqui
        //etapa++;
        etapa = 10;
        Serial.println("Vacio");
      }

      return false;

    //Ciclo lavado

    case 4:
      //Llenado. Etapa 4
      if (llenado(regeneracionDesactivada)) {
        tCiclo->setSetPoint(tiempoLavado);

        etapa++;
        Serial.println("Llenado, segundo ciclo");
      }

      return false;

    case 5:
      //Empezar con el segundo ciclo. Etapa 5
      if (lavado(temperaturaLavado)) {
        etapa++;
        Serial.println("Lavado completo");
      }

      return false;

    case 6:
      //Vaciado. Etapa 6
      if (vaciado()) {
        etapa++;
        Serial.println("Vacio");
      }

      return false;

    //Ciclo abrillantado

    case 7:
      //Llenado. Etapa 7
      if (llenado(regeneracionDesactivada)) {
        tCiclo->setSetPoint(tiempoAbrillantado);

        etapa++;
        Serial.println("Llenado, tercer ciclo");
      }

      return false;

    case 8:
      //Etapa 8
      if (abrillantado(temperaturaAbrillantado)) {
        etapa++;
        Serial.println("Abrillantado completo");
      }

      return false;

    case 9:
      //Vaciado. Etapa 9
      if (vaciado()) {
        etapa++;
        Serial.println("Vacio");
      }

      return false;

    //Ciclo secado

    case 10:
      if (programaSeleccionado == 'R') {
        etapa = 13;
      } else { // Etapa 10
        tCiclo->setSetPoint(tiempoSecado);

        etapa++;
      }

      return false;

    case 11:
      //Etapa 11
      if (secado()) {
        //tVaciado->setSetPoint(TIME_VACIADO_SECADO);

        etapa++;
        Serial.println("Secado completo");
      }

      return false;

    case 12:
      //Vaciado. Etapa 12
      //      if (vaciado()) {
      //        etapa++;
      //      }

      etapa++;

      return false;

    //Fin del programa
    default:
      etapa = 0;

      return true;
  }
}
