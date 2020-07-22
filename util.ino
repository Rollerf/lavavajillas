bool printLine(String texto, byte linea) {
  static String textoAnterior;

  if (!texto.equals(textoAnterior)) {
    lcd.clear();
    lcd.setCursor(0, linea);
    lcd.print(texto);
    textoAnterior = texto;
  }

  return true;
}

void calentar(float temperaturaConsigna) {
  if (calculoNTC() < temperaturaConsigna) {
    digitalWrite(calentador, HIGH);
  } else {
    digitalWrite(calentador, LOW);
  }
}

void resetTimers() {
  tVaciado->IN(resetTimer);
  tDisplayErrores->IN(resetTimer);
  tNivelAgua->IN(resetTimer);
  tMaximoNivelAgua->IN(resetTimer);
  tActivoNivelAgua->IN(resetTimer);
  tCiclo->IN(resetTimer);
  tConfirmarPrograma->IN(resetTimer);
}
