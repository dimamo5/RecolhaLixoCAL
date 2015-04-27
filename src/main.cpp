#include "LoadGraph.h"
#include "Visualizador/showgraph.h"
#include "windows.h"
#include "algoritmos.h"

using namespace std;

Graph<Contentor> newWorkingGraph(Graph<Contentor> &grafo);
void mapPath(Graph<Contentor> &grafo, Graph<Contentor> &newGrafo);
Graph<Contentor> newWorkingGraph(Graph<Contentor> &grafo);

int main() {

	Graph<Contentor> g, newG;
	vector<Camiao> camioes;
	LoadGraph lg;

	lg.loadContentores(g);
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

	//newG.floydWarshallShortestPath();

	//branchBound(newG);

	Camiao c = Camiao(3, 0);

	Camiao c2 = Camiao(1,0);

	brute_force_camiao(newG,c);


	//nearestNeighbourCamiao(newG, c);

	//Camiao c1 = Camiao(3, 0);

	showGraph(newG);
	cin.get();

//	newG = newWorkingGraph(newG);
//	cout << "lol"; cin.get();

	brute_force_camiao(newG,c2);

	showGraph(newG);
	cin.get();

	//nearestNeighbourCamiao(newG, c1);

	//c.calcRotaCamiao(g);

	//showGraph(newG);

	//mapPath(g, newG);

	showGraph(newG);

	mapPath(g, newG);

	showGraph(g);

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

void mapPath(Graph<Contentor> &grafo, Graph<Contentor> &newGrafo) {

	unsigned int id1, id2;

	vector<Contentor> res;

	Vertex<Contentor>* actual = newGrafo.getVertexSet()[0];

	while (actual->path != NULL) {
		id1 = actual->getInfo().getId();
		id2 = actual->path->getInfo().getId();

		res = grafo.getfloydWarshallPath(Contentor(id1, "Inicio", 0, 0), Contentor(id2, "Inicio", 0, 0));

		if (res.size() != 0) {
			for (unsigned int i = 0; i < res.size() - 1; i++) {
				findVertexId(grafo, res[i].getId())->path = findVertexId(grafo, res[i + 1].getId());
			}

		}
		actual = actual->path;
	}

//	for (unsigned int i = 0; i < newGrafo.getNumVertex(); i++) {
//		if (newGrafo.getVertexSet()[i]->path != NULL) {
//			id1 = newGrafo.getVertexSet()[i]->getInfo().getId();
//			id2 = newGrafo.getVertexSet()[i]->path->getInfo().getId();
//		}
//
//		vector<Contentor> res = grafo.getfloydWarshallPath(Contentor(id1, "Inicio", 0, 0), Contentor(id2, "Inicio", 0, 0));
//
//		if (res.size() != 0) {
//			for (unsigned int i = 0; i < res.size() - 1; i++) {
//				findVertexId(grafo, res[i].getId())->path = findVertexId(grafo, res[i + 1].getId());
//			}
//
//		}
//
//	}
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
