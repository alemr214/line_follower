int IN1 = 2;
int IN2 = 3;
int INA = 5;
int IN3 = 7;
int IN4 = 8;
int INB = 9;

// Infrarojo
int infrarojo_izquierdo = 10;
int infrarojo_derecho = 11;
int infrarojo_medio = 6;
int infrarojo_lateral_derecho = 12;
int infrarojo_lateral_izquierdo = 4;

// Variables de entorno
int velocidad = 95;
int tiempo_ejecucion = 5;
int retraso = 1;
int negro = 1;
int blanco = 0;

// Variables para los sensores
int valor_inicial_infrarojo_izq = 0;
int valor_inicial_infrarojo_der = 0;
int valor_inicial_infrarojo_med = 0;
int valor_inicial_infrarojo_lat_der = 0;
int valor_inicial_infrarojo_lat_izq = 0;

void setup(){
  Serial.begin(9600);
  pinMode(infrarojo_izquierdo, INPUT);
  pinMode(infrarojo_derecho, INPUT);
  pinMode(infrarojo_medio, INPUT);
  pinMode(infrarojo_lateral_derecho, INPUT);
  pinMode(infrarojo_lateral_izquierdo, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void loop(){

  while (true){
    valor_inicial_infrarojo_izq = digitalRead(infrarojo_izquierdo);
    valor_inicial_infrarojo_der = digitalRead(infrarojo_derecho);
    valor_inicial_infrarojo_med = digitalRead(infrarojo_medio);
    valor_inicial_infrarojo_lat_der = digitalRead(infrarojo_lateral_derecho);
    valor_inicial_infrarojo_lat_izq = digitalRead(infrarojo_lateral_izquierdo);
    
    if (valor_inicial_infrarojo_izq == blanco && valor_inicial_infrarojo_med == negro && valor_inicial_infrarojo_der == blanco){
      movimiento_delante();
    }
    else if (valor_inicial_infrarojo_izq == negro && (valor_inicial_infrarojo_med == blanco || valor_inicial_infrarojo_med == negro) && valor_inicial_infrarojo_der == negro){
      movimiento_delante();
    }
    // Girar izquierda
    else if ( (valor_inicial_infrarojo_izq == blanco || valor_inicial_infrarojo_lat_izq == blanco) && (valor_inicial_infrarojo_med == negro || valor_inicial_infrarojo_med == blanco) && (valor_inicial_infrarojo_der == negro || valor_inicial_infrarojo_lat_der == negro)){
      movimiento_derecha();
    }
    // Girar derecha
    else if ((valor_inicial_infrarojo_izq == negro || valor_inicial_infrarojo_lat_izq == negro) && (valor_inicial_infrarojo_med == blanco || valor_inicial_infrarojo_med == negro) && (valor_inicial_infrarojo_der == blanco || valor_inicial_infrarojo_lat_der == blanco)){
      movimiento_izquierda();
    }
    // condicion para drift
    else if (valor_inicial_infrarojo_izq == blanco && valor_inicial_infrarojo_med == blanco && valor_inicial_infrarojo_der == blanco){
      detenerse();
    }
    else {
      detenerse();
    }


    
  }

}

void movimiento_delante(){ 
  analogWrite(INB, velocidad);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(INA, velocidad);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(tiempo_ejecucion);
}

void movimiento_atras(){
  analogWrite(INB, velocidad);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(INA, velocidad);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(tiempo_ejecucion);
}

void movimiento_derecha(){

  analogWrite(INB, velocidad+75);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(INA, velocidad);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(tiempo_ejecucion);
}

void movimiento_izquierda(){

  analogWrite(INA, velocidad+75);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(INB, velocidad);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(tiempo_ejecucion);
}

void detenerse(){
  analogWrite(INA, 0);
  analogWrite(INB, 0);
  delay(retraso);
}




