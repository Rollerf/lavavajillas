bool eco() {
  switch (etapa) {
    case 0:
      if (condicionesIniciales()) {
        etapa++;
      }

      break;

    case 1:
      //Llenado. Etapa2
      //        if (llenado(frio, programa)) {
      if (llenado(regeneracionDesactivada)) {
        etapa++;
      }

      break;

    case 2:
      //Empezar con el primer ciclo. Etapa3
      if (remojado()) {
        etapa++;
      }

      break;

    case 3:
      //Vaciado. Etapa4
      if (vaciado()) {
        etapa++;
      }

      break;

    //CICLO 2

    case 4:
      //Llenado. Etapa2
      if (llenado(regeneracionDesactivada)) {
        etapa++;
      }

      break;

    case 5:
      //Empezar con el segundo ciclo. Etapa3
      //TODO: Si el programa es el 'E' (econmomico) este lavado dura mas tiempo
      if (lavado(programa)) {
        etapa++;
      }

      break;

    case 6:
      //Vaciado. Etapa4
      if (vaciado()) {
        etapa++;
      }

      break;

    //CICLO 3

    case 7:
      //Llenado. Etapa 8
      //        if (llenado(frio, programa)) {
      if (programa == 'E') {
        etapa = 11;

        break;
      }
      if (llenado(regeneracionDesactivada)) {
        etapa++;
      }

      break;

    case 8:
      //Repetir segundo ciclo. Etapa 9
      if (lavado(programa)) {
        etapa++;
      }

      break;

    case 9:
      //Vaciado. Etapa 10
      if (vaciado()) {
        etapa++;
      }

      break;

    //CICLO SECADO

    case 10:
      //Llenado. Etapa 11
      //        if (llenado(frio, programa)) {
      if (llenado(regeneracionActivada)) {
        etapa++;
      }

      break;

    case 11:
      //Etapa 12
      if (secado(programa)) {
        etapa++;
      }

      break;

    case 12:
      //Vaciado. Etapa 13
      if (vaciado()) {
        etapa++;
      }

      break;

    //Fin del programa
    default:
      etapa = 0;

      return true;
  }
}
