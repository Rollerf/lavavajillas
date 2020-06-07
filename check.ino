bool check(){
  digitalWrite(EV_EntradaAgua, LOW);
  digitalWrite(Calentador, LOW);
  digitalWrite(mRecirculacion, LOW);

  if(sensorNivel->switchMode()){
    digitalWrite(bVaciado, HIGH);

    return false;
  }else{
    digitalWrite(bVaciado, LOW);
  }

  if(sensorFugas->switchMode()){
    vaciado();

    return false;
  }else{
    digitalWrite(bVaciado, LOW);
  }
  
  return true;
}
//Checkear sonda de temperatura. Que no tenga error 
