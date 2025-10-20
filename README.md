# Tarea semestral Matematicas Discretas

## Modo de uso 

Este programa utiliza el algoritmo de Dijkstra para encontrar el camino más corto entre dos nodos en un grafo. La entrada puede ser un grafo dirigido o no dirigido, leído desde un archivo de texto.

### 1. Requisitos
- Compilador `gcc`
- Entorno tipo Unix (Linux, macOS, WSL) o Windows

### 2. Compilación
Para compilar el programa, ejecuta el siguiente comando en tu terminal:
```bash
gcc -o path src/main.c
```
### 3. Ejecucion
El programa se ejecuta con el siguiente formato:

```bash
./path nodo_inicial nodo_final archivo_grafo [dirigido|no_dirigido]
```
#### Argumentos:
- `nodo_inicial`: El vertice de partida.
- `nodo_final`: El vertice de llegada.
- `archivo_grafo`: La ruta del archivo `.txt` que contiene la definicion del grafo.
- `[dirigido|no_dirigido]`: Especifica si las aristas del grafo deben ser tratadas como dirigidas o no dirigidas.

### Ejemplo concreto

```bash
./path a e grafos/input_graph3.txt no_dirigido
```

### Formato de Salida

La salida del programa mostrará la distancia total del camino más corto y la secuencia de nodos que lo componen.

```Salida
..:: ANALIZADOR DE GRAFOS CON DIJKSTRA ::..
=============================================
  Archivo de grafo : grafos/input_graph.txt
  Tipo de grafo    : No Dirigido
  Total de vértices: 12
  Buscando ruta de : a -> e
=============================================

.---------------------------------.
|    RESULTADOS DEL ALGORITMO     |
'---------------------------------'
> Nodo Inicial:     a
> Nodo Final:       e
> Distancia Mínima: 2
> Camino más corto: a -> c -> e

```