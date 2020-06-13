bool condicionesIniciales() {
  digitalWrite(EV_EntradaAgua, LOW);
  digitalWrite(Calentador, LOW);
  digitalWrite(mRecirculacion, LOW);
  digitalWrite(bVaciado, LOW);
  digitalWrite(Calentador, LOW);
  digitalWrite(mRecirculacion, LOW);

  //Comprobacion nivel de agua
  if (sensorNivel->switchMode(true)) {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(bVaciado, HIGH);
    setError(errorSensorNivel);

    return false;
  } else {
    digitalWrite(bVaciado, LOW);
    clearError(errorSensorNivel);
  }

  //Comprobacion fuga de agua
  if (sensorFugas->switchMode(true)) {
    digitalWrite(EV_EntradaAgua, LOW);
    vaciado();
    setError(errorFugaAgua);

    return false;
  } else {
    digitalWrite(bVaciado, LOW);
    clearError(errorFugaAgua);
  }

  //Comprobacion temperatura
  if (calculoNTC() <= 5 || calculoNTC() >= 35) {
    setError(errorTemperatura);

    return false;
  } else {
    clearError(errorFugaAgua);
  }

  return true;
}
//Checkear sonda de temperatura. Que no tenga error
