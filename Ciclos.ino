bool remojado() {
  if (tRemojado->IN(activar)) {
    digitalWrite(mRecirculacion, LOW);
    tRemojado->IN(reset);

    return false;
  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(calentador, LOW);
    digitalWrite(mRecirculacion, HIGH);

    return false;
  }
}

bool lavado(char programa) {
  if (tLavado->IN(activar)) {
    digitalWrite(mRecirculacion, LOW);
    tLavado->IN(reset);

    return false;
  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(mRecirculacion, HIGH);

    if (programa == 'E') {
      calentar(media);
    } else if (programa == 'N') {
      calentar(alta);
    }

    return false;
  }
}

bool secado(char programa) {
  if (tSecado->IN(activar)) {
    digitalWrite(mRecirculacion, LOW);
    digitalWrite(aAbrillantador, LOW);
    tSecado->IN(reset);

    return false;
  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(mRecirculacion, HIGH);
    digitalWrite(aAbrillantador, HIGH);

    if (programa == 'E') {
      calentar(media);
    } else if (programa == 'N') {
      calentar(alta);
    }

    return false;
  }
}
