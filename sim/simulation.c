#include "simulation.h"

// Variável global que indica se a simulação deve continuar ou não
volatile sig_atomic_t should_stop = 0;

volatile sig_atomic_t should_fill_stock = 0;

// Função que trata o sinal de encerramento
void handle_signal(int signum) {
    should_stop = 1;
}

void handle_fill_stock_signal(int signum) {
    should_fill_stock = 1;
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
int verifica_comedouros(const int *arr, int count, Comedouro *comedouros){
    int i;
    for (i = 0; i < count; i++) {
        int pos = arr[i];
        Comedouro *com = &comedouros[pos];
        pthread_mutex_lock(&com->mutex);
        if (com->qtd_alimento_disp < com->capacidade_max) {
            pthread_mutex_unlock(&com->mutex);
            return pos;
        }
        pthread_mutex_unlock(&com->mutex);
    }
    return -1;
}

void* fornecedor_thread(Fornecedor *fornecedor, Estoque *estoque) {
    while(!should_stop) {
        if(should_fill_stock) {
            printf("Fornecedor preenchendo estoque...\n");

            // Bloquear o estoque para evitar acesso concorrente
            pthread_mutex_lock(&estoque->mutex);

            float carne = 30 - estoque->carne_disp;
            float vegetais = 30 - estoque->vegetais_disp;
            float frutas = 30 - estoque->frutas_disp;

            estoque->carne_disp += carne;
            estoque->vegetais_disp += vegetais;
            estoque->frutas_disp += frutas;
            // preencher outros tipos de alimentos
            fornecedor->carne_entregue += carne;
            fornecedor->vegetais_entregues += vegetais;
            fornecedor->frutas_entregues += frutas;
            // entregar outros tipos de alimentos

            // Desbloquear o estoque após preenchido
            pthread_mutex_unlock(&estoque->mutex);

            printf("Fornecedor entregou 30 unidades de cada alimento.\n");

            should_fill_stock = 0;
        }

        sleep(1); // 1s
    }

    printf("Fornecedor encerrado.\n");

    return NULL;
}

void* preenche_comedouro(Comedouro *comedouro, Estoque *estoque) {
    pthread_mutex_lock(&comedouro->mutex);
    pthread_mutex_lock(&estoque->mutex);

    switch (comedouro->tipo_alimento) {
        case 1: // Carne
            if (estoque->carne_disp >= comedouro->capacidade_max - comedouro->qtd_alimento_disp) {
                estoque->carne_disp -= (comedouro->capacidade_max - comedouro->qtd_alimento_disp);
                comedouro->qtd_alimento_disp = comedouro->capacidade_max;
                printf("Comedouro %d preenchido com carne.\n", comedouro->tipo_alimento);
            } else {
                should_fill_stock = 1;
            }
            break;
        case 2: // Vegetais
            if (estoque->vegetais_disp >= comedouro->capacidade_max - comedouro->qtd_alimento_disp) {
                estoque->vegetais_disp -= (comedouro->capacidade_max - comedouro->qtd_alimento_disp);
                comedouro->qtd_alimento_disp = comedouro->capacidade_max;
                printf("Comedouro %d preenchido com vegetais.\n", comedouro->tipo_alimento);
            } else {
                should_fill_stock = 1;
            }
            break;
        case 3: // Frutas
            if (estoque->frutas_disp >= comedouro->capacidade_max - comedouro->qtd_alimento_disp) {
                estoque->frutas_disp -= (comedouro->capacidade_max - comedouro->qtd_alimento_disp);
                comedouro->qtd_alimento_disp = comedouro->capacidade_max;
                printf("Comedouro %d preenchido com frutas.\n", comedouro->tipo_alimento);
            } else {
                should_fill_stock = 1;
            }
            break;
            // outros tipos de alimentos
    }

    pthread_mutex_unlock(&estoque->mutex);
    pthread_mutex_unlock(&comedouro->mutex);

    return NULL;
}
void* veterinario_thread(void* arg, int vet_id){
    Zoologico *zoo = (Zoologico*) arg;
    // Conversão do argumento genérico para um ponteiro para Veterinario
    Veterinario *vet = &zoo->veterinarios[vet_id];
    Comedouro *comedouros = zoo->comedouros;

    // Loop para simular o ciclo do Veterinario, que será interrompido caso a variável should_stop seja alterada
    while (!should_stop) {
        // Verifica se tem algum comedouro vazio
        int pos = verifica_comedouros(vet->comedouros_resp, vet->num_comedouros_resp, comedouros);
        if(pos != -1){
            //Tenta solicitar o preenchimento do comedouro
            preenche_comedouro(&comedouros[pos], zoo->estoque);
        }

        // Bloqueia a thread por 1 segundo antes de reiniciar o ciclo
        sleep(1);
    }

    // A função foi encerrada por um sinal externo
    printf("Veterinario %d encerrado por sinal externo.\n", vet->id);

    // Não é necessário retornar nenhum valor, já que a função foi interrompida por um sinal externo
    return NULL;
}