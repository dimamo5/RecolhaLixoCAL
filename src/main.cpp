#include "LoadGraph.h"
#include "Visualizador/showgraph.h"
#include "Graph.h"

using namespace std;

Graph<Contentor> newWorkingGraph(Graph<Contentor> &grafo);
void nearestNeighbour(Graph<Contentor> &grafo);
Vertex<Contentor>* findVertexId(Graph<Contentor> &grafo, int id);
void mapPath(Graph<Contentor> &grafo, Graph<Contentor> &newGrafo);
void calcRotaCamiao(Graph<Contentor> &grafo, Camiao &camiao);

int main() {
	Graph<Contentor> g, newG;
	vector<Camiao> camioes;
	LoadGraph lg;

	lg.loadContentores(g);
	lg.loadCamioes(camioes);
	lg.loadAdjacentes(g);

	g.floydWarshallShortestPath();

	newG = newWorkingGraph(g);

	nearestNeighbour(newG);

	mapPath(g, newG);

	Camiao c= Camiao(3,0,INT_MAX);

	calcRotaCamiao(g,c);

	showGraph(g);

	showGraph(newG);

	getchar();

	return 0;
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
			camiao.addContentor(actual->path->getInfo());
			actual=actual->path;
	}

}

