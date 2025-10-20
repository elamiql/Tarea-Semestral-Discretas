#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

int** leer_entrada(const char *file, bool es_dirigido){
    char buffer[100];
    char arista;
    FILE *f = fopen(file, "r");

    if (f == NULL){
        perror("Error al abrir el archivo.\n");
        return NULL;
    }

    if (fscanf(f, "%d", &vertices) != 1 || vertices <= 0){
        printf("Error, numero de vertices invalido.\n");
        fclose(f);
        return NULL;
    }

    int c;
    while ((c = fgetc(f)) != '\n' && c != EOF);

    inicializar_matriz();

    while (fgets(buffer, sizeof(buffer), f) != NULL){
        char u, v;
        if (sscanf(buffer, "%c %c", &u, &v) == 2){
            int i = u - 'a';
            int j = v - 'a';
            matriz[i][j] = 1;
            if (!es_dirigido){
                matriz[j][i] = 1;
            }
        }
    }

    fclose(f);
    return matriz;
}

void dijkstra_alg(int** adjacency_matrix, int n, int start_node, int end_node){
    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, i, j;
    int nextnode = -1;

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
        nextnode = -1;
        for (i = 0; i < n; i++){
            if (distance[i] < mindistance && !visited[i]){
                mindistance = distance[i];
                nextnode = i;
            }
        }

        if (nextnode == -1){
            break;
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

    printf("\n.---------------------------------.\n");
    printf("|    RESULTADOS DEL ALGORITMO     |\n");
    printf("'---------------------------------'\n");
    
if (distance[end_node] == INFINITY) {
        printf("> Status: No hay camino posible\n");
        printf("> Entre:  %c y %c\n", 'a' + start_node, 'a' + end_node);
    } else {
        printf("> Nodo Inicial:     %c\n", 'a' + start_node);
        printf("> Nodo Final:       %c\n", 'a' + end_node);
        printf("> Distancia Mínima: %d\n", distance[end_node]);

        int path[MAX];
        int path_index = 0;
        int j = end_node;

        while (j != start_node){
            path[path_index] = j;
            path_index++;
            j = pred[j];
        }
        path[path_index] = start_node;

        printf("> Camino más corto: ");
        for (int i = path_index; i >= 0; i--) {
            printf("%c", 'a' + path[i]);
            if (i > 0) {
                printf(" -> ");
            }
        }
        printf("\n");
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        printf("Uso: %s nodo_inicial nodo_final archivo_grafo [dirigido|no_dirigido]\n", argv[0]);
        return 1;
    }

    char nodo_inicial = argv[1][0];
    char nodo_final = argv[2][0];
    char* graph = argv[3];
    char* tipo_grafo = argv[4]; 

    int start_index = nodo_inicial - 'a';
    int end_index = nodo_final - 'a';
        
    bool es_dirigido = false;
    if (strcmp(tipo_grafo, "dirigido") == 0){
        es_dirigido = true;
    }
    
    matriz = leer_entrada(graph, es_dirigido);
    if (!matriz) return 1;

    printf("\n..:: ANALIZADOR DE GRAFOS CON DIJKSTRA ::..\n");
    printf("=============================================\n");
    printf("  Archivo de grafo : %s\n", graph);
    printf("  Tipo de grafo    : %s\n", es_dirigido ? "Dirigido" : "No Dirigido");
    printf("  Total de vértices: %d\n", vertices);
    printf("  Buscando ruta de : %c -> %c\n", nodo_inicial, nodo_final);
    printf("=============================================\n");

    if (start_index < 0 || start_index >= vertices || end_index < 0 || end_index >= vertices) {
        printf("Error: Nodos inválidos. Los nodos para este grafo deben estar entre 'a' y '%c'.\n", 'a' + vertices - 1);
        liberar_matriz();
        return 1;
    }
    

    dijkstra_alg(matriz, vertices, start_index, end_index);
    liberar_matriz();
    
    return 0;
}