#include "data.h"

int* sort_animals(int *arr, int len) {
    // cria uma cópia da array de entrada
    int *sorted_arr = malloc(len * sizeof(int));
    memcpy(sorted_arr, arr, len * sizeof(int));

    // ordena a array em ordem decrescente
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (sorted_arr[j] > sorted_arr[i]) {
                int temp = sorted_arr[i];
                sorted_arr[i] = sorted_arr[j];
                sorted_arr[j] = temp;
            }
        }
    }

    // cria uma nova array para armazenar a posição de cada elemento na array ordenada
    int *pos_arr = malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) {
        pos_arr[i] = -1; // valor inicial, para identificar elementos que não foram encontrados
    }

    // preenche a nova array com as posições de cada elemento na array ordenada
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (arr[i] == sorted_arr[j] && pos_arr[j] == -1) {
                pos_arr[j] = i;
                break;
            }
        }
    }

    // libera a memória da array ordenada e retorna a nova array de posições
    free(sorted_arr);
    return pos_arr;
}

Animal* criar_animais(int tipo, int quantidade) {
    Animal* animais = (Animal*) malloc(quantidade * sizeof(Animal));
    if (animais == NULL) {
        fprintf(stderr,"Erro: não foi possível alocar memória para os animais\n");
        return NULL;
    }

    for (int i = 0; i < quantidade; i++) {
        animais[i].tipo = tipo;

        switch (tipo) {
            case 1: // Leão
                animais[i].qtd_alimento = 2.0;
                animais[i].horas_sono = rand() % 5 + 8;
                break;
            case 2: // Suricato
                animais[i].qtd_alimento = 0.5;
                animais[i].horas_sono = rand() % 5 + 6;
                break;
            case 3: // Avestruz
                animais[i].qtd_alimento = 1.5;
                animais[i].horas_sono = rand() % 5 + 4;
                break;
            default:
                fprintf(stderr,"Erro: tipo de animal inválido\n");
                free(animais);
                return NULL;
        }

        animais[i].id = 0;
        animais[i].vezes_comida = 0;
    }

    return animais;
}

Comedouro* cria_comedouro(int quantidade) {
    Comedouro* comedouros = calloc(quantidade, sizeof(Comedouro));
    if (comedouros == NULL) {
        fprintf(stderr, "Erro: falha na alocacao de memoria\n");
        return NULL;
    }

    for (int i = 0; i < quantidade; i++) {
        comedouros[i].tipo_alimento = 0;
        comedouros[i].capacidade_max = 0.0f;
        comedouros[i].qtd_alimento_disp = 0.0f;
        if (pthread_mutex_init(&comedouros[i].mutex, NULL) != 0) {
            fprintf(stderr, "Erro: falha na inicializacao do mutex do comedouro %d\n", i);
            free(comedouros);
            return NULL;
        }
    }

    return comedouros;
}

void inicializa_comedouro(Comedouro* comedouro, int tipo_alimento, float capacidade_max, float qtd_alimento_disp) {
    if (comedouro == NULL) {
        fprintf(stderr, "Erro: o ponteiro do comedouro eh nulo\n");
        exit(1);
    }

    comedouro->tipo_alimento = tipo_alimento;
    comedouro->capacidade_max = capacidade_max;
    comedouro->qtd_alimento_disp = qtd_alimento_disp;
    if (pthread_mutex_init(&comedouro->mutex, NULL) != 0) {
        fprintf(stderr, "Erro: falha na inicializacao do mutex do comedouro\n");
        exit(1);
    }
}

Estoque* inicializa_estoque(float carne_disp, float vegetais_disp, float frutas_disp) {
    Estoque* estoque = malloc(sizeof(Estoque));
    if (estoque == NULL) {
        fprintf(stderr, "Erro: falha na alocacao de memoria\n");
        return NULL;
    }

    estoque->carne_disp = carne_disp;
    estoque->vegetais_disp = vegetais_disp;
    estoque->frutas_disp = frutas_disp;
    if (pthread_mutex_init(&estoque->mutex, NULL) != 0) {
        fprintf(stderr, "Erro: falha na inicializacao do mutex do estoque\n");
        free(estoque);
        return NULL;
    }
    // inicializa outros tipos de alimentos

    return estoque;
}

// Inicializa uma lista de veterinários vazia
Veterinario* cria_veterinarios(int tamanho) {
    Veterinario* lista = malloc(sizeof(Veterinario) * tamanho);
    if (lista == NULL) {
        fprintf(stderr, "Erro ao alocar memória para lista de veterinários\n");
        exit(1);
    }
    for (int i = 0; i < tamanho; i++) {
        lista[i].id = i;
        lista[i].comedouros_resp = NULL;
        lista[i].num_comedouros_resp = 0;
    }
    return lista;
}

// Inicializa e aloca memória para um veterinário
void inicializa_veterinario(Veterinario* vet, int num_comedouros_resp, const int* comedouros_resp) {
    vet->num_comedouros_resp = num_comedouros_resp;
    vet->comedouros_resp = malloc(sizeof(int) * num_comedouros_resp);
    if (vet->comedouros_resp == NULL) {
        fprintf(stderr, "Erro ao alocar memória para lista de comedouros responsáveis do veterinário\n");
        exit(1);
    }
    for (int i = 0; i < num_comedouros_resp; i++) {
        vet->comedouros_resp[i] = comedouros_resp[i];
    }
}

Fornecedor* inicializa_fornecedor(float carne_entregue, float vegetais_entregues, float frutas_entregues) {
    Fornecedor* fornecedor = malloc(sizeof(Fornecedor));
    if (fornecedor == NULL) {
        fprintf(stderr, "Error: unable to allocate memory for fornecedor\n");
        return NULL;
    }
    fornecedor->carne_entregue = carne_entregue;
    fornecedor->vegetais_entregues = vegetais_entregues;
    fornecedor->frutas_entregues = frutas_entregues;
    // initialize other types of delivered food
    return fornecedor;
}

Zoologico* cria_zoologico(int num_leoes, int num_suricatos, int num_avestruses, float capacidade_max_comedouro, float carne_inicial, float vegetais_iniciais, float frutas_iniciais, int vet_padrao) {
    Zoologico *zoo = NULL;

    zoo = (Zoologico*) malloc(sizeof (Zoologico));
    if(zoo == NULL){
        fprintf(stderr,"Erro: não foi possível alocar memória para os animais\n");
        exit(1);
    }

    // Inicializa os animais
    zoo->animais = (Animal*) malloc((num_leoes + num_suricatos + num_avestruses) * sizeof(Animal));
    if (zoo->animais == NULL) {
        fprintf(stderr,"Erro: não foi possível alocar memória para os animais\n");
        exit(1);
    }
    zoo->num_animais = num_leoes + num_suricatos + num_avestruses;

    Animal* leoes = criar_animais(1, num_leoes);
    Animal* suricatos = criar_animais(2, num_suricatos);
    Animal* avestruzes = criar_animais(3, num_avestruses);

    // Concatena os animais criados em uma única lista de animais
    for (int i = 0; i < num_leoes; i++) {
        zoo->animais[i] = leoes[i];
        zoo->animais[i].id = i;
    }
    for (int i = 0; i < num_suricatos; i++) {
        zoo->animais[num_leoes + i] = suricatos[i];
        zoo->animais[num_leoes + i].id = num_leoes + i;
    }
    for (int i = 0; i < num_avestruses; i++) {
        zoo->animais[num_leoes + num_suricatos + i] = avestruzes[i];
        zoo->animais[num_leoes + num_suricatos + i].id = num_leoes + num_suricatos + i;
    }

    free(leoes);
    free(suricatos);
    free(avestruzes);

    // Inicializa os comedouros
    zoo->num_comedouros = 3;
    zoo->comedouros = cria_comedouro(zoo->num_comedouros);
    if (zoo->comedouros == NULL) {
        fprintf(stderr, "Erro: falha na alocacao de memoria para os comedouros\n");
        exit(1);
    }
    for (int i = 0; i < zoo->num_comedouros; i++) {
        inicializa_comedouro(&(zoo->comedouros[i]), i, capacidade_max_comedouro, 30.0f);
    }

    // Inicializa o estoque
    zoo->estoque = inicializa_estoque(carne_inicial, vegetais_iniciais, frutas_iniciais);

    if (zoo->estoque == NULL) {
        fprintf(stderr, "Erro: falha na alocacao de memoria\n");
        exit(1);
    }

    // Inicializa os veterinarios
    int num_veterinarios = 0;

    if(vet_padrao){
        num_veterinarios = 2;
    }else{
        num_veterinarios = 3;
    }

    Veterinario* veterinarios = cria_veterinarios(num_veterinarios);
    if (veterinarios == NULL) {
        fprintf(stderr, "Erro: falha na alocacao de memoria\n");
        exit(1);
    }

    zoo->num_veterinarios = num_veterinarios;

    int tempArr[] = {num_leoes, num_suricatos, num_avestruses};
    int *pos = sort_animals(tempArr, 3);

    if(vet_padrao){
        int temp[2] = {pos[0], pos[1]};
        inicializa_veterinario(&veterinarios[0], 2, temp);
        int temp2[1] = {pos[2]};
        inicializa_veterinario(&veterinarios[1], 1, temp2);
    }else{
        int temp[1] = {0};
        inicializa_veterinario(&veterinarios[0], 1, temp);
        int temp2[1] = {1};
        inicializa_veterinario(&veterinarios[1], 1, temp2);
        int temp3[1] = {2};
        inicializa_veterinario(&veterinarios[2], 1, temp3);
    }

    free(pos);

    zoo->veterinarios = veterinarios;

    // Inicializa o fornecedor
    Fornecedor* fornecedor = inicializa_fornecedor(0, 0, 0);
    if (fornecedor == NULL) {
        fprintf(stderr, "Erro: não foi possível inicializar o fornecedor\n");
        exit(1);
    }
    zoo->fornecedor = fornecedor;

    return zoo;
}

void free_zoo(Zoologico* zoo) {
    // Free memory for the animals
    for (int i = 0; i < zoo->num_animais; i++) {
        free(&(zoo->animais[i]));
    }
    free(zoo->animais);

    // Free memory for the comedouros
    for (int i = 0; i < zoo->num_comedouros; i++) {
        free(&(zoo->comedouros[i]));
    }
    free(zoo->comedouros);

    // Free memory for the veterinarios
    for (int i = 0; i < zoo->num_veterinarios; i++) {
        free(zoo->veterinarios[i].comedouros_resp);
        free(&(zoo->veterinarios[i]));
    }
    free(zoo->veterinarios);

    // Free memory for the fornecedor
    free(zoo->fornecedor);

    // Free memory for the estoque
    free(zoo->estoque);
}

void print_zoo(Zoologico* zoo) {
    printf("=== Zoologico ===\n");

    // Imprime informações dos animais
    printf("Animais:\n");
    for (int i = 0; i < zoo->num_animais; i++) {
        Animal animal = zoo->animais[i];
        printf(" - ID: %d | Tipo: ", animal.id);
        switch (animal.tipo) {
            case 1:
                printf("Leao\n");
                break;
            case 2:
                printf("Suricato\n");
                break;
            case 3:
                printf("Avestruz\n");
                break;
            default:
                printf("%d\n", animal.tipo);
        }
        printf(" | Quantidade de alimento: %.2f | Vezes alimentado: %d | Horas de sono: %d\n", animal.qtd_alimento, animal.vezes_comida, animal.horas_sono);
    }

    // Imprime informações dos comedouros
    printf("Comedouros:\n");
    for (int i = 0; i < zoo->num_comedouros; i++) {
        Comedouro comedouro = zoo->comedouros[i];
        printf(" - Tipo de alimento: %d | Quantidade de alimento disponivel: %.2f | Capacidade maxima: %.2f\n", comedouro.tipo_alimento, comedouro.qtd_alimento_disp, comedouro.capacidade_max);
    }

    // Imprime informações do estoque
    printf("Estoque:\n");
    printf(" - Carne disponivel: %.2f\n", zoo->estoque->carne_disp);
    printf(" - Vegetais disponiveis: %.2f\n", zoo->estoque->vegetais_disp);
    printf(" - Frutas disponiveis: %.2f\n", zoo->estoque->frutas_disp);
    // outros tipos de alimentos

    // Imprime informações dos veterinários
    printf("Veterinarios:\n");
    for (int i = 0; i < zoo->num_veterinarios; i++) {
        Veterinario vet = zoo->veterinarios[i];
        printf(" - ID: %d | Comedouros responsaveis:", vet.id);
        for (int j = 0; j < vet.num_comedouros_resp; j++) {
            printf(" %d", vet.comedouros_resp[j]);
        }
        printf("\n");
    }

    // Imprime informações do fornecedor
    printf("Fornecedor:\n");
    printf(" - Carne entregue: %.2f\n", zoo->fornecedor->carne_entregue);
    printf(" - Vegetais entregues: %.2f\n", zoo->fornecedor->vegetais_entregues);
    printf(" - Frutas entregues: %.2f\n", zoo->fornecedor->frutas_entregues);
    // outros tipos de alimentos
}
