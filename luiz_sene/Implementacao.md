# Implementação

Nesta etapa do projeto colocaremos em prática o que foi abordado e definido pelas etapas anteriores. De forma a atingir os objetivos estipulados,
podemos definir duas diferentes frentes de trabalho. Programação e Maquete.

## Progamação

O primeiro passo foi realizar testes com os componentes de forma a verificar e compreender seu funcionamento. Ao longo deste processo pode-se notar
que muito do que era feito ali poderia e foi integrado ao código final. Inicialmente apenas testes simples foram realizados, a fim de se habituar a plataforma 
utilizada, *ARDUINO IDE*, e sua metodologia. Este ambiente de desenvolvimento suporta as linguagens **C e C++**, além de já possuir diversas bibliotecas desenvolvidas
que auxiliam na implementação e operação de empreendimentos que se utilizem do Arduino, no caso deste projeto toda a programação foi feita através da linguagem **C**.

Cada componente foi testado separadamente através de rotinas simples, após isso métodos de interação entre eles foram gerados, resultando em um código funcional que atende
as exigências do projeto.É interessante destacar que visando uma interação entre os componentes que se aproxime mais da realidade de uma casa, algumas adaptações foram necessárias, por exemplo, a calibração do sensor PIR, visando uma resposta mais precisa foram feitos ajustes na sua sensibilidade e tempo de resposta, estes ajustes foram feitos no próprio *hardware* através de dois potenciômetros, e no caso de ser detectado movimento, um led relacionado ao ambiente será aceso, no caso nos fundos da casa. Foi necessário também atribuir ao sensor de gás um valor limite para que possa haver uma comparação entre o que é medido com o que seria considerado uma ameaça, este valor foi atribuído no código, e é definido como 300ppm, o que significa que caso ele detecte uma amostra de gás maior que 300 partes por milhão, o alarme será ativado, este alarme é um aviso sonoro via buzzer, bem como uma mensagem ao usuário. O servo motor foi programado para girar de 0° até 180º de forma a abrir o portão, e para fechar o oposto ocorre, para que isso ocorra o usuário poderá controlar digitando a letra 'a' para abrir e 'A' para fechar. Para os leds foram designadas teclas para controlar, minúsculas acendem e letras maiúsculas apagam, de acordo com a tabela abaixo. Todo o código fica dividio em duas funções principais *void setup();* onde são configurados os pinos, se serão de entrada ou saída, e *void loop();* onde o código é executado em forma de laço, sempre chamando as demais funções. Toda a programação pode ser visualizado abaixo da tabela 1.

  COD  | Ambiente                 
 ----- | ---------                
 z / Z | fundos         
 x / X | cozinha               
 c / C | quarto         
 v / V | banheiro                
 b / B | sala de estar                        
   m   | apaga todas
 a / A | abre/fecha portão

 
 
*tabela 1 - codigos de acionamento dos leds.*

# Código implementado.
<details>
  <summary>Clique para ver.</summary>
 
````C
/*mapeamento
                          Arduino MEGA 2560
                    -------------------------------
                    |                          USB| - entrada usb
                    |                          GND| - gnd
                    |                             | -
         saida 5V - |5V                     pino12| -> buzzer
                    |                       pino11| -> servo motor
                    |                             | -
                    |                       pino8 | <- sensor movimento
                    |                             |
                    |                       pino7 | -> led fundos
                    |                       pino6 | -> led cozinha
      sensor gas -> |A0                     pino5 | -> led quarto
                    |                       pino4 | -> led banheiro
                    |                       pino3 | -> led sala de estar
                    |                             |
                    -------------------------------
**/
/*atribui as variáveis os valores dos pinos*/
int ledPin7  =  7;
int ledPin6  =  6;
int ledPin5  =  5;
int ledPin4  =  4;
int ledPin3  =  3;
int ledPin2  =  2;
int mvePin8  =  8;
int buzPin12 = 12;
int srvPin11 = 11;

int gasPinA0 = A0;

/* variável de controle para a detectção de gas, esta variavel representa a quantidade
  de gas em partes por milhao, no caso 300ppm*/
int gas_limt = 300;
/*variável responsável pelo controle de posição do servo motor*/
int pos;
/*define um tempo para estabilizar a leitura feita pelo sensor*/
const unsigned long tmpo_sensor = 100;
/*variavel que contara o tempo em que a tarefa está sendo executada*/
unsigned long tmpo_tarefa = 0;
/*variavel que contara o tempo em que a tarefa está sendo executada*/
unsigned long tmpo_mtor = 0;
/*variavel que contara o tempo em que a tarefa está sendo executada, de forma a controlar a velocidade*/
const unsigned long vel_mtor = 15;
/*variavel responsavel pelo controle da lampada do sensor*/
static bool lam_sens = false;

#include <Servo.h>
Servo servo;

void setup()   {

  Serial.begin(9600);

  /*define os pinos a seguir como saída*/
  pinMode(ledPin7, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buzPin12, OUTPUT);

  /*define os pinos a seguir como entrada*/
  pinMode(mvePin8, INPUT);
  pinMode(gasPinA0, INPUT);

  /*atribui ao objeto servo o pino resposável pelo servo motor*/
  servo.attach(srvPin11);

  /*inicia o servo motor sempre na posicao 0*/
  servo.write(0);
}

void loop()
{
  /*variável responsável pela interação com o teclado*/
  char tecla;

  /*obtem o o tempo passado em millissegundos desde que o Arduino começou a executar o programa
  desta forma podemos controlar quanto tempo levara para cada medicao seja feita*/
  unsigned long tmpo_atual = millis();

  if (tmpo_atual - tmpo_tarefa > tmpo_sensor) {

    tmpo_tarefa = tmpo_atual;

    /*recebe a leitura do sensor de presenca, e chama a funcao relacionada*/
    int mve_sensor1 = digitalRead(mvePin8);
    presenca_1(mve_sensor1);

    /*recebe a leitura do sensor de gása e chama a funcao relacionada*/
    int gas_sensor1 = analogRead(gasPinA0);
    gas_dect(gas_sensor1);

  }

  /*detecta se há uma entrada no teclado*/
  if (Serial.available() > 0) {
    tecla = Serial.read();
  }

  /*se for pressionado o botõa 'a' aciona o servo motor para abrir o portão, se for presionado 'A', o portão fechara*/
  if (tecla == 'a' || tecla == 'A') {
    srv_motor(tecla);
  }
  /*chama a função resposavel por acender ou apagar os leds.*/
  else
    acende_led(tecla);

}

/* função responsável pelo acionamento do servo motor.
   recebe como parametro uma char que define se portão ira a abrir ou fechar.
*/
void srv_motor(char tecla) {

  /*caso receba o valor 'a' o portão abrira*/
  if (tecla == 'a') {
    pos = 0;
    /* a partir da posicao 0, incrementa um a um o angulo do motor até o limite de 90 graus
       possui um delay de forma a controlar a velocidade de acionamento*/
    while (pos <= 90) {
      unsigned long tmpo_at = millis();
      if (tmpo_at - tmpo_mtor > vel_mtor) {
        pos++;
        tmpo_mtor = tmpo_at;
        servo.write(pos);
      }
    }
  }
  /*caso receba o valor 'A' o portão ira fechar*/
  else if (tecla == 'A') {
    pos = 90;
    /* a partir da posicao 90, decrementa um a um o angulo do motor até o limite de 0 graus
       possui um delay de forma a controlar a velocidade de acionamento*/
    while (pos >= 0) {
      unsigned long tmpo_at = millis();
      if (tmpo_at - tmpo_mtor > vel_mtor) {
        pos--;
        tmpo_mtor = tmpo_at;
        servo.write(pos);
      }
    }
  }
}


/*função responsável pelo controle do sensor de gas.
  recebe como parametro uma int com o valor detectado pelo sensor.
*/
void gas_dect(int gas_sensor1) {
  /* Compara a leitura feita pelo sensor com o valor limite definido anteriormente.
      Caso o valor seja superior mostra no console o valor medido e aciona o buzzer.
      o buzzer continuara a fazer o barulho até que os valores voltem ao normal, ou seja,
      que não exista mais a ameaça do gás.
  */
  if (gas_sensor1 > gas_limt) {
    digitalWrite(buzPin12, LOW);
    Serial.print("Atenção!! Possível vazamento de gás.");
    Serial.print("Leitura: ");
    Serial.println(gas_sensor1);
  }
  /*caso o valor não seja superior ao definido, mantem o buzzer silencioso*/
  else
    digitalWrite(buzPin12, HIGH);
}

/*Função responsável pela deteccção de movimento.
  recebe como parametro uma int com o valor detectado pelo sensor.
*/
void presenca_1(int mve_sensor1) {
  /*caso o sensor acuse movimentação envia um sinal HIGH que por consequencia ira acender ao led
    relacionado ao ambiente em que se encontra o sensor. Se nada for detecctado ou a movimentação findar
    o led é apagado.
  */
  if (mve_sensor1 == HIGH) {
    digitalWrite(ledPin7, HIGH);
  }
  else {
    /*verifica se a lampada esta acesa, ou seja, lam_sens possui valor 1, caso não esteja, a matem apagada
    ou apaga caso não detecte movimento*/
    if (lam_sens == false)
      digitalWrite(ledPin7, LOW);
  }
}

/*Função responsável pelo acionamento dos leds.
  recebe como parametro uma char com o valor correspondente ao led.
  --------------------------------|
  |  COD  | ambiente              |
  --------------------------------|
  | z / Z | fundos                |
  | x / X | cozinha               |
  | c / C | quarto                |
  | v / V | banheiro              |
  | b / B | sala de estar         |
  |   m   | apaga todas           |
  --------------------------------|
  as letras minusculas acendem o led, enquanto o envio das maiusculas apaga.
*/

void acende_led(char tecla) {
  /*Compara o valor recebido com os disponiveis, uma vez que encontra executa o acionamento
    do led ou o apaga.
  */
  if (tecla == 'z')
  {
    /*atribui a variavel lam_sens o valor 1, dessa forma quando o sensor não detectar movimento, ira verificar se a lampada
    esta acesa, caso esteja ele não ira apaga-la*/
    digitalWrite(ledPin7, HIGH);
    lam_sens = true;
  }
  else if (tecla == 'Z') {
    digitalWrite(ledPin7, LOW);
    lam_sens = false;
  }

  else if (tecla == 'x')
  {
    digitalWrite(ledPin6, HIGH);
  }

  else if (tecla == 'X') {
    digitalWrite(ledPin6, LOW);
  }

  else if (tecla == 'c')
  {
    digitalWrite(ledPin5, HIGH);
  }
  else if (tecla == 'C') {
    digitalWrite(ledPin5, LOW);
  }

  else if (tecla == 'v')
  {
    digitalWrite(ledPin4, HIGH);
  }
  else if (tecla == 'V') {
    digitalWrite(ledPin4, LOW);
  }

  else if (tecla == 'b')
  {
    digitalWrite(ledPin3, HIGH);
  }
  else if (tecla == 'B') {
    digitalWrite(ledPin3, LOW);
  }


  else if (tecla == 'm')
  {
    digitalWrite(ledPin7, LOW);
    digitalWrite(ledPin6, LOW);
    digitalWrite(ledPin5, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin2, LOW);
  }
}
````
</details>

## Maquete

Para a maquete foi utilizado isopor do tipo Depron, que oferece uma estrutura firme.
O desing da casa, bem como o posicionamento de leds e sensores, seguem a disposição
mostrada na planta da etapa de concepção. 
  
 ![figura1](https://github.com/luiz-sene/ProjetoIntegradorII/blob/main/imagens/vista_frente.jpeg)
*figura 1 - Vista da frente da casa*

  Podemos observar na imagem abaixo a disposição dos componentes, e sua semelhança com o proposto na concepção.
  
 ![figura1](https://github.com/luiz-sene/ProjetoIntegradorII/blob/main/imagens/vista_superior.jpeg)
*figura 2 - Vista da parte de cima*

  ![figura1](https://github.com/luiz-sene/ProjetoIntegradorII/blob/main/imagens/vista_atras.jpeg)
*figura 3 - Vista da parte de trás*
