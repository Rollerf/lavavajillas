bool llenado(bool regeneracion) {
  //Si se supera el tiempo maximo estimado para un llenado, se para la maquina y da error
  if (!tMaximoNivelAgua->IN(activar)) {
    //Si se activa el sensor de nivel, se para la entrada de agua y se arranca el motor de recirculacion
    if (sensorNivel->switchMode(invertir)) {
      digitalWrite(EV_EntradaAgua, LOW);
      digitalWrite(regeneracionSal, LOW);
      digitalWrite(mRecirculacion, HIGH);

      //Reseteo el temporizador de nivel activo
      tNivelAgua->IN(resetTimer);

      //Se da por finalizado el llenado
      if (tActivoNivelAgua->IN(activar)) {
        tMaximoNivelAgua->IN(resetTimer);
        tActivoNivelAgua->IN(resetTimer);
        //Serial.println("Fin llenado");
        return true;
      }
    } else {
      digitalWrite(EV_EntradaAgua, HIGH);
      tActivoNivelAgua->IN(resetTimer);

      ////Serial.println("Llenando");

      if (regeneracion && !tRegeneracion->IN(activar)) {
        digitalWrite(regeneracionSal, HIGH);
        //Serial.println("Regenerando");
      }
      if (tNivelAgua->IN(activar)) {
        setError(CHAR_ERROR_NIVEL_AGUA);
        tMaximoNivelAgua->IN(resetTimer);
        tActivoNivelAgua->IN(resetTimer);
        tNivelAgua->IN(resetTimer);
        //Serial.println("Error tNivelAgua");

        return false;
      }
    }

    printLine(CICLO_LLENANDO, SEGUNDA_LINEA);

    return false;

  } else {
    if (sensorNivel->switchMode(invertir)) {
      digitalWrite(EV_EntradaAgua, LOW);
      digitalWrite(regeneracionSal, LOW);
      digitalWrite(mRecirculacion, HIGH);

      return true;

    } else {
      setError(CHAR_ERROR_NIVEL_AGUA);
      tMaximoNivelAgua->IN(resetTimer);
      tNivelAgua->IN(resetTimer);
      tActivoNivelAgua->IN(resetTimer);

      return false;
    }
  }
}
//Vacia durante un tiempo.
//Devuelve true pasado ese tiempo si el sensor no detecta nivel de agua
bool vaciado(bool regeneracion) {

  if (tVaciado->IN(activar)) {
    digitalWrite(bVaciado, LOW);
    digitalWrite(regeneracionSal, LOW);

    if (sensorNivel->switchMode(true)) {
      setError(CHAR_ERROR_NIVEL_AGUA);
      setError(CHAR_ERROR_FILTRO_SUCIO);

      return false;
    }

    tVaciado->IN(resetTimer);

    return true;

  } else {
    digitalWrite(EV_EntradaAgua, LOW);
    digitalWrite(bVaciado, HIGH);

    if(regeneracion && tVaciado->getCurrentTime() < TIME_REGENERATION_DRAINING){
      digitalWrite(regeneracionSal, HIGH);
    }else{
      digitalWrite(regeneracionSal, LOW);
    }

    //Serial.println("Vaciando");

    printLine(CICLO_VACIANDO, SEGUNDA_LINEA);

    return false;
  }
}

void parar() {
  digitalWrite(EV_EntradaAgua, LOW);
  digitalWrite(calentador, LOW);
  digitalWrite(mRecirculacion, LOW);
  digitalWrite(bVaciado, LOW);
  digitalWrite(aAbrillantador, LOW);
  digitalWrite(regeneracionSal, LOW);

  //printLine(EST_PARADO, SEGUNDA_LINEA);
}

bool calentar(float temperaturaConsigna) {
  float temperaturaActual = calculoNTC();

  if (temperaturaActual < temperaturaConsigna - TEMP_OFFSET) {
    digitalWrite(mRecirculacion, HIGH);
    digitalWrite(calentador, HIGH);

    String temperaturaImprimir = TEMP_ACTUAL + String(temperaturaActual, 2);

    printLine(temperaturaImprimir, SEGUNDA_LINEA);

    return false;

  } else if (temperaturaActual  > temperaturaConsigna + TEMP_OFFSET) {
    digitalWrite(calentador, LOW);

    return true;
  }
}
