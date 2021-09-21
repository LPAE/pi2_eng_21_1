  
/*
 *                  Arduino Uno
 *               -----------------
 *           /|\|             A15 | <--- MQ2
 *            | |                 |
 *            --| RST             |-
 *              |                 |        -+
 *  LED_1  <--- | 49              |- <- Rx  -  Cabo USB
 *  LED_2  <--- | 47              |- -> Tx  -
 *  LED_3  <--- | 45              |        -+
 *  LED_4  <--- | 43           51 | <--- MQ2
 *  LED_5  <--- | 41           53 | <--- PIR
 *  LED_6  <--- | 39              |
 *  Servo  <--- | 13              |
 *               -----------------
*/

#include <Servo.h> //biblioteca do servo

#define LED_1 49 //define o pino de controle do LED como 49
#define LED_2 47 //define o pino de controle do LED como 47
#define LED_3 45 //define o pino de controle do LED como 45
#define LED_4 43 //define o pino de controle do LED como 43
#define LED_5 41 //define o pino de controle do LED como 41
#define LED_6 39 //define o pino de controle do LED como 39

#define MQD 51 //define o pino de entrada digital do mq2 como 51
#define MQA A15 //define o pino de entrada analogio do mq2 a15

#define PIR 53 //define o pino de entrada do pir como 53


Servo myservo;  // cria uma variavel de controle pro servo

int prioridade_LED1; //Variavel que informa prioridade do LED
int estado_LED1 = LOW; //Variavel que informa o estado do LED
int estado_LED2 = LOW; //Variavel que informa o estado do LED
int estado_LED3 = LOW; //Variavel que informa o estado do LED
int estado_LED4 = LOW; //Variavel que informa o estado do LED
int estado_LED5 = LOW; //Variavel que informa o estado do LED
int estado_LED6 = LOW; //Variavel que informa o estado do LED

int pos = 5;    // Variavel para armazenar/inicializar a posição do servo

char tecla; //Variavel que recebe um char do teclado

void setup() {
  /* Comunicação serial com o computador */
  Serial.begin(9600);
  while (!Serial);
  /* Configuração dos pinos como entrada ou saída */
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(MQD, INPUT);  
  pinMode(MQA, INPUT);
  pinMode(PIR, INPUT);
  /* Configura o pino 13 como controle do servo e inicia com o portão fechado*/
  myservo.attach(13);
  myservo.write(pos);
  /* inicializa o menu ao ligar o sistema */
  menu();
}


void tarefa_1(){
 if (Serial.available() != 0){ //Caso for lido algum dado pelo teclado...

  tecla = Serial.read(); //lê um char do teclado
  /* Lógica para fazer o switch de um LED, apertando uma tecla*/

  if (tecla == '1'){
    if (estado_LED1 == HIGH){
      estado_LED1 = LOW;
      prioridade_LED1 = LOW;
    }
    else{
      estado_LED1 = HIGH;
      prioridade_LED1 = HIGH;
    }
    digitalWrite(LED_1, estado_LED1);
  }
  if (tecla == '2'){
    if (estado_LED2 == HIGH)
      estado_LED2 = LOW;
    else
      estado_LED2 = HIGH;
    digitalWrite(LED_2, estado_LED2);
  }
  if (tecla == '3'){
    if (estado_LED3 == HIGH)
      estado_LED3 = LOW;
    else
      estado_LED3 = HIGH;
    digitalWrite(LED_3, estado_LED3);
  }
  if (tecla == '4'){
    if (estado_LED4 == HIGH)
      estado_LED4 = LOW;
    else
      estado_LED4 = HIGH;
    digitalWrite(LED_4, estado_LED4);
  }
  if (tecla == '5'){
    if (estado_LED5 == HIGH)
      estado_LED5 = LOW;
    else
      estado_LED5 = HIGH;
    digitalWrite(LED_5, estado_LED5);
  }
  if (tecla == '6'){
    if (estado_LED6 == HIGH)
      estado_LED6 = LOW;
    else
      estado_LED6 = HIGH;
    digitalWrite(LED_6, estado_LED6);
  }  
  if (tecla == '7'){
    if (pos >= 40)
      pos = 5;
    else
      pos = 80;
    myservo.write(pos); // Faz o servo ir para a posição desejada
  } 
  if (tecla == 'm'){
    menu ();
  }         
 }
}

const unsigned long periodo_tarefa_2 = 3000; //define o tempo em milisegundos para ler o MQ2
unsigned long tempo_tarefa_2 = millis();

void tarefa_2(unsigned long tempo_atual){
 if(tempo_atual - tempo_tarefa_2 > periodo_tarefa_2) {
    tempo_tarefa_2 = tempo_atual; 
  int gas = digitalRead(MQD);
  int analog = analogRead(MQA);
  /* Lógica para avisar caso detectado gas/imprimir o valor analogico e abrir o portão*/
  if (gas == LOW){
   Serial.println("Vazamento de gas/fumaca detectado!!!!!! Concentracao:");
   Serial.println(analog);
   Serial.println();
   pos = 80;
   myservo.write(pos);
  }
 }
}

const unsigned long periodo_tarefa_3 = 1000; //define o tempo em milisegundos para ler o PIR
unsigned long tempo_tarefa_3 = millis();

void tarefa_3(unsigned long tempo_atual){
if(tempo_atual - tempo_tarefa_3 > periodo_tarefa_3) {
    tempo_tarefa_3 = tempo_atual;
  int movimento= digitalRead(PIR);
  /* Lógica para fazer o LED acender caso detectado movimento*/
  if (movimento == HIGH){
      estado_LED1 = HIGH;
      Serial.println("movimento detectado na entrada!");}
  else if (prioridade_LED1 == LOW)
      estado_LED1 = LOW;
  digitalWrite(LED_1, estado_LED1);
 }
}

void menu(){
  Serial.println("Menu:");
  Serial.println("Tecla '1': Acende/apaga a luz da entrada");
  Serial.println("Tecla '2': Acende/apaga a luz da sala/cozinha");
  Serial.println("Tecla '3': Acende/apaga a luz do quarto 1");
  Serial.println("Tecla '4': Acende/apaga a luz do quarto 2");
  Serial.println("Tecla '5': Acende/apaga a luz do banheiro 1");
  Serial.println("Tecla '6': Acende/apaga a luz do banheiro 2");
  Serial.println("Tecla '7': Abre/fecha o portão eletronico");
  Serial.println("Tecla 'm': Mostra o menu de funções da casa");
}

void loop() {
  unsigned long meu_tempo_atual = millis();
  tarefa_1();
  tarefa_2(meu_tempo_atual);
  tarefa_3(meu_tempo_atual);
}
