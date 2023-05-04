#include "simulation.h"

// Variável global que indica se a simulação deve continuar ou não
volatile sig_atomic_t should_stop = 0;

// Função que trata o sinal de encerramento
void handle_signal(int signum) {
    should_stop = 1;
}

// Variável global que representa o mutex para controle de acesso aos animais
pthread_mutex_t mutex_animais = PTHREAD_MUTEX_INITIALIZER;

void exibir_animal(Animal* animal) {
    // Lock no mutex antes de acessar o animal
    pthread_mutex_lock(&mutex_animais);

    // Impressão das informações do animal
    printf("Animal %d:\n", animal->id);
    printf("Tipo: %d\n", animal->tipo);
    printf("Quantidade de alimento ingerido: %.2f\n", animal->qtd_alimento);
    printf("Número de vezes alimentado: %d\n", animal->vezes_comida);
    printf("Horas de sono: %d\n", animal->horas_sono);

    // Unlock no mutex após acessar o animal
    pthread_mutex_unlock(&mutex_animais);
}

void alimentar_animal(Animal* animal, Comedouro* comedouro) {
    // Bloqueia o acesso de outros animais ao comedouro enquanto este animal estiver comendo
    pthread_mutex_lock(&(comedouro->mutex));

    if (comedouro->qtd_alimento_disp < animal->qtd_alimento) {
        printf("Comedouro vazio! Animal não pôde ser alimentado.\n");
    } else {
        // Remove a quantidade de alimento consumida pelo animal do comedouro
        comedouro->qtd_alimento_disp -= animal->qtd_alimento;

        // Incrementa o contador de vezes que o animal comeu
        animal->vezes_comida++;

        printf("Animal %d foi alimentado. Restam %.1f unidades de alimento no comedouro.\n",
               animal->id, comedouro->qtd_alimento_disp);
    }

    // Libera o acesso ao comedouro para outros animais
    pthread_mutex_unlock(&(comedouro->mutex));
}

void dormir_animal(Animal* animal) {
    printf("Animal %d vai dormir por %d horas\n", animal->id, animal->horas_sono);
    sleep(animal->horas_sono * 3600); // converte horas para segundos
    printf("Animal %d acordou\n", animal->id);
}

void* animal_thread(void* arg, Comedouro* comedouro) {
    // Conversão do argumento genérico para um ponteiro para Animal
    Animal* animal = (Animal*) arg;

    // Loop para simular o ciclo diário do animal, que será interrompido caso a variável should_stop seja alterada
    while (!should_stop) {
        // Etapa de exibição do animal
        exibir_animal(animal);

        // Etapa de alimentação do animal
        alimentar_animal(animal, comedouro);

        // Etapa de sono do animal
        dormir_animal(animal);

        // Bloqueia a thread por 1 segundo antes de reiniciar o ciclo
        sleep(1);
    }

    // A função foi encerrada por um sinal externo
    printf("Animal %d encerrado por sinal externo.\n", animal->id);

    // Não é necessário retornar nenhum valor, já que a função foi interrompida por um sinal externo
    return NULL;
}