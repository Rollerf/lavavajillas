bool remojado() {
  if (tCiclo->IN(activar)) {
    digitalWrite(mRecirculacion, LOW);

    tCiclo->IN(resetTimer);

    return true;

  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(calentador, LOW);
    digitalWrite(mRecirculacion, HIGH);

    printLine(CICLO_REMOJANDO, SEGUNDA_LINEA);

    return false;
  }
}

bool lavado(float temperatura, long tiempoPararCalentarLavado) {
  if (tCiclo->IN(activar)) {
    digitalWrite(calentador, LOW);
    digitalWrite(mRecirculacion, LOW);

    tCiclo->IN(resetTimer);

    return true;

  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(mRecirculacion, HIGH);

    if (tCiclo->getSetPoint() - tCiclo->getCurrentTime() < tiempoPararCalentarLavado) {
      digitalWrite(calentador, LOW);
    } else {
      calentar(temperatura);
    }

    printLine(CICLO_LAVANDO, SEGUNDA_LINEA);

    return false;
  }
}

bool abrillantado(float temperatura, long tiempoPararCalentarAbrillantado) {
  if (tCiclo->IN(activar)) {
    digitalWrite(mRecirculacion, LOW);
    digitalWrite(calentador, LOW);
    digitalWrite(aAbrillantador, LOW);

    tCiclo->IN(resetTimer);

    return true;

  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(mRecirculacion, HIGH);

    if (tCiclo->getSetPoint() - tCiclo->getCurrentTime() < tiempoPararCalentarAbrillantado) {
      digitalWrite(calentador, LOW);
    } else {
      if (calentar(temperatura)) { //Cuando ya cogio temperatura, abro el abrillantador
        digitalWrite(aAbrillantador, HIGH);
      }
    }

    printLine(CICLO_ABRILLANTANDO, SEGUNDA_LINEA);

    return false;
  }
}

bool secado() {
  if (tCiclo->IN(activar)) {
    tCiclo->IN(resetTimer);

    return true;

  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(mRecirculacion, LOW);
    digitalWrite(calentador, LOW);

    printLine(CICLO_SECANDO, SEGUNDA_LINEA);

    return false;
  }
}

bool espera() {
  if (tCiclo->IN(activar)) {
    tCiclo->IN(resetTimer);

    return true;

  } else {

    return false;
  }
}
