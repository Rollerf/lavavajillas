bool llenado(bool regeneracion) {
  //TODO: Poder detectar filtro sucio con un tiempo o algo
  if (!tMaximoNivelAgua->IN(activar)) {
    if (sensorNivel->switchMode(invertir)) {
      digitalWrite(EV_EntradaAgua, LOW);
      digitalWrite(regeneracionSal, LOW);
      digitalWrite(mRecirculacion, HIGH);

      if (!flagActivoNivel) {
        tMaximoNivelAgua->IN(reset);
        tNivelAgua->IN(reset);
        tActivoNivelAgua->IN(reset);
        return true;
      }
    } else {
      digitalWrite(EV_EntradaAgua, HIGH);

      if (regeneracion) {
        digitalWrite(regeneracionSal, HIGH);
      }
      if (tNivelAgua->IN(activar)) {
        setError(ERROR_NIVEL_AGUA);
        tMaximoNivelAgua->IN(reset);
        tActivoNivelAgua->IN(reset);
        tNivelAgua->IN(reset);

        return false;
      }

      flagActivoNivel = tActivoNivelAgua->IN(activar);
    }

    return false;

  } else {
    setError(ERROR_NIVEL_AGUA);
    tMaximoNivelAgua->IN(reset);
    tNivelAgua->IN(reset);
    tActivoNivelAgua->IN(reset);

    return false;
  }

}

bool vaciado() {

  if (tVaciado->IN(activar)) {
    digitalWrite(bVaciado, LOW);

    if (sensorNivel->switchMode(true)) {
      setError(ERROR_NIVEL_AGUA);

      return false;
    }

    tVaciado->IN(reset);

    return true;
  }

  else {
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
