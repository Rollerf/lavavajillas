bool prgLavado(char programaSeleccionado) {
  unsigned long tiempoRemojado;
  unsigned long tiempoLavado;
  unsigned long tiempoAbrillantado;
  unsigned long tiempoSecado;
  unsigned long tiempoEspera;
  unsigned long tiempoPararCalentarLavado;
  unsigned long tiempoPararCalentarAbrillantado;
  float temperaturaLavado;
  float temperaturaAbrillantado;

  switch (programaSeleccionado) {
    case 'E':
      tiempoRemojado = TIME_REM_PRG_ECO;
      tiempoLavado = TIME_LAV_PRG_ECO;
      tiempoAbrillantado = TIME_ABR_PRG_ECO;
      tiempoSecado = TIME_SEC_PRG_ECO;
      tiempoEspera = TIME_ESP;
      tiempoPararCalentarLavado = TIME_LAV_STOP_HEAT_PRG_ECO;
      tiempoPararCalentarAbrillantado = TIME_ABR_STOP_HEAT_PRG_ECO;
      temperaturaLavado = TEMP_LAV_PRG_ECO;
      temperaturaAbrillantado = TEMP_ABR_PRG_ECO;


      break;

    case 'N':
      tiempoRemojado = TIME_REM_PRG_NORMAL;
      tiempoLavado = TIME_LAV_PRG_NORMAL;
      tiempoAbrillantado = TIME_ABR_PRG_NORMAL;
      tiempoSecado = TIME_SEC_PRG_NORMAL;
      tiempoEspera = TIME_ESP;
      tiempoPararCalentarLavado = TIME_LAV_STOP_HEAT_PRG_NORMAL;
      tiempoPararCalentarAbrillantado = TIME_ABR_STOP_HEAT_PRG_NORMAL;
      temperaturaLavado = TEMP_LAV_PRG_NORMAL;
      temperaturaAbrillantado = TEMP_ABR_PRG_NORMAL;

      break;

    case 'S':
      tiempoRemojado = TIME_REM_PRG_STRONG;
      tiempoLavado = TIME_LAV_PRG_STRONG;
      tiempoAbrillantado = TIME_ABR_PRG_STRONG;
      tiempoSecado = TIME_SEC_PRG_STRONG;
      tiempoEspera = TIME_ESP;
      tiempoPararCalentarLavado = TIME_LAV_STOP_HEAT_PRG_STRONG;
      tiempoPararCalentarAbrillantado = TIME_ABR_STOP_HEAT_PRG_STRONG;
      temperaturaLavado = TEMP_LAV_PRG_STRONG;
      temperaturaAbrillantado = TEMP_ABR_PRG_STRONG;

      break;

    case 'R':
      tiempoRemojado = 0;
      tiempoLavado = TIME_LAV_PRG_RAPIDO;
      tiempoAbrillantado = TIME_ABR_PRG_RAPIDO;
      tiempoSecado = 0;
      tiempoEspera = TIME_ESP;
      tiempoPararCalentarLavado = TIME_LAV_STOP_HEAT_PRG_RAPIDO;
      tiempoPararCalentarAbrillantado = TIME_ABR_STOP_HEAT_PRG_RAPIDO;
      temperaturaLavado = TEMP_LAV_PRG_RAPIDO;
      temperaturaAbrillantado = TEMP_ABR_PRG_RAPIDO;

      break;

    case 'D':
      tiempoRemojado = TIME_REM_PRG_DELICADO;
      tiempoLavado = TIME_LAV_PRG_DELICADO;
      tiempoAbrillantado = TIME_ABR_PRG_DELICADO;
      tiempoSecado = TIME_SEC_PRG_DELICADO;
      tiempoEspera = TIME_ESP;
      tiempoPararCalentarLavado = TIME_LAV_STOP_HEAT_PRG_DELICADO;
      tiempoPararCalentarAbrillantado = TIME_ABR_STOP_HEAT_PRG_DELICADO;
      temperaturaLavado = TEMP_LAV_PRG_DELICADO;
      temperaturaAbrillantado = TEMP_ABR_PRG_DELICADO;

      break;
  }

  switch (etapa) {
    //Condiciones iniciales
    case 0:
      if (condicionesIniciales()) {
        etapa++;
        //etapa = 5;
        //Serial.println("Condiciones iniciales cumplidas");
      }

      return false;

    //Ciclo de remojado
    case 1:
      if (programaSeleccionado == PRG_RAPIDO) {
        etapa = 5;

      } else if (llenado(regeneracionDesactivada)) { //Llenado. Etapa2
        tCiclo->setSetPoint(tiempoRemojado);
        //Serial.println("Llenado completo");
        etapa++;
      }

      return false;

    case 2:
      //Empezar con el primer ciclo. Etapa 2
      //if (remojado()) {
      if (lavado(temperaturaLavado, tiempoPararCalentarLavado)) {
        //Serial.println("Remojado completo");
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
      if (vaciado(regeneracionDesactivada)) {
        etapa++;
        //Serial.println("Vacio");
      }

      return false;

    //Ciclo lavado

    case 5:
      //Llenado. Etapa 5
      if (llenado(regeneracionDesactivada)) {
        tCiclo->setSetPoint(tiempoLavado);

        etapa++;
        //Serial.println("Llenado, segundo ciclo");
      }

      return false;

    case 6:
      //Empezar con el segundo ciclo. Etapa 6
      if (lavado(temperaturaLavado, tiempoPararCalentarLavado)) {
        etapa++;
        tCiclo->setSetPoint(tiempoEspera);
        //Serial.println("Lavado completo");
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
      if (vaciado(regeneracionDesactivada)) {
        etapa++;
        //Serial.println("Vacio");
      }

      return false;

    //Ciclo abrillantado

    case 9:
      //Llenado. Etapa 9
      if (llenado(regeneracionActivada)) {
        tCiclo->setSetPoint(tiempoAbrillantado);

        etapa++;
        //Serial.println("Llenado, tercer ciclo");
      }

      return false;

    case 10:
      //Etapa 10
      if (abrillantado(temperaturaAbrillantado, tiempoPararCalentarAbrillantado)) {
        etapa++;
        tCiclo->setSetPoint(tiempoEspera);
        //Serial.println("Abrillantado completo");
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
      if (vaciado(regeneracionActivada)) {
        etapa++;
        //Serial.println("Vacio");
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
        //Serial.println("Secado completo");
      }

      return false;

    case 15:
      //Vaciado. Etapa 15
      if (vaciado(regeneracionDesactivada)) {
        etapa++;
      }

      return false;

    //Fin del programa
    default:
      etapa = 0;

      return true;
  }
}
