/**********************************************************************************************************
  Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina-Campus Florianópolis
  Unidade Curricular: Projeto Integrador II
  Aluna: Laura Martin Werneck
  Semestre 2021.1
  Objetivo: Teste do funcionamento do sensor MQ2 e do buzzer.
************************************************************************************************************/
int Pinbuzzer = 2; // Buzzer conectado ao pino digital 2.
int PinA0 = A0;  // MQ2 conectado ao pino analógico A0.

//int leitura_sensor = 300; // Define o valor máximo da leitura do sensor.

void setup() {
  pinMode(PinA0, INPUT); // Define o MQ2 como entrada.
  pinMode(Pinbuzzer, OUTPUT); // Define o Buzzer como saida.
  Serial.begin(9600); // Inicia a porta serial, configura a taxa de dados para 9600 bps.
}
void loop() {
  int valor_analogico = analogRead(PinA0);
  Serial.print("Leitura: "); // Mostra no monitor serial o valor da leitura do MQ2.
  Serial.println(valor_analogico); // Valor obtido pelo MQ2.
  if (valor_analogico > 300) {  // Caso a leitura seja maior do que o valor estabelecido como limite,
    digitalWrite(Pinbuzzer, LOW); // aciona o Buzzer.
  }
  else{ // Caso contrário,
    noTone(Pinbuzzer); // deixa o buzzer desligado.
    digitalWrite(Pinbuzzer, HIGH); //Aciona um valor HIGH no pino do Buzzer.
  }
  delay(1000); //Pausa o programa por 1000 ms.
}
