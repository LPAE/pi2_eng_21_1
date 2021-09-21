/*##################################################################################################################################################################*/

/* THE_HOUSE_CARIOCA.ino
 * Programa principal para o Projeto Integrador II do curso de Engenharia Eletrônica no IFSC
 * Propriedade de Gabriel de Oliveira Peres - Aluno do curso de Engenharia Eletrônica no IFSC
 * Email: peres.gabriel.gabriel@gmail.com
 * GitHub: https://github.com/imperes
 */

/*##################################################################################################################################################################*/

/* Bibliotecas utilizadas */
#include "DHT.h"                                  // Biblioteca do Sensor de Temperatura e Umidade
#include <Servo.h>                                // Biblioteca do Motor Servo
#include <Wire.h>                                 // Parte complementar da biblioteca do Display 16x2 para comunicação I2C
#include <LiquidCrystal_I2C.h>                    // Biblioteca do Display 16x2 com comunicação I2C

/*##################################################################################################################################################################*/

/* Definição dos PINOS DOS LEDS */
#define LEDB1 2                                   // LED Branco           SALA                           1° ANDAR
#define LEDB2 3                                   // LED Branco           COZINHA                        1° ANDAR
#define LEDB3 4                                   // LED Branco           QUARTO 1                       2° ANDAR
#define LEDB4 10                                  // LED Branco           QUARTO 2                       2° ANDAR
#define LEDB5 11                                  // LED Branco           QUARTO 3                       3º ANDAR
#define LEDV1 5                                   // LED Azul             JARDIM
#define LEDV2 6                                   // LED Laranja          JARDIM
#define LEDV3 7                                   // LED Branco           JARDIM
#define LEDV4 8                                   // LED Verde            VARANDA                        3° ANDAR
#define LEDV5 9                                   // LED Azul             GARAGEM

/* Definição dos SENSORES & MOTORES */
#define MQ2 A7                                    // Sensor de Gás - MQ2
#define LDR A0                                    // Resistor Variável Conforme Incidência De Luz
#define PIR 40                                    // Sensor de Movimento - PIR
#define BUZZER 12                                 // Componente que emite som

#define STU A1                                    // Sensor de Temperatura e Umidade - DHT
#define DHTTYPE DHT11                             // Modelo DHT (DHT11)
DHT dht(STU, DHTTYPE);                            // Configura o sensor DTH com o modelo e o pino utilizado

#define SERVO 46                                  // Motor Servo
Servo motor;                                      // Cria um objeto Servo para controlar o Servo

/* Variáveis Globais*/                            // É necessário que os valores independente do contexto de execução das funções seja mantido                          
int limite_de_gas = 300;                          // Configura a concentração limite de gás normal (Valor Máximo)
int nivel_de_luz = 500;                           // Configura a intensidade luminosa para ligar ou desligar o sistema de iluminação do jardim
int posicao_motor = 0;                            // Configura a posição inicial do Motor Servo para 0°

LiquidCrystal_I2C lcd(0x27, 16, 2);               // Configurando Display LCD 16x2 no endereço 0x27 para 16 colunas e 2 linhas

/*##################################################################################################################################################################*/

void setup() 
{
  /* Configurações Gerais*/
  Serial.begin(9600);                             // Inicia a comunicação serial com o computador
  
  dht.begin();                                    // Inicia o Sensor de Temperatura e Umidade
  
  motor.attach(SERVO);                            // Associa o pino escolhido ao servo motor
  motor.write(posicao_motor);                     // Inicia o Motor Servo na posição 0°

  lcd.init();                                     // Inicia o LCD DISPLAY 16x2
  lcd.backlight();                                // Liga a iluminação do LCD Display 16x2
  
  lcd.clear();                                    // Limpa o Display
  lcd.setCursor(3,0);                             // Seta cursor na coluna 3 linha 1
  lcd.print("THE HOUSE");                         // Escreve o nome do projeto
  lcd.setCursor(5,1);                             // Seta o Cursor na coluna 5 e linha 2
  lcd.print("CARIOCA");                           // Escreve a segunda parte do projeto
  delay(1000);                                    // Dá um tempo de 1s 
  lcd.clear();                                    // Limpa o Display novamente
  
  /* Configurações dos pinos do LED como ENTRADA ou SAÍDA */
  pinMode(LEDB1, OUTPUT);
  pinMode(LEDB2, OUTPUT);
  pinMode(LEDB3, OUTPUT);
  pinMode(LEDB4, OUTPUT);
  pinMode(LEDB5, OUTPUT);
  pinMode(LEDV1, OUTPUT);
  pinMode(LEDV2, OUTPUT);
  pinMode(LEDV3, OUTPUT);
  pinMode(LEDV4, OUTPUT);
  pinMode(LEDV5, OUTPUT);

  /* Configurações dos pinos dos SENSORES como ENTRADA ou SAÍDA */
  pinMode(MQ2, INPUT);
  pinMode(PIR, INPUT);
  pinMode(BUZZER, OUTPUT);

  /* Configura o BUZZER para ficar desligado */
  digitalWrite(BUZZER, HIGH);
  
  /* Manual de funcionamento no monitor Serial*/
  Serial.flush();                                 // Limpa a memória Serial
  Serial.println("SEJA BEM VINDO(A) A THE HOUSE CARIOCA");
  Serial.println("DIGITE: \n 'S' para acender a luz da SALA no 1° andar \n 's' para apagar a luz da SALA no 1° andar");
  Serial.println(" 'C' para acender a luz da COZINHA no 1° andar \n 'c' para apagar a luz da COZINHA no 1° andar");
  Serial.println(" 'J' para acender a luz do JARDIM \n 'j' para apagar a luz do JARDIM");
  Serial.println(" 'G' para acender a luz da GARAGEM \n 'g' para apagar a luz da GARAGEM");
  Serial.println(" 'P' para abrir o PORTÃO \n 'p' para fechar o PORTÃO");
  Serial.println(" 'V' para acender a luz da VARANDA \n 'v' para apagar a luz da VARANDA");
  Serial.println(" 'B' para acender a luz do QUARTO 1 no 2° andar \n 'b' para apagar a luz do QUARTO 1 no 2° andar");
  Serial.println(" 'N' para acender a luz do QUARTO 2 no 2° andar \n 'n' para apagar a luz do QUARTO 2 no 2° andar");
  Serial.println(" 'M' para acender a luz do QUARTO 3 no 3° andar \n 'm' para apagar a luz do QUARTO 3 no 3° andar");   
  Serial.println(" 'T' para acender todas as luzes \n 't' para apagar todas as luzes");
}

/*##################################################################################################################################################################*/

void acender_luz()
{
  if (Serial.available() > 0)                     // Verifica se a porta serial está disponível
  {
    char letra;
    letra = Serial.read();
    if (letra == 'S')                             
    {
      digitalWrite(LEDB1, HIGH);
    }
    else if (letra == 's')
    {
      digitalWrite(LEDB1, LOW);  
    }
    else if (letra == 'C')
    {
      digitalWrite(LEDB2, HIGH);
    }
    else if (letra == 'c')
    {
      digitalWrite(LEDB2, LOW);
    }
    else if (letra == 'J')
    {
      digitalWrite(LEDV1, HIGH);
      digitalWrite(LEDV2, HIGH);
      digitalWrite(LEDV3, HIGH);  
    }
    else if (letra == 'j')
    {
      digitalWrite(LEDV1, LOW);
      digitalWrite(LEDV2, LOW);
      digitalWrite(LEDV3, LOW);
    }
    else if (letra == 'P')
    {
      motor.write(90);
    }
    else if (letra == 'p')
    {
      motor.write(-90);
    }
    else if (letra == 'V')
    {
      digitalWrite(LEDV4, HIGH);
    }
    else if (letra == 'v')
    {
      digitalWrite(LEDV4, LOW);
    }
    else if (letra == 'B')
    {
      digitalWrite(LEDB3, HIGH);
    }
    else if (letra == 'b')
    {
      digitalWrite(LEDB3, LOW);
    }
    else if (letra == 'G')
    {
      digitalWrite(LEDV5, HIGH);
    }
    else if (letra == 'g')
    {
      digitalWrite(LEDV5, LOW);
    }
    else if (letra == 'N')
    {
      digitalWrite(LEDB4, HIGH);
    }
    else if (letra == 'n')
    {
      digitalWrite(LEDB4, LOW);
    }
    else if (letra == 'M')
    {
      digitalWrite(LEDB5, HIGH);
    }
    else if (letra == 'm')
    {
      digitalWrite(LEDB5, LOW);
    }
    else if (letra == 'T')
    {
      digitalWrite(LEDB1, HIGH);
      digitalWrite(LEDB2, HIGH);
      digitalWrite(LEDB3, HIGH);
      digitalWrite(LEDB4, HIGH);
      digitalWrite(LEDB5, HIGH);
      digitalWrite(LEDV1, HIGH);
      digitalWrite(LEDV2, HIGH);
      digitalWrite(LEDV3, HIGH);
      digitalWrite(LEDV4, HIGH);
      digitalWrite(LEDV5, HIGH);
    }
    else if (letra == 't')
    {
      digitalWrite(LEDB1, LOW);
      digitalWrite(LEDB2, LOW);
      digitalWrite(LEDB3, LOW);
      digitalWrite(LEDB4, LOW);
      digitalWrite(LEDB5, LOW);
      digitalWrite(LEDV1, LOW);
      digitalWrite(LEDV2, LOW);
      digitalWrite(LEDV3, LOW);
      digitalWrite(LEDV4, LOW);
      digitalWrite(LEDV5, LOW);
    }
  }
  Serial.flush();
}

/*##################################################################################################################################################################*/

void sensor_movimento(unsigned long tempo_atual)
{
  bool movimento = digitalRead(PIR);                                     // Lê o Sensor de movimento - PIR
  if (movimento == HIGH ){
    Serial.println("SAÍDA DE VEÍCULO! CUIDADO!");                        // Envia mensagens de aviso
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("VEICULO SAINDO");
    lcd.setCursor(5,1);
    lcd.print("CUIDADO");
    motor.write(90);
    for (int repetir = 1; repetir <=10; repetir++)                       // Soa o alarme
      {
        for (int x = 90; x > 0; x--)
        {
          float sen;
          int f;
                                                                        
          sen = (cos(x * 3.1416 / 180));                                // Converte graus para rad e depois obtém o valor de sen
                                                                        
          f = 500 + (int(sen * 1000));                                  // Gera uma frequência a partir do valor de sen
          tone(BUZZER, f);
          delay(12);
          }
    noTone(BUZZER);                                                     // Desliga buzzer
    digitalWrite(BUZZER, HIGH);
    }
    lcd.clear();                                                        // Limpa o Display do LCD
    motor.write(-90);
    }
  else (movimento == LOW );{                                            // Função vazia pois não quero que faça nada quando não detecta movimento. Apenas quando houver movimento
      
    }
  }

/*##################################################################################################################################################################*/

/* Variáveis Globais que temporiza as funções */
const unsigned long periodo_gas = 2000;
unsigned long tempo_gas = millis();

void sensor_gas(unsigned long tempo_atual)
{
  int valor_analogico = analogRead(MQ2);
  if (tempo_atual - tempo_gas > periodo_gas)
  {
    tempo_gas = tempo_atual;
    lcd.setCursor(0,0);
    lcd.print("GAS: "); 
    lcd.println(valor_analogico);
    lcd.setCursor(0,0);
    delay(100);
    if(valor_analogico > limite_de_gas)
    {
      Serial.println("ALERTA!!!! VAZAMENTO DE GÁS DETECTADO!!!!");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("VAZAMENTO GAS");
      lcd.setCursor(4,1);
      lcd.print("DETECTADO");
      for (int repetir = 1; repetir <=20; repetir++)
      {
        for (int x = 180; x > 0; x--)
        {
          float sen;
          int f;
            
          sen = (sin(x * 3.1416 / 180));
            
          f = 500 + (int(sen * 1000));
          tone(BUZZER, f);                                              // Envia a frequência do som para o BUZZER
          delay(2);
          }
      noTone(BUZZER);                                                  // Desliga buzzer
      digitalWrite(BUZZER, HIGH);
      
      digitalWrite(LEDB1, LOW);                                        // Apaga todas as luzes como proteção a explosão
      digitalWrite(LEDB2, LOW);
      digitalWrite(LEDB3, LOW);
      digitalWrite(LEDB4, LOW);
      digitalWrite(LEDB5, LOW);
      digitalWrite(LEDV1, LOW);
      digitalWrite(LEDV2, LOW);
      digitalWrite(LEDV3, LOW);
      digitalWrite(LEDV4, LOW);
      digitalWrite(LEDV5, LOW);

      motor.write(90);                                                // Abre o portão para facilitar a saída
        }
     lcd.clear();         
    }
  }
  }

/*##################################################################################################################################################################*/

const unsigned long periodo_LDR = 2000;
unsigned long tempo_LDR = millis();

void jardim(unsigned long tempo_atual)
{
  if (tempo_atual - tempo_LDR > periodo_LDR)
  {
    tempo_LDR = tempo_atual;
    int valor_LDR = analogRead(LDR);
    //Serial.print("Luz: ");                                         // Usei para configurar a intensidade da luz e assim determinar em qual valor ligar ou desligar 
    //Serial.println(valor_LDR);                                     // os LEDs do jardim

    if (valor_LDR < nivel_de_luz)
    {
      digitalWrite(LEDV1, HIGH);
      digitalWrite(LEDV2, HIGH);
      digitalWrite(LEDV3, HIGH);
    }
    else
    {
      digitalWrite(LEDV1, LOW);
      digitalWrite(LEDV2, LOW);
      digitalWrite(LEDV3, LOW);
    }
  }
}

/*##################################################################################################################################################################*/

const unsigned long periodo_DHT = 3000;
unsigned long tempo_DHT = millis();

void sensor_temperatura_umidade(unsigned long tempo_atual)
{
  if (tempo_atual - tempo_DHT > periodo_DHT)
  {
    tempo_DHT = tempo_atual;

    float u = dht.readHumidity();                                    // Grava a leitura de umidade em "u"
    float t = dht.readTemperature();                                 // Grava a leitura da temperatura em "t"

    if (isnan(t) || isnan(u))                                        // Verifica se o sensor retorna algo, senão tem algo errado
    {
      //Serial.println("Falha na leitura do DHT");
      
    }
    else                                                             // Configra para mostrar os valores no LCD DISPLAY 16x2
    {
      lcd.setCursor(0,1);                                            // Seta o cursor na coluna 0 e linha 2
      lcd.print("U: ");
      lcd.print(u);  
      lcd.println(" %t");
 
      lcd.setCursor(8,1);                                            // Seta o cursor na coluna 8 e linha 2 
      lcd.print("T: ");
      lcd.print(t);
      lcd.println(" *C");
      delay(100);                                                    // Faz a varredura a cada 100 ms
    }
  }
}

/*##################################################################################################################################################################*/

/* Função que é executada assim que o arduino é energizado */
void loop()
{
  unsigned long meu_tempo_atual = millis();

  acender_luz();

  sensor_temperatura_umidade(meu_tempo_atual);

  sensor_movimento(meu_tempo_atual);

  sensor_gas(meu_tempo_atual);

  jardim(meu_tempo_atual);
}

/*##################################################################################################################################################################*/
