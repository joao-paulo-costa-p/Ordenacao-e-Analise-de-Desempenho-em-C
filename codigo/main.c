#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Definição do tamanho máximo para o RGM
#define MAX_RGM_LEN 15

// Variável global para contagem de passos (comparações e trocas)
long long steps = 0;

// Macros para contagem de operações-chave
#define COUNT_CMP() (steps++) // Conta uma comparação
#define COUNT_SWAP() (steps++) // Conta uma troca

// --- Funções Auxiliares ---

/**
 * Troca os valores de dois inteiros.
 */
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
    COUNT_SWAP(); 
}

// --- Algoritmo de Ordenação ---

/**
 * Implementação do Bubble Sort.
 */
void bubbleSort(int arr[], int n) {
    int i, j;
    int swapped; 
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            COUNT_CMP(); 
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
}

// --- Funções de Benchmark e Setup ---

/**
 * Gera um vetor de inteiros aleatórios.
 */
int* generateRandomArray(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000; 
    }
    return arr;
}

/**
 * Converte a string do RGM em um vetor de inteiros (dígitos).
 */
int* rgmToArray(const char* rgm_str, int* size) {
    *size = strlen(rgm_str);
    int* arr = (int*)malloc(*size * sizeof(int));
    if (arr == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < *size; i++) {
        // Verifica se o caractere é um dígito
        if (rgm_str[i] >= '0' && rgm_str[i] <= '9') {
            arr[i] = rgm_str[i] - '0'; 
        } else {
            // Trata caracteres não numéricos ou espaços
            fprintf(stderr, "Aviso: Caractere não numérico ('%c') encontrado e ignorado.\n", rgm_str[i]);
        }
    }
    return arr;
}

/**
 * Copia o conteúdo de um vetor para outro.
 */
void copyArray(int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

/**
 * Função principal de execução e coleta de métricas.
 */
void run_benchmark(int arr[], int N, const char* case_name, const char* method_name) {
    int* temp_arr = (int*)malloc(N * sizeof(int));
    if (temp_arr == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    copyArray(arr, temp_arr, N); 

    steps = 0; // Zera o contador de passos
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    bubbleSort(temp_arr, N);
    end = clock();

    cpu_time_used = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC; // Tempo em milissegundos

    // SAÍDA DE DADOS: Imprime a linha CSV
    printf("%s,%d,%s,%lld,%.3f\n", method_name, N, case_name, steps, cpu_time_used);

    // Saída adicional para o RGM (para visualização)
    if (strcmp(case_name, "rgm") == 0) {
        printf("RGM Original: ");
        for (int i = 0; i < N; i++) {
            // Note: O array original não é salvo, mas os valores são os do RGM
            printf("%d%s", arr[i], (i == N - 1 ? "" : " "));
        }
        printf("\nRGM Ordenado: ");
        for (int i = 0; i < N; i++) {
            printf("%d%s", temp_arr[i], (i == N - 1 ? "" : " "));
        }
        printf("\n");
    }

    free(temp_arr);
}

// --- Main ---
int main() {
    // 1. ENTRADA DE DADOS: Leitura do RGM 
    char my_rgm_str[MAX_RGM_LEN];
    printf(">> Digite seu RGM (apenas números): ");
    if (fgets(my_rgm_str, MAX_RGM_LEN, stdin) == NULL) {
        fprintf(stderr, "Erro na leitura do RGM.\n");
        return 1;
    }
    // Remove a nova linha ('\n') se presente
    my_rgm_str[strcspn(my_rgm_str, "\n")] = 0; 

    // Define os tamanhos dos vetores para benchmark
    int N_sizes[] = {100, 1000, 5000, 10000}; 
    int num_sizes = sizeof(N_sizes) / sizeof(N_sizes[0]);

    srand(time(NULL)); // Inicializa a semente para números aleatórios

    printf("\n---------------------------------------------\n");
    printf("Resultados do Benchmark de Bubble Sort\n");
    printf("---------------------------------------------\n");
    
    // SAÍDA DE DADOS: Cabeçalho CSV
    printf("metodo, N, caso, passos, tempo\n");

    // 1. Entrada A (RGM)
    int rgm_size;
    int* rgm_arr = rgmToArray(my_rgm_str, &rgm_size);
    if (rgm_size > 0) {
        run_benchmark(rgm_arr, rgm_size, "rgm", "bubble");
    } else {
        printf("// rgm, 0, rgm, 0, 0.000\n"); // Caso o RGM seja vazio
    }
    free(rgm_arr);

    // 2. Entradas B (Benchmark Aleatório)
    for (int i = 0; i < num_sizes; i++) {
        int N = N_sizes[i];
        int* random_arr = generateRandomArray(N);
        run_benchmark(random_arr, N, "aleatorio", "bubble");
        free(random_arr);
    }

    // 3. Teste Melhor Caso (Ordenado)
    int N_test_ordered = 10000;
    int* ordered_arr = (int*)malloc(N_test_ordered * sizeof(int));
    for (int i = 0; i < N_test_ordered; i++) {
        ordered_arr[i] = i; 
    }
    run_benchmark(ordered_arr, N_test_ordered, "melhor caso ordenado", "bubble");
    free(ordered_arr);

    // 4. Teste Pior Caso (Reverso)
    int N_test_reverse = 10000;
    int* reverse_arr = (int*)malloc(N_test_reverse * sizeof(int));
    for (int i = 0; i < N_test_reverse; i++) {
        reverse_arr[i] = N_test_reverse - i; 
    }
    run_benchmark(reverse_arr, N_test_reverse, "pior caso reverso", "bubble");
    free(reverse_arr);

    return 0;
}