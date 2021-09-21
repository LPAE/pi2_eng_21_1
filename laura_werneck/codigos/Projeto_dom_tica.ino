/**********************************************************************************************************
  Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina-Campus Florianópolis
  Unidade Curricular: Projeto Integrador II
  Aluna: Laura Martin Werneck
  Semestre 2021.1
  Objetivo: Automção residencial
************************************************************************************************************/

/* Definição dos pinos que os componentes foram ligados*/
#define LED_Q1 13 /* Q1 = quarto 1 (perto da cozinha) */
#define LED_Q2 12 /* Q2 = quarto 2 (perto da sala) */
#define LED_S 11 /* S = sala */
#define LED_J 10 /* J = jardim */
#define PIR 9

#define Buzzer 2
#define MQ_2 A0
#include <Servo.h> /* incluir a biblioteca de servo */
Servo myservo;  /* Inclusão do servo */
int pos = 0;  /* Posição zero para o servo */

void setup() {
  /* Comunicação serial com o computador */
  Serial.begin(9600);
  while (!Serial);
  /* Configuração dos pinos como entrada ou saída */
  pinMode(LED_Q1, OUTPUT);
  pinMode(LED_Q2, OUTPUT);
  pinMode(LED_J, OUTPUT);
  pinMode(LED_S, OUTPUT);
  pinMode(PIR, INPUT);

  myservo.attach(8);  /*Pino do servo+arduino */
  myservo.write(0);  /* Servo setado com valor zero */

  pinMode(MQ_2, INPUT);
  pinMode(Buzzer, OUTPUT);

  Serial.flush();  //Limpando a memoria do serial
  Serial.println("Digite: \n 'a' para acender a luz do quarto 1 (próximo à  cozinha) \n 'A' para apagar a luz do quarto 1"); // Imprime o menu de comandos.
  Serial.println(" 'b' para acender a luz do quarto 2 (próximo à  sala) \n 'B' para apagar a luz do quarto 2");
  Serial.println(" 'c' para acender a luz da sala \n 'C' para apagar a luz da sala \n 'd' para apagar todas as luzes internas");
  Serial.println(" 'e' para arir o portão \n 'E' para fechar o portão");
}


void tarefa_1() { // Acender e apagar as luzes internas
  if (Serial.available() > 0) { //Teste se porta serial esta recebendo dados
    char tecla;
    tecla = Serial.read(); // Lê o valor digitado pelo usuário.
    if (tecla == 'a') // Acende a luz do Quarto 1.
    {
      digitalWrite(LED_Q1, HIGH);
    }
    else if (tecla == 'A') // Apaga a luz do Quarto 1.
    {
      digitalWrite(LED_Q1, LOW);
    }
    else if (tecla == 'b') // Acende a luz do Quarto 2.
    {
      digitalWrite(LED_Q2, HIGH);
    }
    else if (tecla == 'B') // Apaga a luz do Quarto 2.
    {
      digitalWrite(LED_Q2, LOW);
    }
    else if (tecla == 'c') // Acende a luz da sala.
    {
      digitalWrite(LED_S, HIGH);
    }
    else if (tecla == 'C') // Apaga a luz da sala.
    {
      digitalWrite(LED_S, LOW);
    }
    else if (tecla == 'd') // Apaga todas as luzes.
    {
      digitalWrite(LED_Q1, LOW);
      digitalWrite(LED_Q2, LOW);
      digitalWrite(LED_S, LOW);
    }
    else if (tecla == 'e') // Abre a cancela.
    {
      myservo.write(90);
      delay(500);
    }
    else if (tecla == 'E') // Fecha a cancela.
    {
      myservo.write(-180);
      delay(500);
    }
  }
  Serial.flush();
}

void tarefa_2() {
  int x = digitalRead(PIR); // Lê o valor do pino do PIR.

  if (x == LOW) // Caso o sensor não capte movimento.
  {
    digitalWrite(LED_J, LOW); // Não aciona a luz do jardim.
  }
  else // Caso o sensor capte movimento.
  {
    digitalWrite(LED_J, HIGH); // Acende a luz do jardim.
  }
}

const unsigned long periodo_tarefa_3 = 2000; // Temporiza a leitura dos valores do MQ2
unsigned long tempo_tarefa_3 = millis();

void tarefa_3(unsigned long tempo_atual) {
  int valor_analogico = analogRead(MQ_2);
  if(tempo_atual - tempo_tarefa_3 > periodo_tarefa_3) {
    tempo_tarefa_3 = tempo_atual;
 // Serial.print("Leitura: "); // Mostra no monitor serial o valor da leitura do MQ2.
  //Serial.println(valor_analogico); // Valor obtido pelo MQ2.
  if (valor_analogico > 300) {  // Caso a leitura seja maior do que o valor estabelecido como limite,

    digitalWrite(Buzzer, LOW); // aciona o Buzzer.
  }
  else { // Caso contrário,
    noTone(Buzzer); // deixa o buzzer desligado.
    digitalWrite(Buzzer, HIGH); //Aciona um valor HIGH no pino do Buzzer.
  }
}
}

void loop() {

  unsigned long meu_tempo_atual = millis();

  tarefa_1();

  tarefa_2();

  tarefa_3(meu_tempo_atual);
}

