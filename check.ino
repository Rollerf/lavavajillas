bool condicionesIniciales() {
  static bool lleno;

  digitalWrite(EV_EntradaAgua, LOW);
  digitalWrite(calentador, LOW);
  digitalWrite(mRecirculacion, LOW);
  digitalWrite(aAbrillantador, LOW);
  digitalWrite(regeneracionSal, LOW);

  //Comprobacion nivel de agua
  if (sensorNivel->switchMode(invertir)) {
    digitalWrite(EV_EntradaAgua, LOW);
    //Serial.println("Error, nivel de agua alto");
    setError(CHAR_ERROR_SENSOR_NIVEL);
    setError(CHAR_ERROR_FILTRO_SUCIO);
    lleno = !vaciado(regeneracionDesactivada);

    return false;

  } else if (lleno) {
    lleno = !vaciado(regeneracionDesactivada);

    return !lleno;

  } else {
    clearError(CHAR_ERROR_SENSOR_NIVEL);
    clearError(CHAR_ERROR_FILTRO_SUCIO);
  }

  //Comprobacion fuga de agua
  if (sensorFugas->switchMode(real)) {
    digitalWrite(EV_EntradaAgua, LOW);
    vaciado(regeneracionDesactivada);
    //Serial.println("Error, fuga de agua");
    setError(CHAR_ERROR_FUGA_AGUA);

    return false;

  } else {
    digitalWrite(bVaciado, LOW);
    clearError(CHAR_ERROR_FUGA_AGUA);
  }

  //Comprobacion temperatura
  float temperatura = calculoNTC();

  if (temperatura <= 5 || temperatura >= 55) {
    //Serial.println("Seteo error temperatura sonda");
    //Serial.println("Temperatura: ");
    //Serial.println(temperatura);
    setError(CHAR_ERROR_TEMPERATURA_SONDA);

    return false;

  } else {
    clearError(CHAR_ERROR_FUGA_AGUA);
  }

  return true;
}

//Checkear sonda de temperatura. Que no tenga error
bool checkSondaTemperatura() {
  float temperatura = calculoNTC();
  //Serial.print("checkTemperatura:");
  //Serial.println(temperatura);
  if (temperatura <= 5.0 || temperatura >= 80.0) {
    setError(CHAR_ERROR_TEMPERATURA_SONDA);
    //Serial.println("Seteo error temperatura sonda");

    return false;
  }

  return true;
}

bool checkFugas() {
  //Comprobacion fuga de agua
  static bool vacio;
  if (sensorFugas->switchMode(real) && !vacio) {
    digitalWrite(EV_EntradaAgua, LOW);
    vacio = vaciado(regeneracionDesactivada);
    //Serial.println("Error, fuga de agua");
    setError(CHAR_ERROR_FUGA_AGUA);

    return true;

  } else if (sensorFugas->switchMode(real) && vacio) {

    return true;

  } else {

    return false;
  }
}

bool checkNivelSal() {
  if (sensorSal->switchMode(invertir)) {
    printLine(ERROR_NIVEL_SAL, PRIMERA_LINEA);

    return false;
  }

  return true;
}
