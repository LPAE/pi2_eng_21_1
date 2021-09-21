# Design

Tendo em vista o que foi apresentado na concepção do projeto, é necessário desenvolver uma maquete de uma casa automatizada, para que seja concluido esse objetivo seguimos para a etapa de design.

Nessa etapa será desenvolvida uma maquete eletrônica, de acordo com as funções prometidas na etapa da concepção. 
A maquete eletrônica ira mostrar as ligações de todos os componentes selecionados ao Arduino Mega 2560 e códigos teste para que sejam testados individualmente todos os sensores e atuadores utilizados. 

Tambem será apresentada uma lista de componentes utilizados, e uma breve explicação sobre o funcionamento dos componentes.
## Maquete Eletrônica
![](./imagens/image.png)
## Tabela

| Componente | Quantidade |   
| ----------------------| ---------- |
|Arduino Mega 2560| 1
| Sensor de Fumaça MQ2	 |  1
| Micro Servo SG92| 1
| Sensor de Movimento PIR | 1
| LED 	 |  6
| Resistor 330 Ohm	| 6

### Apresentação e Codigos de Teste dos Componentes

#### Arduino Mega 2560:
Utilizado para realizar controle de todos atuadores, receber os sinais dos sensores e oferecer alimentações positivas e negativas aos componentes. É o componente principal do projeto. A programção é feita através do IDE Arduino, sendo necessário selecionar o modelo de placa que será utilizado (Mega 2560) na barra de "Ferramentas" antes de carregar o codigo.

#### Sensor de Fumaça MQ2:
Utilizado para detectar um possivel vazamento de gás na cozinha (e informar para o Arduino), possui uma saída digital e outra analógica.

No MQ2 foi ajustado o potenciômetro para quando a sua saída analógica for aproximadamente 300 ou mais, que seja acionada a sua saída digital.
[Teste funcionamento MQ2](./testes/Teste_MQ2.ino)

#### Micro Servo SG92:
Vai ser controlado pelo Arduino por uma modulação de largura de pulso (PWM) para fazer o acionamento do portão de garagem da casa.
[Teste acionamento de um servo motor pelo teclado](./testes/Teste_Servo_com_teclado.ino)

#### Sensor de Movimento PIR:
Detecta a presença de algum movimento na entrada de para realizar um acionamento automático das luzes externas, e também informa o Arduino sobre o movimento.

No sensor PIR temos regulagens a serem feitas, para a etapa de teste de funcionamento destes sensores, no PIR, foi girado totalmente no sentido anti horário os potenciômetros de sensibilidade e de tempo
[Teste funcionamento PIR](./testes/Teste_PIR.ino)

#### LED:
Utilizado para fazer a iluminação da casa, que pode ser controlada remotamente (através do computador).
[Teste acionamento de um LED pelo teclado](./testes/Teste_LED_com_teclado.ino)

#### Resistor 330 Ohm:
Tem a função de limitar a corrente máxima fornecida pelos terminais de controle dos LEDs, para que não ocorra uma possivel queima do Arduino e/ou do LED.
