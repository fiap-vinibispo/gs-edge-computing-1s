# Projeto: Medidor de Consumo de Energia

## Autores

- **Felipe Molinari RM559885**
- **Vinícius Bispo RM560188**

Este projeto foi realizado em função da Global Solution de Edge Computing do 1o semestre de Engenharia de Software da FIAP.

---

## Descrição

Este projeto tem como objetivo criar um sistema simples de medição de consumo de energia elétrica utilizando um display LCD, potenciômetros e botões conectados a um Arduino UNO. Ele permite calcular o custo de consumo de energia com base em uma taxa definida pelo usuário, simulando medições de corrente e tensão através de potenciômetros.

## Funcionalidades

- **Configuração da taxa de energia:** O usuário pode ajustar a taxa de energia (em R$/kWh) através de botões.
- **Monitoramento de consumo:** O sistema exibe em tempo real a potência consumida, energia acumulada e custo estimado.
- **Interface simples:** Utiliza um display LCD 20x4 para exibir informações e botões para interação.

---

## Componentes Necessários

- **Microcontrolador:** Arduino UNO.
- **Display LCD:** LCD 20x4 com interface I2C.
- **Potenciômetros:** 2 potenciômetros para simular valores de corrente e tensão.
- **Botões:** 3 botões (um principal e dois para ajuste).
- **Protoboard** e **fios de conexão**.

---

## Esquemático de Conexão

As conexões entre os componentes foram feitas conforme o seguinte:

### Botões
- Botão Primário (Iniciar):
  - Conectado ao pino **5** do Arduino.
- Botão de Ajuste Esquerdo ([-]):
  - Conectado ao pino **6** do Arduino.
- Botão de Ajuste Direito ([+]):
  - Conectado ao pino **3** do Arduino.

### Potenciômetros
- Potenciômetro de Corrente:
  - **SIG** conectado ao pino **A0** do Arduino.
- Potenciômetro de Tensão:
  - **SIG** conectado ao pino **A2** do Arduino.

### Display LCD
- Alimentação (**VCC** e **GND**) conectados à protoboard.
- **SDA** conectado ao pino **A4**.
- **SCL** conectado ao pino **A5**.

---

## Instruções de Uso

1. **Montagem do Circuito:**
   - Siga o esquemático de conexão fornecido acima.
   - Certifique-se de que as conexões estão firmes e corretas.

2. **Carregamento do Código:**
   - Instale a [IDE do Arduino](https://www.arduino.cc/en/software).
   - Certifique-se de ter a biblioteca `LiquidCrystal_I2C` instalada.
   - Copie e carregue o código fornecido no Arduino.

3. **Operação do Sistema:**
   - Após carregar o código, o display exibirá uma mensagem inicial com a opção para iniciar.
   - Pressione o botão principal para configurar a taxa de energia.
   - Utilize os botões de ajuste para alterar a taxa e confirme pressionando novamente o botão principal.
   - O sistema passará a monitorar o consumo em tempo real.

---

## Bibliotecas Necessárias

- **LiquidCrystal_I2C:** Para controlar o display LCD.
  - Instalação: Acesse **Ferramentas > Gerenciar Bibliotecas** na IDE do Arduino e procure por "LiquidCrystal_I2C".

---

## Requisitos do Sistema

- **Software:**
  - IDE Arduino 1.8 ou superior.
- **Hardware:**
  - Arduino UNO ou compatível.
  - Componentes mencionados na seção de "Componentes Necessários".

---

## Explicação do Código

### Estrutura Geral

- **Função `setup()`:** Configura os pinos, inicializa o display LCD e outros componentes.
- **Função `loop()`:** Controla o fluxo do programa e chama as funções principais.
- **Função `mainSystem()`:** Gerencia a navegação entre as páginas do sistema:
  - `systemOnboarding`: Tela inicial com introdução.
  - `setFee`: Ajuste da taxa de energia.
  - `feeMonitor`: Monitoramento do consumo e custo.

---

## Simulação Online

Você pode simular este projeto no Wokwi clicando [aqui](https://wokwi.com/projects/415118916606876673).

---

## Licença

Este projeto está sob a licença MIT. Sinta-se livre para usá-lo e modificá-lo conforme necessário.

---

Se precisar de mais informações ou suporte, entre em contato conosco!

---
