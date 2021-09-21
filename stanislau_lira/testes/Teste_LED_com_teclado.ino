/*
                 Arduino Uno/Mega
                 -----------------
             /|\|                 |
              | |                 |
              --| RST             |
                |                 |        -+
    LED_1  <--  | 49              |- <- Rx  -  Cabo USB
                |                 |- -> Tx  -
                |                 |        -+
                |                 | 
*/

#define LED_1 49 //define o pino de controle do LED como 49

int estado_LED1 = LOW; //Variavel que informa o estado do LED
char tecla; //Variavel que recebe um char do teclado

void setup() {
  /* Comunicação serial com o computador */
  Serial.begin(9600);
  while (!Serial);
  /* Configuração dos pinos como entrada ou saída */
  pinMode(LED_1, OUTPUT);
}

void tarefa_1(){
  
  tecla = Serial.read(); //lê um char do teclado
  /* Lógica para fazer o switch de um LED, apertando uma tecla*/
  if (tecla == '1'){
    if (estado_LED1 == HIGH)
      estado_LED1 = LOW;
    else
      estado_LED1 = HIGH;
    digitalWrite(LED_1, estado_LED1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  tarefa_1();
}
