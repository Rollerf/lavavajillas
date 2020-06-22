bool llenado(bool regeneracion) {
  //TODO: Poder detectar filtro sucio con un tiempo o algo
  //TODO: Resetear temporizador seguridad de llenado
  //TODO: Cambiar el numero de intentos de llenado por que cuando solo llene durante 2s lo de por lleno.
  if (!tMaximoNivelAgua->IN(activar)) {
    if (sensorNivel->switchMode(invertir) && contadorNivel < maximoLlenados) {
      digitalWrite(EV_EntradaAgua, LOW);
      digitalWrite(regeneracionSal, LOW);
      digitalWrite(mRecirculacion, HIGH);

      if (flagContadorNivel) {
        contadorNivel++;
        flagContadorNivel = false;
      }
    } else if (contadorNivel < maximoLlenados) {
      digitalWrite(EV_EntradaAgua, HIGH);
      if (regeneracion) {
        digitalWrite(regeneracionSal, HIGH);
      }
      flagContadorNivel = true;
      if (tNivelAgua->IN(activar)) {
        setError(errorNivelAgua);
        tNivelAgua->IN(reset);
      }
    }

    if (contadorNivel == maximoLlenados) {
      digitalWrite(EV_EntradaAgua, LOW);
      digitalWrite(regeneracionSal, LOW);
      digitalWrite(mRecirculacion, HIGH);

      return true;
    }

    return false;

  } else {
    setError(errorNivelAgua);
    tMaximoNivelAgua->IN(reset);

    return false;
  }

}

bool vaciado() {

  if (tVaciado->IN(activar)) {
    digitalWrite(bVaciado, LOW);

    if (sensorNivel->switchMode(true)) {
      setError(errorNivelAgua);

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
