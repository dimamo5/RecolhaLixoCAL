#include "LoadGraph.h"
#include "Visualizador/showgraph.h"
#include "Graph.h"
#include "windows.h"
#include <algorithm>

using namespace std;

Graph<Contentor> newWorkingGraph(Graph<Contentor> &grafo);

void nearestNeighbour(Graph<Contentor> &grafo);
Vertex<Contentor>* findVertexId(Graph<Contentor> &grafo, int id);
void mapPath(Graph<Contentor> &grafo, Graph<Contentor> &newGrafo);
void calcRotaCamiao(Graph<Contentor> &grafo, Camiao &camiao);
void nearestNeighbourCamiao(Graph<Contentor> &grafo, Camiao &c);
void branchBound(Graph<Contentor> &grafo);
int calcMinRow(int ** W, int size, int row);
int calcMinColumn(int ** W, int size, int row);
int calcLowerBound(int ** W, int size, int id);
void printSquareArray(int ** arr, unsigned int size);
void branchBoundRec(Graph<Contentor> &grafo, vector<int> &path, int id, int** W);
bool visitedPath(vector<int> &path, int id);
int getVertexIndice(Graph<Contentor> &grafo, int id);

//================
int bound, row, col, pencost[11];

void branch_Bound(Graph<Contentor> &grafo);
int allVisited(int v[], int size);
int checkBounds(int orig, int dest, int**w, int size);
int calcMinRow(int ** W, int size, int row);
int calcMinColumn(int ** W, int size, int row);
int rowReduction(int **w, int size);
int colReduction(int **w, int size);

//=================
struct point {
	int orig, dest;
};

void brute_force(Graph<Contentor> &grafo);

void iguala_arrays(int v[], int a[], int size);

void print(int v[], int size) {

	for (int i = 0; i < size; i++)
		cout << v[i] << " " << endl;
}

//=================
int main() {

	Graph<Contentor> g, newG;
	vector<Camiao> camioes;
	LoadGraph lg;

	lg.loadContentores(g);
	lg.loadCamioes(camioes);
	lg.loadAdjacentes(g);

	//============================
	//g.floydWarshallShortestPath();

	//	brute_force(g);
	//	cin.get();
	//
	//	showGraph(g);
	//	cin.get();
	//============================
	g.floydWarshallShortestPath();

	newG = newWorkingGraph(g);

	newG.floydWarshallShortestPath();

	showGraph(newG);

	branchBound(newG);

	//g.printSquareArray(g.getW(), g.getNumVertex());

	//cout << checkBounds(0, 5, g.getW(), 11);

	/*newG = newWorkingGraph(g);
	 cout << "vertices " << newG.getNumVertex() << endl;
	 cin.get();




	 newG.printSquareArray(newG.getW(), newG.getNumVertex());
	 cin.get();

	 brute_force(newG);
	 cin.get();
	 showGraph(newG);

	 //cin.get();

	 nearestNeighbour(newG);

	 mapPath(g, newG);

	 Camiao c = Camiao(3, 0, INT_MAX);

	 calcRotaCamiao(g, c);

	 //	Camiao c = Camiao(3, 0, 15000);
	 //	Camiao c1 = Camiao(3, 0, 1000);
	 //
	 //	nearestNeighbourCamiao(newG, c);
	 //
	 //	cout<<"Lixo Apanhado:"<<c.getQuantidadeLixo()<<endl;
	 //
	 //	nearestNeighbourCamiao(newG, c1);
	 //
	 //	cout<<"Lixo Apanhado:"<<c1.getQuantidadeLixo()<<endl;
	 //
	 //	cout<<"Rota tamanho:"<<c.getRota().size()<<endl;

	 //cout<<newG.getVertexSet()[2]->getInfo().getQuantidadeLixo();
	 //calcRotaCamiao(g, c);
	 //cout << "Dist Opt:" << c.getDist() << endl;

	 showGraph(g);

	 //showGraph(newG);

	 //return 0;

	 branch_Bound(g);

	 getchar();
	 */
	cin.get();
	return 0;
}

//===================================
void brute_force(Graph<Contentor> &grafo) {

	int sum = 0, min_dist = INT_INFINITY;
	int size = grafo.getNumVertex();

	int route[size], vert[size];

	for (int i = 0; i < size; i++) {
		vert[i] = i;
	}

	grafo.printSquareArray(grafo.getW(), grafo.getNumVertex());
	cin.get();

	while (std::next_permutation(vert + 1, vert + size - 1)) {

		print(vert, size);
		cin.get();

		for (int i = 0; i < size - 1; i++) {

			if (grafo.getW()[vert[i]][vert[i + 1]] == INT_INFINITY)
				sum = INT_INFINITY;

			if (sum != INT_INFINITY)
				sum += grafo.getW()[vert[i]][vert[i + 1]];
		}

		if (sum < min_dist) {
			min_dist = sum;
			iguala_arrays(route, vert, size);
		}
		sum = 0;
	}

	cout << "min_dist " << min_dist << endl;
	print(route, size);

}

void iguala_arrays(int v[], int a[], int size) {

	for (int i = 0; i < size; i++) {
		v[i] = a[i];
	}
}
//===================================

Graph<Contentor> newWorkingGraph(Graph<Contentor> &grafo) {

	Graph<Contentor> workingGraph = Graph<Contentor>();

	vector<Contentor> contentorPrioritarios;

	for (int i = 0; i < grafo.getNumVertex(); i++) {

		if (grafo.getVertexSet()[i]->getInfo().isPrioritario()) {
			contentorPrioritarios.push_back(grafo.getVertexSet()[i]->getInfo());
		}
		//vertice incio e final
		if (i == 0 || i == grafo.getNumVertex() - 1) {
			contentorPrioritarios.push_back(grafo.getVertexSet()[i]->getInfo());
		}
	}

	for (unsigned int i = 0; i < contentorPrioritarios.size(); i++) {
		workingGraph.addVertex(contentorPrioritarios[i]);
	}

	vector<Contentor> res;

	for (unsigned int i = 0; i < contentorPrioritarios.size(); i++) {
		for (unsigned int j = 0; j < contentorPrioritarios.size(); j++) {
			if (j == i) {
				continue;
			} else {
				//Se existir arestas entre os vertices
				res = grafo.getfloydWarshallPath(contentorPrioritarios[i], contentorPrioritarios[j]);

				if (res.size() > 0) {
					int peso = grafo.getfloydWarshallWeigth(contentorPrioritarios[i], contentorPrioritarios[j]);
					workingGraph.addEdge(contentorPrioritarios[i], contentorPrioritarios[j], peso);
				}
			}
		}
	}

	return workingGraph;
}

void nearestNeighbour(Graph<Contentor> &grafo) {
	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {
		grafo.getVertexSet()[i]->setVisited(false);
	}
	Vertex<Contentor>* actual = grafo.getVertexSet()[0];
	Vertex<Contentor>* proximo;
	unsigned int pesoMinimo = INT_INFINITY;
	actual->setVisited(true);

	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {
		for (unsigned int j = 0; j < actual->getAdj().size(); j++) {
			if (actual->getAdj()[j].getWeight() < pesoMinimo && !actual->getAdj()[j].getDest()->isVisited()) {
				if ((actual->getAdj()[j].getDest()->getInfo().getQuantidadeMaxima() == 0) && i < grafo.getNumVertex() - 1) {
					continue;
				} else {
					pesoMinimo = actual->getAdj()[j].getWeight();
					proximo = actual->getAdj()[j].getDest();
				}
			}
		}
		if (!(proximo->getInfo() == actual->getInfo())) {
			actual->path = proximo;
		}
		actual = proximo;
		actual->setVisited(true);
		pesoMinimo = INT_INFINITY;

	}

}

void mapPath(Graph<Contentor> &grafo, Graph<Contentor> &newGrafo) {

	unsigned int id1, id2;

	for (unsigned int i = 0; i < newGrafo.getNumVertex(); i++) {
		if (newGrafo.getVertexSet()[i]->path != NULL) {
			id1 = newGrafo.getVertexSet()[i]->getInfo().getId();
			id2 = newGrafo.getVertexSet()[i]->path->getInfo().getId();
		}

		vector<Contentor> res = grafo.getfloydWarshallPath(Contentor(id1, "Inicio", 0, 0), Contentor(id2, "Inicio", 0, 0));

		if (res.size() != 0) {
			for (unsigned int i = 0; i < res.size() - 1; i++) {
				findVertexId(grafo, res[i].getId())->path = findVertexId(grafo, res[i + 1].getId());
			}

		}

	}
}

Vertex<Contentor>* findVertexId(Graph<Contentor> &grafo, int id) {
	for (unsigned int j = 0; j < grafo.getVertexSet().size(); j++) {
		if (id == grafo.getVertexSet()[j]->getInfo().getId()) {
			return grafo.getVertexSet()[j];
		}
	}
	return NULL;
}

void calcRotaCamiao(Graph<Contentor> &grafo, Camiao &camiao) {

	Vertex<Contentor>* actual = grafo.getVertexSet()[0];

	camiao.addContentor(actual->getInfo());

	while (actual->path != NULL) {

		for (unsigned int i = 0; i < actual->getAdj().size(); i++) {
			if (actual->path->getInfo().getId() == actual->getAdj()[i].getDest()->getInfo().getId()) {
				camiao.addDist(actual->getAdj()[i].getWeight());
				break;
			}
		}

		camiao.addContentor(actual->path->getInfo());
		actual = actual->path;
	}
}

void branchBound(Graph<Contentor> &grafo) {

	vector<int> path;

	int row = rowReduction(grafo.getW(), grafo.getNumVertex());
	int col = colReduction(grafo.getW(), grafo.getNumVertex());

	cout << "Bound inicial:" << (bound = row + col) << endl;

	int ** newW = new int *[grafo.getNumVertex()];

	for (int i = 0; i < grafo.getNumVertex(); i++) {
		newW[i] = new int[grafo.getNumVertex()];
		for (int j = 0; j < grafo.getNumVertex(); j++) {
			newW[i][j] = grafo.getW()[i][j];
		}
	}

	path.push_back(0);

	branchBoundRec(grafo, path, 0, newW);

	path.push_back(getVertexIndice(grafo,grafo.getVertexSet()[grafo.getNumVertex() - 1]->getInfo().getId()));

}

int getVertexIndice(Graph<Contentor> &grafo, int id) {
	for (int i = 0; i < grafo.getNumVertex(); i++) {
		if (grafo.getVertexSet()[i]->getInfo().getId() == id) {
			return i;
		}
	}
	return -1;
}

void branchBoundRec(Graph<Contentor> &grafo, vector<int> &path, int id, int** W) {

	Vertex<Contentor>* actual = grafo.getVertexSet()[id];

	if (path.size() == grafo.getNumVertex()-1) {
		return;
	}

	int minBound = INT_MAX, novoId, idComparar;

	for (unsigned int i = 0; i < actual->getAdj().size(); i++) {
		idComparar = getVertexIndice(grafo,actual->getAdj()[i].getDest()->getInfo().getId());

		if (checkBounds(id, idComparar, W, grafo.getNumVertex()) < minBound && !visitedPath(path, idComparar)
				&& idComparar != getVertexIndice(grafo, grafo.getVertexSet()[grafo.getNumVertex() - 1]->getInfo().getId())) {
			minBound = checkBounds(id, getVertexIndice(grafo, actual->getAdj()[i].getDest()->getInfo().getId()), W, grafo.getNumVertex());
			novoId = getVertexIndice(grafo, actual->getAdj()[i].getDest()->getInfo().getId());
		}
	}
	path.push_back(novoId);

	for (int i = 0; i < grafo.getNumVertex(); i++) {
		W[id][i] = INT_INFINITY;
	}

	for (int i = 0; i < grafo.getNumVertex(); i++) {
		W[i][novoId] = INT_INFINITY;
	}

	W[novoId][id] = INT_INFINITY;

	//cout << endl << "Id:" << novoId << "Bound:" << minBound << endl;

	rowReduction(W, grafo.getNumVertex());
	colReduction(W, grafo.getNumVertex());

	branchBoundRec(grafo, path, novoId, W);

}

bool visitedPath(vector<int> &path, int id) {
	for (unsigned int i = 0; i < path.size(); i++) {
		if (id == path[i]) {
			return true;
		}
	}
	return false;
}

int checkBounds(int orig, int dest, int**w, int size) {

	pencost[0] = bound;

	int reduced_size = size; //actualizar esta variavel convenientemente
	int ** reduced = new int *[size];

	for (int i = 0; i < size; i++) {
		reduced[i] = new int[size];
		for (int j = 0; j < size; j++) {
			reduced[i][j] = w[i][j];
		}
	}

	for (int i = 0; i < size; i++) {
		reduced[orig][i] = INT_INFINITY;
	}

	for (int i = 0; i < size; i++) {
		reduced[i][dest] = INT_INFINITY;
	}
	reduced[dest][orig] = INT_INFINITY;

	rowReduction(reduced, reduced_size);
	colReduction(reduced, reduced_size);

	pencost[dest] = pencost[orig] + row + col + w[orig][dest];

	return pencost[dest];
}


int calcMinRow(int ** W, int size, int row) {
	unsigned int min = INT_MAX;
	for (unsigned int i = 0; i < size; i++) {
		if (row == i) {
			continue;
		} else if (W[row][i] < min) {
			min = W[row][i];
		}
	}
	return min;
}

int calcMinColumn(int ** W, int size, int col) {
	unsigned int min = INT_MAX;
	for (unsigned int i = 0; i < size; i++) {
		if (col == i) {
			continue;
		} else if (W[i][col] < min) {
			min = W[i][col];
		}
	}

	return min;
}

int rowReduction(int ** w, int size) {

	row = 0;
	int rmin;

	for (int i = 0; i < size; i++) {
		rmin = calcMinRow(w, size, i);

		if (rmin != INT_INFINITY)
			row += rmin;

		for (int j = 0; j < size; j++) {
			if (!(w[i][j] == INT_INFINITY || i == j))
				w[i][j] -= rmin;
		}
	}
	return row;
}

int colReduction(int **w, int size) {

	col = 0;
	int cmin;

	for (int i = 0; i < size; i++) {
		cmin = calcMinColumn(w, size, i);

		if (cmin != INT_INFINITY)
			col += cmin;

		for (int j = 0; j < size; j++) {
			if (!(w[j][i] == INT_INFINITY || i == j))
				w[j][i] -= cmin;
		}
	}
	return col;
}

//===========================

void nearestNeighbourCamiao(Graph<Contentor> &grafo, Camiao &c) {
	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {
		grafo.getVertexSet()[i]->path = NULL;
	}

	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {
		grafo.getVertexSet()[i]->setVisited(false);
	}

	Vertex<Contentor>* actual = grafo.getVertexSet()[0];
	Vertex<Contentor>* proximo;
	unsigned int lixoMaior = 0;
	actual->setVisited(true);

	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {
		for (unsigned int j = 0; j < actual->getAdj().size(); j++) {

			if (actual->getAdj()[j].getDest()->getInfo().getQuantidadeLixo() > lixoMaior && !actual->getAdj()[j].getDest()->isVisited()) {
				if ((actual->getAdj()[j].getDest()->getInfo().getQuantidadeMaxima() == 0)) {
					continue;
				} else {
					if ((actual->getAdj()[j].getDest()->getInfo().getQuantidadeLixo() + c.getQuantidadeLixo()) < c.getCapacidadeMaxima()) {
						lixoMaior = actual->getAdj()[j].getDest()->getInfo().getQuantidadeLixo();
						proximo = actual->getAdj()[j].getDest();
					}
				}
			}
		}

		//Acabou apanhar lixo
		if (actual->getInfo() == proximo->getInfo()) {
			actual->path = grafo.getVertexSet()[grafo.getNumVertex() - 1];
			c.addContentor(findVertexId(grafo, grafo.getVertexSet()[grafo.getNumVertex() - 1]->getInfo().getId())->getInfo());
			return;
		}

		if (!(proximo->getInfo() == actual->getInfo())) {
			actual->path = proximo;
			c.addContentor(actual->path->getInfo());

			proximo->getInfo().setQuantidadeLixo(0);
		}

		actual = proximo;
		actual->setVisited(true);
		lixoMaior = 0;
	}
}

void printSquareArray(int ** arr, unsigned int size) {
	for (unsigned int k = 0; k < size; k++) {
		if (k == 0) {
			cout << "   ";
			for (unsigned int i = 0; i < size; i++) {
				cout << setw(5);
				cout << i;
			}
			cout << endl;
		}

		for (unsigned int i = 0; i < size; i++) {
			if (i == 0) {
				cout << setw(5);

				cout << k;
			}

			if (arr[k][i] == INT_INFINITY) {
				cout << setw(5);
				cout << "-";
			}

			else {
				cout << setw(5);
				cout << arr[k][i];
			}
		}

		cout << endl;
	}
}
