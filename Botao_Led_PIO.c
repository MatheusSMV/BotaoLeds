#include <stdio.h> //Inclui a biblioteca padrão de entrada e saída do C.
#include "pico/stdlib.h" //Inclui a biblioteca padrão do Raspberry Pi Pico, que fornece funções para controlar GPIO, temporização e comunicação serial.
#include "pico/time.h" //Inclui a biblioteca de tempo do Pico.

//Define constantes para os pinos GPIO que serão usados no código.
#define LED_GREEN_PIN 11 //O LED verde está conectado ao pino GPIO 11.
#define LED_BLUE_PIN 12 //O LED azul está conectado ao pino GPIO 12.       //De acordo com a placa BitDogLab.
#define LED_RED_PIN 13 //O LED vermelho está conectado ao pino GPIO 13.
#define BUTTON_PIN 5 // O botão está conectado ao pino GPIO 5.

bool routine_active = false; //  Uma variável booleana que indica se a rotina de controle dos LEDs está ativa ou não. //False - Rotina não começou.
absolute_time_t start_time;  // Armazena o tempo de início da rotina - Usado para trabalhar com funções de tempo do Pico.

//Função para exibir o tempo decorrido.
void print_elapsed_time() {
    int64_t elapsed_time = absolute_time_diff_us(start_time, get_absolute_time()) / 1000000; //Calcula a diferença de tempo entre o momento atual e o tempo de início - Transforma em segundos.
    printf("%lld segundo(s) se passaram.\n", elapsed_time + 1); //Exibe o tempo decorrido no console - Começa em 1 segundo o primeiro "loop" da rotina.
}

//Função de callback para desligar o LED verde após 3 segundos
int64_t turn_off_green_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_GREEN_PIN, false); //Desliga o LED verde, configurando o pino GPIO 11 para nível baixo - Lembrando que inicia em nível alto.
    printf("LED verde desligado.\n"); //Exibe uma mensagem no serial indicando que o LED verde foi desligado.  //Obs: Separar foi a solução para manter os tempos corretos na rotina.
    return 0; //Indica que o alarme não deve ser repetido.
}

//Função de callback para desligar o LED azul após 6 segundos.
int64_t turn_off_blue_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_BLUE_PIN, false); //Desliga o LED azul, configurando o pino GPIO 11 para nível baixo - Lembrando que inicia em nível alto.
    printf("LED azul desligado.\n"); //Exibe uma mensagem no serial indicando que o LED verde foi desligado. //Obs: Separar foi a solução para manter os tempos corretos na rotina.
    return 0; //Indica que o alarme não deve ser repetido.
}

//Função de callback para desligar o LED vermelho após 9 segundos.
int64_t turn_off_red_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_RED_PIN, false); //Desliga o LED vermelho, configurando o pino GPIO 11 para nível baixo - Lembrando que inicia em nível alto.
    routine_active = false;       //Marca o fim da rotina, permitindo que o botão seja pressionado novamente para iniciar uma nova execução.
    printf("LED vermelho desligado.\n"); //Exibe uma mensagem no serial indicando que o LED vermelho foi desligado.
    return 0; //Indica que o alarme não deve ser repetido.
}

int main() {
    stdio_init_all(); //Inicializa a comunicação serial.

    //Configura os pinos dos LEDs como saída.
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

    gpio_init(LED_BLUE_PIN);                                            //Led é saída e o botão a entrada.
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);

    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);

    //Configura o pino do botão como entrada com pull-up.
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    while (true) { //Loop infinito que mantém o programa em execução.
        if (gpio_get(BUTTON_PIN) == 0 && !routine_active) { //Verifica se o botão foi pressionado (nível baixo) e Garante que a rotina só seja iniciada se não estiver ativa.
            sleep_ms(50); //Debounce para evitar leituras errôneas do botão.
            if (gpio_get(BUTTON_PIN) == 0) {
                //Liga todos os LEDs.
                gpio_put(LED_GREEN_PIN, true); 
                gpio_put(LED_BLUE_PIN, true);
                gpio_put(LED_RED_PIN, true);

                //Marca que a rotina está ativa.
                routine_active = true;

                //Armazena o tempo de início da rotina.
                start_time = get_absolute_time();

                //Agenda o desligamento do LED verde após 3 segundos.
                add_alarm_in_ms(3000, turn_off_green_callback, NULL, false);

                //Agenda o desligamento do LED azul após 6 segundos.
                add_alarm_in_ms(6000, turn_off_blue_callback, NULL, false);

                //Agenda o desligamento do LED vermelho após 9 segundos.
                add_alarm_in_ms(9000, turn_off_red_callback, NULL, false);

                printf("Rotina iniciada. Todos os LEDs ligados.\n"); //Exibe uma mensagem no console indicando que a rotina foi iniciada.
            }
        }

        //A cada segundo, exibe o tempo decorrido no console.
        if (routine_active) {
            static absolute_time_t last_print_time = 0;
            if (absolute_time_diff_us(last_print_time, get_absolute_time()) >= 1000000) {
                print_elapsed_time();
                last_print_time = get_absolute_time();
            }
        }

        sleep_ms(10); //Pequena pausa para reduzir o uso da CPU. - Wokwi integrado ao VSCode travando isso resolve.
    }

    return 0;
}