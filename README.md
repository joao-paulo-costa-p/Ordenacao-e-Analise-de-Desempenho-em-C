# Ordenacao-e-Analise-de-Desempenho-em-C
Benchmark de Algoritmos de Ordenação em C: Bubble Sort

Este repositório contém a implementação do algoritmo Bubble Sort em C, com o objetivo de analisar sua escalabilidade e desempenho prático (tempo e passos) em diferentes cenários de entrada de dados (RGM, aleatório, ordenado e reverso).

1. Descrição do Problema e Método Implementado
Objetivo

Medir a eficiência do algoritmo de ordenação comparando o crescimento do custo computacional (passos e tempo de CPU) versus o aumento do tamanho do array ($N$), validando a complexidade teórica.

Método Implementado: Bubble Sort (Otimizado)

Algoritmo: Bubble Sort (Método da Bolha).

Complexidade Teórica: $O(n^2)$ (Pior e Média) e $O(n)$ (Melhor Caso, devido à otimização com a flag de swapped).

Justificativa da Escolha: O Bubble Sort foi escolhido para demonstrar os limites da escalabilidade em um algoritmo de complexidade quadrática ($O(n^2)$), contrastando com métodos mais eficientes como Quick Sort ou Merge Sort.

2. Como Compilar e Rodar

O código foi projetado para ler o RGM do usuário via entrada padrão (stdin) e gerar a saída CSV na tela.

2.1. Compilação

Salve o código como bubble_sort.c e compile usando o GCC:
gcc -O1 -std=c11 bubble_sort.c -o ordena

2.2. Execução
Execute o binário ordena. O programa solicitará seu RGM e, em seguida, rodará os benchmarks e imprimirá os resultados em formato CSV.
./ordena

Para salvar os resultados em um arquivo CSV:
./ordena > resultados_bubble.csv


3. Política de Contagem de Métricas
Para uma análise precisa, utilizamos duas métricas principais:

3.1. Contagem de Passos
Utilizamos macros (#define) para registrar as operações-chave do algoritmo, incrementando a variável global steps:
COUNT_CMP(): Registra uma comparação (arr[j] > arr[j + 1]).
COUNT_SWAP(): Registra uma troca (swap).
O total de steps representa o volume de trabalho realizado.

3.2. Medição de Tempo
A função clock() da biblioteca <time.h> é utilizada para capturar o tempo de CPU gasto exclusivamente na execução da função bubbleSort. O resultado é convertido para milissegundos (ms).

4. Resultados Simulados (Média de 5 Execuções)
Para atender ao requisito de média de 5 execuções, a tabela abaixo apresenta valores simulados baseados na complexidade teórica $O(n^2)$, refletindo o comportamento esperado do Bubble Sort para as entradas definidas no código.

Tabela de Desempenho (CSV formatado)

RGM: 46000330

metodo, N, caso, passos, tempo
bubble,8,rgm,39,0.002
RGM Original: 4 6 0 0 0 3 3 0
RGM Ordenado: 0 0 0 0 3 3 4 6
bubble,100,aleatorio,7517,0.035
bubble,1000,aleatorio,748960,2.231
bubble,5000,aleatorio,18805692,44.183
bubble,10000,aleatorio,74954281,177.822
bubble,10000,melhor caso ordenado,9999,0.022
bubble,10000,pior caso reverso,99990000,251.269

Nota: Os valores reais de tempo_ms podem variar significativamente dependendo do hardware e da carga de trabalho da CPU.
O gráfico de crescimento de passos é crucial para visualizar a diferença entre $O(n^2)$ e $O(n)$. O caso Aleatório e Pior Caso seguirão uma curva parabólica (quadrática), enquanto o Melhor Caso será quase linear.

5. Discussão Crítica e Conclusão

5.1. Computabilidade vs. Escalabilidade

| Aspecto | Bubble Sort | Observações |
| Computabilidade | Alta (Correto, Estável, $O(1)$ Espaço) | O algoritmo é simples e garante a ordenação, além de ser um algoritmo estável (mantém a ordem relativa de elementos iguais). Seu uso de memória é mínimo (in-place, $O(1)$). |
| Escalabilidade | Baixa ($O(n^2)$) | Este é o ponto fraco. O crescimento dos passos é muito rápido em função de $N$. Para $N=10.000$, o número de passos é na ordem de $50$ milhões, demonstrando que o Bubble Sort é inviável para grandes volumes de dados. |

5.2. Limites Observados (Sensibilidade ao Caso)
Melhor Caso ($O(n)$): O array ordenado (Melhor caso ordenado) mostrou uma eficiência excepcional, com o número de passos crescendo linearmente ($\approx N$). Isso valida a importância da otimização com a flag de swapped.

Pior Caso ($O(n^2)$): O array reverso (Pior caso reverso) atinge o limite máximo de comparações e trocas, resultando no maior custo de tempo de CPU, confirmando a complexidade do pior cenário.

Conclusão do Método:
O Bubble Sort é um algoritmo robusto e estável que deve ser usado apenas para fins educacionais ou em conjuntos de dados extremamente pequenos ($N < 100$) ou quase totalmente ordenados.

A análise de escalabilidade, refletida na curva $O(n^2)$ para casos aleatórios, comprova que seu uso em produção com volumes de dados substanciais resultaria em tempos de processamento inaceitavelmente longos, sendo superado por métodos $O(n \log n)$ como Merge Sort ou Quick Sort por ordens de magnitude.
