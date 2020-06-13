void ciclo1() {
  if (sensorNivel->switchMode(true) && contadorNivel < 6) {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(mRecirculacion, HIGH);

    if (flagContadorNivel) {
      contadorNivel++;
    }
  } else if (contadorNivel < 6) {
    digitalWrite(EV_EntradaAgua, HIGH);
    flagContadorNivel = true;
  }

  if (contadorNivel >= 6) {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(mRecirculacion, LOW);
  }
}
