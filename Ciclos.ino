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

bool lavado(float temperatura) {
  if (tCiclo->IN(activar)) {
    digitalWrite(calentador, LOW);
    digitalWrite(mRecirculacion, LOW);

    tCiclo->IN(resetTimer);

    return true;

  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(mRecirculacion, HIGH);

    calentar(temperatura);

    printLine(CICLO_LAVANDO, SEGUNDA_LINEA);

    return false;
  }
}

bool abrillantado(float temperatura) {
  if (tCiclo->IN(activar)) {
    digitalWrite(mRecirculacion, LOW);
    digitalWrite(calentador, LOW);
    digitalWrite(aAbrillantador, LOW);

    tCiclo->IN(resetTimer);

    return true;

  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(mRecirculacion, HIGH);
    digitalWrite(aAbrillantador, HIGH);

    calentar(temperatura);

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
