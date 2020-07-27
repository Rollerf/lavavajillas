bool llenado(bool regeneracion) {
  //TODO: Poder detectar filtro sucio con un tiempo o algo
  if (!tMaximoNivelAgua->IN(activar)) {
    if (sensorNivel->switchMode(invertir)) {
      digitalWrite(EV_EntradaAgua, LOW);
      digitalWrite(regeneracionSal, LOW);
      digitalWrite(mRecirculacion, HIGH);

      tActivoNivelAgua->IN(resetTimer);

      Serial.println("Lleno");

      if (!flagActivoNivel) {
        tMaximoNivelAgua->IN(resetTimer);
        tNivelAgua->IN(resetTimer);
        tActivoNivelAgua->IN(resetTimer);
        Serial.println("Fin llenado");
        return true;
      }
    } else {
      digitalWrite(EV_EntradaAgua, HIGH);

      Serial.println("Llenando");

      if (regeneracion) {
        digitalWrite(regeneracionSal, HIGH);
        Serial.println("Regenerando");
      }
      if (tNivelAgua->IN(activar)) {
        setError(CHAR_ERROR_NIVEL_AGUA);
        tMaximoNivelAgua->IN(resetTimer);
        tActivoNivelAgua->IN(resetTimer);
        tNivelAgua->IN(resetTimer);
        Serial.println(ERROR_NIVEL_AGUA);

        return false;
      }

      flagActivoNivel = tActivoNivelAgua->IN(activar);
    }

    printLine(CICLO_LLENANDO, SEGUNDA_LINEA);

    return false;

  } else {
    setError(CHAR_ERROR_NIVEL_AGUA);
    tMaximoNivelAgua->IN(resetTimer);
    tNivelAgua->IN(resetTimer);
    tActivoNivelAgua->IN(resetTimer);

    return false;
  }

}
//Vacia durante un tiempo.
//Devuelve true pasado ese tiempo si el sensor no detecta nivel de agua
bool vaciado() {

  if (tVaciado->IN(activar)) {
    digitalWrite(bVaciado, LOW);

    if (sensorNivel->switchMode(true)) {
      setError(CHAR_ERROR_NIVEL_AGUA);

      return false;
    }

    tVaciado->IN(resetTimer);

    return true;
    
  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(bVaciado, HIGH);

    printLine(CICLO_VACIANDO, SEGUNDA_LINEA);
    
    return false;
  }
}

void parar() {
  digitalWrite(EV_EntradaAgua, LOW);
  digitalWrite(calentador, LOW);
  digitalWrite(mRecirculacion, LOW);
  digitalWrite(bVaciado, LOW);
  digitalWrite(aAbrillantador, LOW);
  digitalWrite(regeneracionSal, LOW);

  printLine(EST_PARADO, SEGUNDA_LINEA);
}

void calentar(float temperaturaConsigna) {
  float temperaturaActual = calculoNTC();
  Serial.println("Calentando");
  if (temperaturaActual < temperaturaConsigna - TEMP_OFFSET) {
    digitalWrite(mRecirculacion, HIGH);
    digitalWrite(calentador, HIGH);

    String temperaturaImprimir = TEMP_ACTUAL + String(temperaturaActual, 2);

    printLine(temperaturaImprimir, SEGUNDA_LINEA);
  } else if (temperaturaActual  > temperaturaConsigna + TEMP_OFFSET) {
    digitalWrite(calentador, LOW);
  }
}
