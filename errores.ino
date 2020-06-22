void setError(String descripcionError) {
  char str_array[descripcionError.length()];
  descripcionError.toCharArray(str_array, descripcionError.length());
  for (int i = 0; i < erroresLength; i++) {
    if (descripcionError.compareTo(errores[i])) {
      errores[i] = "";
      return;
    }
  }
  for (int i = 0; i < erroresLength; i++) {
    if (errores[i] == "") {
      errores[i] = str_array;
      break;
    }
  }
}

void clearError(String descripcionError) {
  for (int i = 0; i < erroresLength; i++) {
    if (descripcionError.compareTo(errores[i])) {
      errores[i] = "";
      break;
    }
  }
}

void clearErrors() {
  for (int i = 0; i < erroresLength; i++) {
    errores[i] = "";
  }
}

bool showErrors() {
  for (int i = 0; i < erroresLength; i++) {
    if (errores[i] != "") {
      printLine(errores[i], 1);
      return true;
    }
  }
  return false;
}

bool searchError(String descripcionError) {
  for (int i = 0; i < erroresLength; i++) {
    if (descripcionError.compareTo(errores[i])) {
      return true;
    }
  }
}
