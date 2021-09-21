# Implementação
Avançando no projeto, cujo o objetivo é construir e operar uma maquete de uma residencia automatizada, além de adquirir conhecimento sobre o assunto de automação residencial, começamos a etapa de implementação.

Nesta etapa será desenvolvido a maquete, levando em consideração a planta baixa apresentada na etapa de concepção, e o densenvolvimento do código completo para a automatização da maquete, com todos os componentes apresentados na etapa de design, no final desta etapa o projeto (em questão de desenvolvimento) deverá estar finalizado. A programção é feita através do IDE Arduino, sendo necessário selecionar o modelo de placa que será utilizado (Mega 2560) na barra de "Ferramentas" antes de carregar o codigo.

## Integração dos Componentes

Realizando a conexão de todos os componentes no Arduino e utilizando os códigos de testes anteriores e a experiência adquirida na etapa anterior, foi desenvolvido um código final para o projeto que integrasse todos os componentes que vão ser utilizados, realizando todas as funções necessárias, que foram apresentadas na concepção e design do projeto. Desta forma finalizamos a parte de programação do projeto e temos um projeto elétrico pronto para ser inserido na maquete.

![](./imagens/Projeto%20elétrico.jpg)

No link abaixo temos o código finalizado da casa, com as funções previamente apresentadas.

[Codigo da Casa Automatizada](./testes/Codigo_Final.ino)

### Setup do Codigo 
~~~ C  
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

int prioridade_LED1; //Variavel que informa prioridade do LED, para um controle independente do PIR e do teclado
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
~~~
### Loop
A função loop mantem a 3 tarefas sendo reproduzidas sem parar, é importante frisar a temporização das tarefas, para não sobrecarregar o microcontrolador, já que existem tarefas
que não necessitam ser executadas a todo momento. 
~~~ C
void loop() {
  unsigned long meu_tempo_atual = millis();
  tarefa_1();
  tarefa_2(meu_tempo_atual);
  tarefa_3(meu_tempo_atual);
}
~~~

### Sensor MQ2
Na tarefa_2 temos o exemplo de como é feita a temporização de funções. Nessa função temos a detecção de vazamento de gás, informando para o display do computador e abrindo o portão eletrônico. Para testar um isqueiro foi utilizado para soltar gás próximo ao sensor até que ele acione e seja verificado o acionamento dos dipositivos desejados.
~~~ C
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
~~~

### Sensor PIR
Nessa função temos a detecção de movimento na parte frontal da casa, ligando o LED externo e informando para o display do computador. Para testar foi utilizado apenas o 
movimento da mão na frente do sensor PIR verificando o funcionamento correto dos itens desejados.
~~~ C
const unsigned long periodo_tarefa_3 = 1000; //define o tempo em milisegundos para ler o PIR
unsigned long tempo_tarefa_3 = millis();

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
~~~

### Acionamentos pelo teclado
Nessa função devemos controlar todos os LEDs de forma indepente, abrir e fechar o portão eletrônico e mostrar o menu, de acordo com o que for solicitado pelo teclado. O Serial.avaible() retorna se o monitor serial recebeu alguma informação do teclado, caso nada for recebido, a função não faz nada.
~~~ C
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
~~~
### Menu 

Utilizado apenas para imprimir no monitor serial as ações que podem ser realizas pelo teclado
~~~ C
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
~~~

## Construção da Maquete
Com o projeto elétrico finalizado, foi realizada a construção da maquete tomando como base a planta baixa apresentada na etapa de concepção. Para a confecção da maquete foi utilizada uma caixa de papelão, palito de dente, durex e cola.
![](./imagens/Construção%20maquete.jpg)

Com a maquete finalizada foi integrado a parte elétrica nela, foi utilizado uma outra caixa de papelão na parte inferior para armazenar os componentes. 

![](./imagens/Integração%20elétrica.jpg)

### Maquete Finalizada

![](./imagens/Maquete%20finalizada.jpg)
