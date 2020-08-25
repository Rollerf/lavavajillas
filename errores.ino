void setError(char descripcionError) {
  //  //Serial.println(descripcionError);
  for (int i = 0; i < erroresLength; i++) {
    if (descripcionError == errores[i]) {
      return;
    }
  }
  for (int i = 0; i < erroresLength; i++) {
    if (errores[i] == 0) {
      errores[i] = descripcionError;
      char letraError = errores[i];
      //      //Serial.print("Error seteado:");
      //      //Serial.println(letraError);
      break;
    }
  }
}

void clearError(char descripcionError) {
  for (int i = 0; i <= erroresLength; i++) {
    if (descripcionError == errores[i]) {
      char errorBorrado = errores[i];
      //      //Serial.print("Error borrado: ");
      //      //Serial.println(errorBorrado);
      errores[i] = 0;
      break;
    }
  }
}

void clearErrors() {
  for (int i = 0; i < erroresLength; i++) {
    errores[i] = 0;
  }
}

bool showErrors() {
  //TODO:Hacer que de alguna manera vayan rotando y mostrandose todos los errores
  for (int i = 0; i <= erroresLength; i++) {
    char errorMostrar = errores[i];
    //    //Serial.print("Error a mostrar: ");
    //    //Serial.println(errorMostrar);
    if (errores[i] == CHAR_ERROR_FUGA_AGUA) {
      printLine(ERROR_FUGA_AGUA, SEGUNDA_LINEA);

      return true;

    } else if (errores[i] == CHAR_ERROR_SENSOR_NIVEL) {
      printLine(ERROR_SENSOR_NIVEL, SEGUNDA_LINEA);

      return true;

    } else if (errores[i] == CHAR_ERROR_TEMPERATURA_SONDA) {
      printLine(ERROR_TEMPERATURA_SONDA, SEGUNDA_LINEA);

      return true;

    } else if (errores[i] == CHAR_ERROR_NIVEL_AGUA) {
      printLine(ERROR_NIVEL_AGUA, SEGUNDA_LINEA);

      return true;

    }
  }

  return false;
}

bool searchError(char descripcionError) {
  for (int i = 0; i < erroresLength; i++) {
    if (descripcionError == errores[i]) {

      return true;
    }
  }

  return false;
}
