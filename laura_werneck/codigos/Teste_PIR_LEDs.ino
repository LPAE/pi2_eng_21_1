/**********************************************************************************************************
  Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina-Campus Florianópolis
  Unidade Curricular: Projeto Integrador II
  Aluna: Laura Martin Werneck
  Semestre 2021.1
  Objetivo: Teste do sendor PIR com LEDs.
************************************************************************************************************/

#define LED 7 // LED 1 conectado ao pino digital 7.
#define LED2 5 // LED 2 conectado ao pino digital 5.
#define PIR 9  // PIR conectado ao pino digital 9.

void setup() { 
 Serial.begin(9600); // Inicia a porta serial, configura a taxa de dados para 9600 bps.
  pinMode(PIR, INPUT); // Define o PIR como entrada.
  pinMode(LED,OUTPUT); // Define o LED 1 como saida.
  pinMode(LED2, OUTPUT); // Define o LED 2 como saida.
}

void loop() {
  
int x= digitalRead(PIR); // Lê o valor do pino do PIR.

  if(x==LOW) // Caso o sensor não capte movimento.
  {
    digitalWrite(LED,LOW); // LED 1 continua apagado.
    digitalWrite(LED2, HIGH); // Acende o LED 2.
    Serial.println(x);
  }
  else // Caso o sensor capte movimento.
  {
    digitalWrite(LED,HIGH); // Acende o LED 1.
    digitalWrite(LED2, LOW); // Apaga o LED 2.
    Serial.println(x);//Imprime dados na porta serial
  }
}
