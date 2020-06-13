bool vaciado() {

  if (tVaciado->IN(true)) {
    digitalWrite(bVaciado, HIGH);
    return false;
  }

  else {
    digitalWrite(bVaciado, LOW);
    tVaciado->IN(false);
    return true;
  }
}

bool printLine(String texto, byte linea) {
  lcd.setCursor(0, linea);
  lcd.print("                    ");  //borramos la linea
  lcd.print(texto);

  return true;
}
