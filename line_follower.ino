#include  <Arduino.h>

// Declaración de los pines que controlarana los motores
int Motor1A = 7;   // IN1
int Motor1B = 6;   // IN2
int Motor2C = 5;   // IN3
int Motor2D = 4;   // IN4
int infPin = 10;    // Izquierdo - pin de infrarojos utilizado como entrada digital
int infPin1 = 8;   // Derecho
int infPinM = 9;
int valorInf = 0;  // Valor inicial de la lectura digital de los infrarrojos
int valorInf1 = 0;
int valorInfM = 0;
int ENA = 11;
int ENB = 3;
int velocidad = 100;
// Declaración del método para avanzar
void Avanzar(){
    digitalWrite(Motor1A, HIGH);
    digitalWrite(Motor1B, LOW);
    analogWrite(ENA,velocidad);

    digitalWrite(Motor2C, HIGH);
    digitalWrite(Motor2D, LOW);
    analogWrite(ENB,velocidad);
    delay(1);
}

// Declaración del método para girar a la derecha
void girarDerecha(){
    digitalWrite(Motor1A, HIGH);
    digitalWrite(Motor1B, LOW);
    analogWrite(ENA,velocidad);

    digitalWrite(Motor2C, LOW);
    digitalWrite(Motor2D, LOW);
    analogWrite(ENB,velocidad);
    delay(1);
}

// Declaración del método para girar a la izquierda
void girarIzquierda(){
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, LOW);
    analogWrite(ENA,velocidad);

    digitalWrite(Motor2D, LOW);
    digitalWrite(Motor2C, HIGH);
    analogWrite(ENB,velocidad);
    delay(1);
}

// Declaración del método para detener el vehiculo en caso de detectar una línea negra
void Stop(){
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, LOW);
    analogWrite(ENA,velocidad);
    digitalWrite(Motor2D, LOW);
    digitalWrite(Motor2C, LOW);
    analogWrite(ENB,velocidad);
    delay(500);
}

// Configuración de los sensores y los pines
void setup() {
  Serial.begin(9600);
  pinMode(infPin, INPUT);
  pinMode(infPin1, INPUT);
  pinMode(Motor1A, OUTPUT);
  pinMode(Motor1B, OUTPUT);
  pinMode(Motor2D, OUTPUT);
  pinMode(Motor2C, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2D, LOW);
  digitalWrite(Motor2C, LOW);
}

// Ejecución continua de todos los métodos
void loop() {
  valorInf = digitalRead(infPin);   // Valor de entrada para el infrarrojo izquierdo
  valorInf1 = digitalRead(infPin1); // Valor de entrada para el infrarrojo derecho
  valorInfM = digitalRead(infPinM); // Valor de entrada para el infrarroljo de en medio

  if (valorInf == 0 && valorInfM == 1 && valorInf1 == 0) { // Avance 
    Serial.println("Avanzar");
    Avanzar();
  }

  else if(valorInf == 0 && valorInfM == 1 && valorInf1 == 1){ // Gira hacia la derecha
    Serial.println("derecha");
    girarDerecha();
  }
  else if (valorInf == 0 && valorInfM == 0 && valorInf1 == 1){
    Serial.println("derecha");
    girarDerecha();
  }

  else if (valorInf == 1 && valorInfM == 1 && valorInf1 == 0) { // Gira hacia la izquierda
    Serial.println("izquierda");
    girarIzquierda();

  }
  else if (valorInf == 1 && valorInfM == 0 && valorInf1 == 0){
    Serial.println("izquierda");
    girarIzquierda();
  }

  else if (valorInf == 1 && valorInfM == 1 && valorInf1 == 1) { // STOP
    Serial.println("Avanzar todos prendidos");
    Avanzar();
  }

  else if (valorInf == 0 && valorInfM == 0 && valorInf1 == 0){
    Avanzar();
    delay(1000);
    girarDerecha();
    delay(1000);
    girarIzquierda();
    delay(1000);
  }

  else if (valorInf == 1 && valorInfM == 0 && valorInf1 == 1){
    Avanzar();
  }

  else{
    Serial.println("Giro xd");
    Serial.println("El valor INF "); Serial.println(valorInf);
    Serial.println("El valor INF1 "); Serial.println(valorInf1);
    Serial.println("El valor INFM "); Serial.println(valorInfM);
    Avanzar();
    delay(1000);
    girarDerecha();
    delay(1000);
    girarIzquierda();
    delay(1000);
  }
}
