# Concepção

O projeto tem como objetivo aplicar os conceitos de domótica de forma a
automatizar uma residência. Para que tenhamos êxito na empreitada alguns requisitos
mínimos devem ser atendidos.

Devemos ser capazes de controlar a iluminação de cômodos,
feita através de LEDS, de forma remota. É necessário também ter acesso às medições feitas
por 2 tipos de sensores, de presença e de gás. E por fim seremos capazes de controlar
um portão eletrônico.

A fim de facilitar a implementação do projeto, utlizaremos uma maquete para testar as funcionalidades.

A integração destas funcionalidades será feita através da plataforma Arduino.
Ele será o responsável pela aquisição dos dados emitidos pelos sensores e por controlar
o acionamento ou não, da iluminação ou do portão. A interface de interação entre
o usuário e o Arduino se dará em primeiro momento pelo computador, havendo tempo hábil pode-se estudar uma interface através do smartphone.
	
  Sobre a residência a ser automatizada, optou-se por uma simples. A mesma possui
um quarto, um banheiro, uma cozinha e uma sala. Temos ainda um quintal com jardim, e
uma garagem. Sobre a disposição dos cômodos, os mesmos podem ser melhor visualizados na planta.
	
  Todos os cômodos possuem uma lâmpada de LED, incluindo o jardim no quintal. 
  O sensor de gás esta presente na cozinha, enquanto o sensor de presença esta nos fundos.


![figura 1 - Planta baixa da residência.](https://github.com/luiz-sene/ProjetoIntegradorII/blob/main/imagens/planta_legenda_2.png)

Na imagem acima, representando o domicilio podemos notar retângulos coloridos. Cada um desses retângulos 
simboliza a localização de  algo a ser implementado. Segue a legenda.

- ![#ffffff](https://via.placeholder.com/15/ffffff/000000?text=+)  - **Lâmpadas de LED**
- ![#964B00](https://via.placeholder.com/15/964B00/000000?text=+)  - **Sensor de movimento**
- ![#FFB6C1](https://via.placeholder.com/15/FFB6C1/000000?text=+) -  **Sensor de gás**
- ![#FF0000](https://via.placeholder.com/15/FF0000/000000?text=+) -  **Servomotor**
