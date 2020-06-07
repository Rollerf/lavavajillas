bool vaciado(){

  if(tVaciado->IN(true)){
    digitalWrite(bVaciado, HIGH);
    return false;
  }

  else{
    digitalWrite(bVaciado, LOW);
    tVaciado->IN(false);  
    return true;
  }
}

bool entradaAgua(){
  
}
