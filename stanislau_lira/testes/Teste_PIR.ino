/*
                 Arduino Uno/Mega
                 -----------------
             /|\|                 |
              | |                 |
              --| RST             |
                |                 |        -+
    LED_1  <--  | 49              |- <- Rx  -  Cabo USB
    PIR    <--  | 53              |- -> Tx  -
                |                 |        -+
                |                 | 
*/

#define LED_1 49 //define o pino de controle do LED como 49
#define PIR 53 //define o pino de entrada do pir como 53

int estado_LED1 = LOW; //Variavel que informa o estado do LED


void setup() {
  /* Comunicação serial com o computador */
  Serial.begin(9600);
  while (!Serial);
  /* Configuração dos pinos como entrada ou saída */
  pinMode(LED_1, OUTPUT);
  pinMode(PIR, INPUT);
}

void tarefa_1(){
  
  int movimento= digitalRead(PIR);
  /* Lógica para fazer o LED acender caso detectado movimento*/
  if (movimento == HIGH)
      estado_LED1 = HIGH;
  else
      estado_LED1 = LOW;
      digitalWrite(LED_1, estado_LED1);
      Serial.println(movimento);
}

void loop() {
  // put your main code here, to run repeatedly:
  tarefa_1();
}
