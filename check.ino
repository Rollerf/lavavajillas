bool condicionesIniciales() {
  digitalWrite(EV_EntradaAgua, LOW);
  digitalWrite(calentador, LOW);
  digitalWrite(mRecirculacion, LOW);
  digitalWrite(aAbrillantador, LOW);
  digitalWrite(regeneracionSal, LOW);

  //Comprobacion nivel de agua
  if (sensorNivel->switchMode(invertir)) {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(bVaciado, HIGH);
    Serial.println("Error, nivel de agua alto");
    setError(CHAR_ERROR_SENSOR_NIVEL);

    return false;
  } else {
    digitalWrite(bVaciado, LOW);
    clearError(CHAR_ERROR_SENSOR_NIVEL);
  }

  //Comprobacion fuga de agua
  if (sensorFugas->switchMode(real)) {
    digitalWrite(EV_EntradaAgua, LOW);
    vaciado();
    Serial.println("Error, fuga de agua");
    setError(CHAR_ERROR_FUGA_AGUA);

    return false;
  } else {
    digitalWrite(bVaciado, LOW);
    clearError(CHAR_ERROR_FUGA_AGUA);
  }

  //Comprobacion temperatura
  if (calculoNTC() <= 5 || calculoNTC() >= 40) {
    Serial.println("Seteo erro temperatura sonda");
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
  Serial.print("Temperatura:");
  Serial.println(temperatura);
  if (temperatura <= 5.0 || temperatura >= 80.0) {
    setError(CHAR_ERROR_TEMPERATURA_SONDA);
    Serial.println("Seteo error temperatura sonda");
    return false;
  }

  return true;
}

bool checkFugas() {
  //Comprobacion fuga de agua
  static bool vacio;
  if (sensorFugas->switchMode(real) && !vacio) {
    digitalWrite(EV_EntradaAgua, LOW);
    vacio = vaciado();
    Serial.println("Error, fuga de agua");
    setError(CHAR_ERROR_FUGA_AGUA);

    return true;

  } else if (sensorFugas->switchMode(real) && vacio) {

    return true;

  } else {

    return false;
  }
}

bool checkNivelSal(){
  if(sensorSal->switchMode(invertir)){
    printLine(FALTA_SAL, PRIMERA_LINEA);
    
    return false;
  }

  return true;
}
