bool printLine(String texto, byte linea) {
  static String lastTextL1;
  static String lastTextL2;

  if (linea == 0) {
    if (texto.equals(lastTextL1)) {

      return false;
    }
  } else if (linea == 1) {
    if (texto.equals(lastTextL2)) {

      return false;
    }
  }
  if (tRefrescoDisplay->IN(activar)) {
    Serial.println("Imprimir display");
    Serial.println(texto);
    Serial.println(lastTextL1);
    Serial.println(lastTextL2);

    lcd.setCursor(0, linea);
    lcd.print(LINEA_VACIA);
    lcd.setCursor(0, linea);
    lcd.print(texto);

    if (linea == 0) {
      lastTextL1 = texto;
    } else if (linea == 1) {
      lastTextL2 = texto;
      Serial.println("Nuevo texto linea 2");
    }
    tRefrescoDisplay->IN(resetTimer);
  }

  return true;
}

void resetTimers() {
  tVaciado->IN(resetTimer);
  tNivelAgua->IN(resetTimer);
  tMaximoNivelAgua->IN(resetTimer);
  tActivoNivelAgua->IN(resetTimer);
  tCiclo->IN(resetTimer);
  tRegeneracion->IN(resetTimer);
}
