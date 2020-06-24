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
    setError(ERROR_SENSOR_NIVEL);

    return false;
  } else {
    digitalWrite(bVaciado, LOW);
    clearError(ERROR_SENSOR_NIVEL);
  }

  //Comprobacion fuga de agua
  if (sensorFugas->switchMode(invertir)) {
    digitalWrite(EV_EntradaAgua, LOW);
    vaciado();
    setError(ERROR_FUGA_AGUA);

    return false;
  } else {
    digitalWrite(bVaciado, LOW);
    clearError(ERROR_FUGA_AGUA);
  }

  //Comprobacion temperatura
  if (calculoNTC() <= 5 || calculoNTC() >= 35) {
    setError(ERROR_TEMPERATURA_SONDA);

    return false;
  } else {
    clearError(ERROR_FUGA_AGUA);
  }

  return true;
}

//Checkear sonda de temperatura. Que no tenga error
bool checkSondaTemperatura() {
  float temperatura = calculoNTC();

  if (temperatura <= 5.0 || temperatura >= 80.0) {
    setError(ERROR_TEMPERATURA_SONDA);

    return false;
  }

  return true;
}
