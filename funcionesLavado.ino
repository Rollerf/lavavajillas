bool llenado(bool regeneracion) {
  //TODO: Poder detectar filtro sucio con un tiempo o algo
  if (!tMaximoNivelAgua->IN(activar)) {
    if (sensorNivel->switchMode(invertir)) {
      digitalWrite(EV_EntradaAgua, LOW);
      digitalWrite(regeneracionSal, LOW);
      digitalWrite(mRecirculacion, HIGH);

      if (!flagActivoNivel) {
        tMaximoNivelAgua->IN(resetTimer);
        tNivelAgua->IN(resetTimer);
        tActivoNivelAgua->IN(resetTimer);
        return true;
      }
    } else {
      digitalWrite(EV_EntradaAgua, HIGH);

      if (regeneracion) {
        digitalWrite(regeneracionSal, HIGH);
      }
      if (tNivelAgua->IN(activar)) {
        setError(CHAR_ERROR_NIVEL_AGUA);
        tMaximoNivelAgua->IN(resetTimer);
        tActivoNivelAgua->IN(resetTimer);
        tNivelAgua->IN(resetTimer);

        return false;
      }

      flagActivoNivel = tActivoNivelAgua->IN(activar);
    }

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
  }

  else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(bVaciado, HIGH);

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
}
