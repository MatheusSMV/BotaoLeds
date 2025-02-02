# Controle de LEDs com Temporização - Raspberry Pi Pico

Este projeto utiliza o Raspberry Pi Pico - BitDogLab para controlar três LEDs (verde, azul e vermelho) com base em um temporizador. O código foi desenvolvido para ligar os LEDs ao pressionar um botão e desligá-los de forma sequencial após determinados períodos de tempo (3, 6 e 9 segundos).

## Objetivo

O objetivo deste código é:

1. Ligar os LEDs (verde, azul e vermelho) quando o botão é pressionado.
2. Desligar cada LED em intervalos específicos:
    - LED verde: Desliga após 3 segundos.
    - LED azul: Desliga após 6 segundos.
    - LED vermelho: Desliga após 9 segundos.
3. Exibir o tempo decorrido no console a cada segundo enquanto a rotina está ativa.

## Hardware Requerido

- **Placa BitDogLab - EmbarcaTech**.

### Conexões

- **LED verde**: Pino GPIO 11.
- **LED azul**: Pino GPIO 12.
- **LED vermelho**: Pino GPIO 13.
- **Botão**: Pino GPIO 5.

## Descrição do Código

### Inicialização e Configuração

- O código começa com a inicialização da comunicação serial e configuração dos pinos GPIO para os LEDs e o botão.
- O botão é configurado para ter um resistor de pull-up, garantindo que seu valor seja alto quando não pressionado.
- Cada LED é configurado como uma saída digital.

### Rotina de Controle de LEDs

1. **Pressionar o Botão**: Quando o botão é pressionado, todos os LEDs são ligados, e a rotina de controle dos LEDs é iniciada.
   
2. **Desligamento Sequencial dos LEDs**:
    - O LED verde é desligado após 3 segundos.
    - O LED azul é desligado após 6 segundos.
    - O LED vermelho é desligado após 9 segundos.
   
3. **Exibição do Tempo Decorrido**: Enquanto a rotina está ativa, o tempo decorrido desde o início da rotina é exibido no console a cada segundo.

### Funções de Callback

As funções de callback são usadas para agendar o desligamento dos LEDs após os intervalos de tempo especificados:
- `turn_off_green_callback`: Desliga o LED verde após 3 segundos.
- `turn_off_blue_callback`: Desliga o LED azul após 6 segundos.
- `turn_off_red_callback`: Desliga o LED vermelho após 9 segundos.

Cada uma dessas funções é chamada após o respectivo intervalo de tempo usando `add_alarm_in_ms()`.

### Debounce do Botão

A leitura do botão é protegida por um pequeno atraso (debounce) para evitar leituras incorretas devido a ruídos ou múltiplos registros do botão sendo pressionado.

### Fluxo Principal

- O fluxo principal do programa verifica constantemente o estado do botão e executa a rotina de controle de LEDs quando o botão é pressionado.
- A cada segundo, o tempo decorrido desde o início da rotina é impresso no console.

## Como Executar

1. **Carregue o código** na placa BitDogLab usando a interface de programação - Visual Studio Code.
3. **Abra o monitor serial** para visualizar as mensagens de status e o tempo decorrido.
4. **Pressione o botão** para iniciar a rotina. Os LEDs serão desligados sequencialmente após 3, 6 e 9 segundos.

## Dependências

Este projeto utiliza as bibliotecas padrão do Raspberry Pi Pico:
- `pico/stdlib.h` para controle de GPIO e comunicação serial.
- `pico/time.h` para manipulação de tempos absolutos e agendamento de alarmes.

## Exemplo de Saída no Console

---- Opened the serial port COM6 ----
Rotina iniciada. Todos os LEDs ligados.
1 segundo(s) se passaram.
2 segundo(s) se passaram.
3 segundo(s) se passaram.
LED verde desligado.
4 segundo(s) se passaram.
5 segundo(s) se passaram.
6 segundo(s) se passaram.
LED azul desligado.
7 segundo(s) se passaram.
8 segundo(s) se passaram.
9 segundo(s) se passaram.
LED vermelho desligado.
Rotina iniciada. Todos os LEDs ligados.
1 segundo(s) se passaram.
2 segundo(s) se passaram.
3 segundo(s) se passaram.
LED verde desligado.
4 segundo(s) se passaram.
5 segundo(s) se passaram.
6 segundo(s) se passaram.
LED azul desligado.
7 segundo(s) se passaram.
8 segundo(s) se passaram.
9 segundo(s) se passaram.
LED vermelho desligado.

## Autor

Matheus Santos Souza

## Código Base

Professor Ricardo Menezes Prates

## Código Base Obtenção
Código obtido do GitHub disponibilizado pelo própio docente: [GitHubProfessorRicardo](https://github.com/rmprates84/alarm_botao.git)

