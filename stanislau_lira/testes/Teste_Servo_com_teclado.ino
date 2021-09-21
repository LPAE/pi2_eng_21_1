/*
                 Arduino Uno/Mega
                 -----------------
             /|\|                 |
              | |                 |
              --| RST             |
                |                 |        -+
    Servo  <--  | 13              |- <- Rx  -  Cabo USB
                |                 |- -> Tx  -
                |                 |        -+
                |                 | 
*/

#include <Servo.h> //biblioteca do servo

Servo myservo;  // cria uma variavel de controle pro servo
int pos = 5;    // variavel para armazenar a posição do servo

char tecla; //Variavel que recebe um char do teclado

void setup() {
  /* Comunicação serial com o computador */
  Serial.begin(9600);
  while (!Serial);
  /* Configuração dos pinos como entrada ou saída */
  myservo.attach(13);  // configura o pino 13 como controle do servo
}

void tarefa_1(){
  myservo.write(pos);
  tecla = Serial.read(); //lê um char do teclado
  /* Lógica para fazer o switch de um LED, apertando uma tecla*/
  if (tecla == '1'){
    if (pos >= 40)
      pos = 5;
    else
      pos = 80;
    myservo.write(pos); // Faz o servo ir para a posição desejada
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  tarefa_1();
}
