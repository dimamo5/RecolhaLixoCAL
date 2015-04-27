#include "LoadGraph.h"
#include "Visualizador/showgraph.h"
#include "windows.h"
#include "algoritmos.h"

using namespace std;

Graph<Contentor> newWorkingGraph(Graph<Contentor> &grafo);
void mapPath(Graph<Contentor> &grafo, Graph<Contentor> &newGrafo);
void part1(Graph<Contentor> &g, Graph<Contentor> &newG);
void part2(Graph<Contentor> &g, Graph<Contentor> &newG);
bool hasPrioritarios(Graph<Contentor> grafo);
void menu(Graph<Contentor> &g);

int main() {

	Graph<Contentor> g;
	LoadGraph lg;

	lg.loadContentores(g);
	lg.loadAdjacentes(g);

	g.floydWarshallShortestPath();

	menu(g);

	system("PAUSE");
	return 0;
}

void menu(Graph<Contentor> &g) {

	Graph<Contentor> newG = newWorkingGraph(g);

	newG.floydWarshallShortestPath();

	cout << endl << "Escolha Opção" << endl;
	cout << "1- Camião com Capacidade Ilimitada passa por todos os pontos." << endl;
	cout << "2- Camiões com Capacidade Limitada pelo maximo de lixo que podem recolher" << endl;

	char opcao;
	cin >> opcao;

	if (opcao == '1') {
		part1(g, newG);
	} else if (opcao == '2') {
		part2(g, newG);
	}
}

Graph<Contentor> newWorkingGraph(Graph<Contentor> &grafo) {

	Graph<Contentor> workingGraph;

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

void part1(Graph<Contentor> &g, Graph<Contentor> &newG) {

	char opcao2 = 'd';

	clock_t t;
	while (opcao2 != 5) {

		cout << "1- Brute Force (Permutacoes)" << endl;
		cout << "2- Branch and Bound" << endl;
		cout << "3- Nearest neighbour" << endl;
		cout << "4- Compara os 3" << endl;
		cout << "5- Retornar" << endl;

		cin >> opcao2;

		if (opcao2 == '1') {
			Camiao c;
			c.setCapacidadeMaxima(INT_MAX);
			brute_force(newG, c);
			c.calcRotaCamiao(newG);
			c.print();
			cout << flush;
			showGraph(newG);
			mapPath(g, newG);
			showGraph(g);
			getchar();

		} else if (opcao2 == '2') {
			Camiao c;
			c.setCapacidadeMaxima(INT_MAX);
			branchBound(newG, c);
			c.calcRotaCamiao(newG);
			c.print();
			cout << flush;
			showGraph(newG);
			mapPath(g, newG);
			showGraph(g);

		} else if (opcao2 == '3') {
			Camiao c;
			c.setCapacidadeMaxima(INT_MAX);
			nearestNeighbour(newG, c);
			c.calcRotaCamiao(newG);
			c.print();
			cout << flush;
			showGraph(newG);
			mapPath(g, newG);
			showGraph(g);
		} else if (opcao2 == '4') {
			Camiao c;
			c.setCapacidadeMaxima(INT_MAX);
			cout << "Nearest neighbour:" << endl;
			t = clock();
			nearestNeighbour(newG, c);
			t = clock() - t;
			cout << "Ticks:" << t << endl;

			cout << "Brute Force:" << endl;
			t = clock();
			brute_force(newG, c);
			t = clock() - t;
			cout << "Ticks:" << t << endl;

			cout << "Branch And Bound:" << endl;
			t = clock();
			branchBound(newG, c);
			t = clock() - t;
			cout << "Ticks:" << t << endl;
		} else if (opcao2 == '5') {
			return;
		}
		cout << endl << "Permir novamente para sair!" << endl;
		cout << flush;
		cin.get();
	}

}

void part2(Graph<Contentor> &g, Graph<Contentor> &newG) {

	char opcao;

	showGraph(g);

	cout << "1- Nearest Neighbour adaptado" << endl;
	cout << "2- Brute Force" << endl;
	cout << "3- Retornar" << endl;

	cin >> opcao;

	if (opcao == '1') {
		while (hasPrioritarios(newG)) {
			Camiao c;
			nearestNeighbourCamiao(newG, c);
			c.calcRotaCamiao(newG);
			c.print();
		}
		menu(g);
	} else if (opcao == '2') {
		while (hasPrioritarios(newG)) {
			Camiao c;
			brute_force_camiao(newG, c);
			c.calcRotaCamiao(newG);
			c.print();
		}
		menu(g);
	} else if (opcao == '3') {
		menu(g);
	}
}

void mapPath(Graph<Contentor> &grafo, Graph<Contentor> &newGrafo) {

	unsigned int id1, id2;

	vector<Contentor> res;

	Vertex<Contentor>* actual = newGrafo.getVertexSet()[0];

	while (actual->path != NULL) {
		id1 = actual->getInfo().getId();
		id2 = actual->path->getInfo().getId();
		//		cout<<" id1:"<<id1<<" id2:"<<id2<<"->";

		res = grafo.getfloydWarshallPath(Contentor(id1, "Inicio", 0, 0), Contentor(id2, "Inicio", 0, 0));

		if (res.size() != 0) {
			for (unsigned int i = 0; i < res.size() - 1; i++) {
				findVertexId(grafo, res[i].getId())->path = findVertexId(grafo, res[i + 1].getId());
			}

		}
//		cout << actual->getInfo().getId() << "  ";
		actual = actual->path;

		res.clear();
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

bool hasPrioritarios(Graph<Contentor> grafo) {
	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {
		if (grafo.getVertexSet()[i]->getInfo().isPrioritario()) {
			return true;
		}
	}
	return false;
}
