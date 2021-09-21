# Design

Conforme as necessidades do projeto, apresentadas na concepção, foi desenvolvida uma maquete eletrônica no *software* **Fritzing**.
Como é possível notar na figura 1, os seguintes componentes foram utilizados:

Quantidade | Componente
-----------|--------------
 1 | Arduino MEGA 2560
 1 | Protoboard
 1 | Servomotor Tower Pro SG90
 1 | Sensores de movimento HC-SR501
 1 | Sensores detectores de gás representados pelo MQ-4
 5 | LEDs que representam as lâmpadas
 5 | Resistores 1k




![figura1](https://github.com/luiz-sene/ProjetoIntegradorII/blob/main/imagens/design_PI_2_2.1_bb.png)
*figura 1 - Maquete eletrônica.*

## Testes dos componentes

A fim de verificar se os componentes individualmente se comportavam como esperado alguns testes foram realizados.
Para isso foi utilizada a plataforma *ARDUINO IDE* e a **linguagem C**. Cada um foi testado separadamente de acordo com os códigos abaixo.

#### Teste dos LED
<details>
  <summary>Clique para ver.</summary>
 
````C
/* atribui ao led que esta sendo testado o pino 7*/
int ledPin =  7; 
 
void setup()   {
/*define o pino 7 como saida*/
  pinMode(ledPin, OUTPUT); 
}
 
void loop() 
{
  /*coloca o pino 7 em nivel alto
  espera um tempo em seguida coloca o pino em nivel baixo, desta forma o led acende e apaga apos um tempo */
  digitalWrite(ledPin, HIGH);  
  delay(1000);               
  digitalWrite(ledPin, LOW); 
  delay(1000);              
} 
````
</details>

#### Teste do sensor de movimento PIR
<details>
  <summary>Clique para ver.</summary>
 
````C
int mvePin =  8; 
 
void setup()   {
/*define o pino 8 como entrada*/
  pinMode(mvePin, INTPUT); 
}
 
void loop() 
{
  /*variavel recebe o valor enviado pelo sensor no pino8*/
  int mve_sensor1 = digitalRead(mvePin);
  
  /*caso o sensor detecte movimento envia um sinal em nivel alto, o valor da variavel é comparado
  com valor alto,caso positivo, é mostrado para o usuário que o movimento foi detectado*/
  if(mve_sensor1 == HIGH)
  Serial.print("Movimento detectado");
  
  delay(1000)
} 
```` 
</details>

#### Teste do sensor de gás MQ2
<details>
  <summary>Clique para ver.</summary>

````C
/*atribui ao pino analogico A0 o sensor de gas */
int gasPin =  A0; 

/* variável de controle para a detectção de gas, esta variavel representa a quantidade
  de gas em partes por milhao, no caso 300ppm*/
int gas_limt = 300;

void setup()   {
/*define o pino A0 como entrada*/
  pinMode(gasPin, INTPUT); 
}
 
void loop() 
{
/*recebe a leitura do sensor de gás*/    
int gas_sensor1 = analogRead(gasPinA0);
  
/*compara o valor recebido do sensor com o valor limite estabelecido anteriormente,
caso este seja superior ao permitido, mostra ao usuario a medida e um aviso de seguranca*/
if(gas_sensor1 >= gas_limt){
    Serial.print("Atenção!! Possível vazamento de gás.");
    Serial.print("Leitura: ");
    Serial.println(gas_sensor1);
  }
  delay(1000)
} 
````
</details>


#### Teste do Buzzer
<details>
  <summary>Clique para ver.</summary>

````C
/*atribui ao pino 12 o buzzer */
int buzPin =  12; 

void setup()   {
/*define o pino 12 como saida*/
  pinMode(gasPin, OUTPUT); 
}
 
void loop() 
{
/*como o buzzer em questão ativa em nivel logico baixo, foi enviado um pulso baixo*/
digitalWrite(buzPin, LOW);
delay(500);
/*apos um tempo em funcionamento o buzzer e desligado atraves de um sinal alto*/
ditialWrite(buzPìn, HIGH);
delay(500);
} 
````
</details>

#### Teste do Servo motor
<details>
  <summary>Clique para ver.</summary>

````C
/*atribui ao pino 11 o servo motor */
int srvPin =  11; 

/*variavel responsavel por armazenar a posição do motor*/
int pos;
/*inclui a biblioteca disponivel pela plataforma, Servo.h, para facilitar a utilização do mesmo*/
#include <Servo.h>
/*define o objeto servo do tipo servo*/
Servo servo;

void setup()   {
 
 /*atribui o objeto servo ao pino resposável pelo servo motor*/
  servo.attach(srvPin11);

  /*define a posição inicial do servo motor como 0*/
  servo.write(0);
}
 
void loop() 
{
/*a partir da posicao 0 graus ate 90 graus, o servo ira se mover 1° de cada vez com um delay
para controlar a velocidade*/
for(pos = 0; pos <90; pos++){
 servo.write(pos);
 delay(20);
}
/*a partir da posicao 90 graus ate 0 graus, o servo ira se mover 1° de cada vez com um delay
para controlar a velocidade*/
for(pos = 90; pos >= 0; pos--){
 servo.write(pos);
 delay(20);
} 
````
</details>

