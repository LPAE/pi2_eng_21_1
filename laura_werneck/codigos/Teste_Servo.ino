/**********************************************************************************************************
  Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina-Campus Florianópolis
  Unidade Curricular: Projeto Integrador II
  Aluna: Laura Martin Werneck
  Semestre 2021.1
  Objetivo: Teste do funcionamento do servo motor.
************************************************************************************************************/
#include <Servo.h> // Inclui a biblioteca do Servo.
 
Servo myservo; 
 
int pos = 0; // Posição Servo.
 
void setup() 
{ 
  myservo.attach(8); // Anexa a variável Servo ao pino 8.
} 
  
void loop() 
{ 
  for(pos = 0; pos < 180; pos += 1) // Aumenta o angulo do servo ate chegar em 180 graus
  {                                   
    myservo.write(pos); // Grava o valor da posição do servo e controla o eixo de acordo.
    delay(6); 
  } 
  
  for(pos = 180; pos>=1; pos-=1)  // Diminui o angulo do servo
  {                                
    myservo.write(pos); 
    delay(6); //Pausa o programa por 6 ms.
  }  
} 
