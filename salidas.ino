bool printLine(String texto, byte linea) {
  lcd.setCursor(0, linea);
  lcd.print("                    ");  //borramos la linea
  lcd.print(texto);

  return true;
}

void calentar(float temperaturaConsigna) {
  if (calculoNTC() < temperaturaConsigna) {
    digitalWrite(calentador, HIGH);
  } else {
    digitalWrite(calentador, LOW);
  }
}
