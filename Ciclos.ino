bool remojado() {
  if (tCiclo->IN(activar)) {
    digitalWrite(mRecirculacion, LOW);
    tCiclo->IN(resetTimer);

    return false;
  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(calentador, LOW);
    digitalWrite(mRecirculacion, HIGH);

    return false;
  }
}

bool lavado(float temperatura) {
  if (tCiclo->IN(activar)) {
    digitalWrite(mRecirculacion, LOW);
    tCiclo->IN(resetTimer);

    return false;
  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(mRecirculacion, HIGH);
    calentar(temperatura);

    return false;
  }
}

bool abrillantado(float temperatura) {
  if (tCiclo->IN(activar)) {
    digitalWrite(mRecirculacion, LOW);
    digitalWrite(aAbrillantador, LOW);
    tCiclo->IN(resetTimer);

    return false;
  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(mRecirculacion, HIGH);
    digitalWrite(aAbrillantador, HIGH);
    calentar(temperatura);

    return false;
  }
}

bool secado(float temperatura) {
  if (tCiclo->IN(activar)) {
    digitalWrite(mRecirculacion, LOW);
    tCiclo->IN(resetTimer);

    return false;
  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(mRecirculacion, HIGH);
    calentar(temperatura);

    return false;
  }
}
