# Operação

Tendo em vista que o projeto da maquete residencial automatizada já foi concluido durante as etapas anteriores, nesta ultima etapa temos como o objetivo de operar, ou seja utilizar o nosso projeto, verificando se os objetivos foram cumpridos e identificando falhas e sugestões de melhorias.

## Como utilizar?

O Arduino deve ser conectado ao computador por meio de um USB e é necessário ter o software "IDE Arduino" instalado. 

Para a comunicação do usuário para o Arduino e do Arduino para o usuário, o monitor seral é utilizado, é por ele que será enviado os comandos das funções da casa e também recebido as informações necessárias.

![](./imagens/Monitor%20Serial.JPG)

## Menu
Para realizar as ações desejadas é disponibilizado um menu no monitor serial, que pode ser acessado novamente enviando o caracter "m".
~~~
Tecla '1': Acende/apaga a luz da entrada
Tecla '2': Acende/apaga a luz da sala/cozinha
Tecla '3': Acende/apaga a luz do quarto 1
Tecla '4': Acende/apaga a luz do quarto 2
Tecla '5': Acende/apaga a luz do banheiro 1
Tecla '6': Acende/apaga a luz do banheiro 2
Tecla '7': Abre/fecha o portão eletronico
Tecla 'm': Mostra o menu de funções da casa
~~~

## Funções automáticas

Caso seja detectado algum movimento na parte frontal da casa, a luz externa é acionada e uma mensagem é enviada ao monitor serial para informar sobre o movimento.

Caso seja detectado gás/fumaça o portão eletrônico é aberto e uma mensagem é enviada ao monitor serial para informar sobre o movimento.

[Video demonstrando a operação](https://www.youtube.com/watch?v=gDG_pcwu0pY&ab_channel=StanislauKaszubowski)

## Conclusões

Todas as funções funcionaram de acordo com o esperado e a utilização da maquete é de facil entendimento.

Ficaram algumas sugestões podem ser feitas em projetos posteriores: 

A utilização de um buzzer, que poderia ser utilizado para um sistema de alarme contra o vazamento de gás e contra intrusos, tendo em vista os componentes já utilizados.

Comunicação Wireless do computador, celular ou tablet com o Arduino poderia ser implementada já que é um ponto amplamente utilizado na domótica isso deixaria o projeto mais fácil de ser utilizado por algum usuário e tornaria o projeto mais funcional.
