bool eco() {
  switch (etapa) {
    case 0:
      if (condicionesIniciales()) {
        etapa++;
      }

      return false;

    case 1:
      //Llenado. Etapa2
      if (llenado(regeneracionDesactivada)) {
        etapa++;
      }

      return false;

    case 2:
      //Empezar con el primer ciclo. Etapa3
      if (remojado()) {
        etapa++;
      }

      return false;

    case 3:
      //Vaciado. Etapa4
      if (vaciado()) {
        etapa++;
      }

      return false;

    //CICLO 2

    case 4:
      //Llenado. Etapa2
      if (llenado(regeneracionDesactivada)) {
        etapa++;
      }

      return false;

    case 5:
      //Empezar con el segundo ciclo. Etapa3
      if (lavado(programa)) {
        etapa++;
      }

      return false;

    case 6:
      //Vaciado. Etapa4
      if (vaciado()) {
        etapa++;
      }

      return false;

    //CICLO 3

    case 7:
      //Llenado. Etapa 8
      if (programa == 'E') {
        etapa = 11;

        return false;
      }
      if (llenado(regeneracionDesactivada)) {
        etapa++;
      }

      return false;

    case 8:
      //Repetir segundo ciclo. Etapa 9
      if (lavado(programa)) {
        etapa++;
      }

      return false;

    case 9:
      //Vaciado. Etapa 10
      if (vaciado()) {
        etapa++;
      }

      return false;

    //CICLO SECADO

    case 10:
      //Llenado. Etapa 11
      if (llenado(regeneracionActivada)) {
        etapa++;
      }

      return false;

    case 11:
      //Etapa 12
      if (secado(programa)) {
        etapa++;
      }

      return false;

    case 12:
      //Vaciado. Etapa 13
      if (vaciado()) {
        etapa++;
      }

      return false;

    //Fin del programa
    default:
      etapa = 0;

      return true;
  }
}
