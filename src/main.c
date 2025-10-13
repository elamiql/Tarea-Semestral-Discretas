#include <stdio.h>
#include <stdlib.h>

#define INFINITY 9999
#define MAX 50

int vertices;
int** matriz;

void inicializar_matriz(){
    matriz = (int **)malloc(vertices*sizeof(int*));
    for (int i = 0; i < vertices; i++){
        matriz[i] = (int *)malloc(vertices*sizeof(int));
        for (int j = 0; j < vertices; j++){
            matriz[i][j] = 0;
        }
    }
}

void imprimir_matriz() {
    printf("\nMatriz de adyacencia: \n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void liberar_matriz() {
    for (int i = 0; i < vertices; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int** leer_entrada(const char *file){
    char buffer[100];
    char arista;
    FILE *f = fopen(file, "r");

    if (f == NULL){
        perror("Error al abrir el archivo.\n");
    }

    if (fscanf(f, "%d", &vertices) != 1 || vertices <= 0){
        printf("Error, numero de vertices invalido.\n");
        fclose(f);
    }

    inicializar_matriz();

    while (fgets(buffer, sizeof(buffer), f) != NULL){
        char u, v;
        if (sscanf(buffer, "%c %c", &u, &v) == 2){
            int i = u - 'a';
            int j = v - 'a';
            matriz[i][j] = 1;
            matriz[j][i] = 1;
        }
    }

    fclose(f);
    return matriz;
}

void dijkstra_alg(int** adjacency_matrix, int n, int start_node, int end_node){
    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, nextnode, i, j;

    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if (adjacency_matrix[i][j] == 0){
                cost[i][j] = INFINITY;
            }
            else{
                cost[i][j] = adjacency_matrix[i][j];
            }
        }
    }
    for (i = 0; i < n; i++){
        distance[i] = cost[start_node][i];
        pred[i] = start_node;
        visited[i] = 0;
    }

    distance[start_node] = 0;
    visited[start_node] = 1;
    count = 1;

    while (count < n-1){
        mindistance = INFINITY;
        for (i = 0; i < n; i++){
            if (distance[i] < mindistance && !visited[i]){
                mindistance = distance[i];
                nextnode = i;
            }
        }

        visited[nextnode] = 1;
        for (i = 0; i < n; i++){
            if (!visited[i]){
                if (mindistance + cost[nextnode][i] < distance[i]){
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
            }
        }
        count++;
    }

    if (distance[end_node] == INFINITY) {
        printf("\nNo hay camino posible entre %c y %c.\n", 'a' + start_node, 'a' + end_node);
    } else {
        printf("\nDistancia de %c a %c: %d\n", 'a' + start_node, 'a' + end_node, distance[end_node]);
        printf("Camino: %c", 'a' + end_node);
        j = end_node;
        while (j != start_node) {
            j = pred[j];
            printf(" -> %c", 'a' + j);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Uso: %s nodo_inicial nodo_final\n", argv[0]);
        return 1;
    }

    char nodo_inicial = argv[1][0];
    char nodo_final = argv[2][0];
    char* graph = argv[3];

    int start_index = nodo_inicial - 'a';
    int end_index = nodo_final - 'a';

    if (start_index < 0 || start_index >= MAX || end_index < 0 || end_index >= MAX) {
        printf("Nodos inválidos\n");
        return 1;
    }

    matriz = leer_entrada(graph);
    if (!matriz) return 1;

    imprimir_matriz();
    dijkstra_alg(matriz, vertices, start_index, end_index);

    liberar_matriz();
    return 0;
}