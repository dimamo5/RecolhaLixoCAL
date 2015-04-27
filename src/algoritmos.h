#include "Graph.h"
#include "Contentor.h"
#include "Camiao.h"

void iguala_arrays(int v[], int a[], int size);
void brute_force(Graph<Contentor> &grafo);

void nearestNeighbour(Graph<Contentor> &grafo);
Vertex<Contentor>* findVertexId(Graph<Contentor> &grafo, int id);
void nearestNeighbourCamiao(Graph<Contentor> &grafo, Camiao &c);

void branchBound(Graph<Contentor> &grafo);
void branchBoundRec(Graph<Contentor> &grafo, vector<int> &path, int id, int** W);

int checkBounds(int orig, int dest, int**w, int size);
int calcMinRow(int ** W, int size, int row);
int calcMinColumn(int ** W, int size, int col);
int rowReduction(int ** w, int size);
int colReduction(int **w, int size);
bool visitedPath(vector<int> &path, int id);
int getVertexIndice(Graph<Contentor> &grafo, int id);
