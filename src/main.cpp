#include "LoadGraph.h"
#include "Visualizador/showgraph.h"

using namespace std;

Graph<Contentor> newWorkingGraph(Graph<Contentor> &grafo);

int main() {
	Graph<Contentor> g,newG;
	vector<Camiao> camioes;
	LoadGraph lg;

	lg.loadContentores(g);
	g.getVertexSet().size();
	lg.loadCamioes(camioes);
	lg.loadAdjacentes(g);

	g.floydWarshallShortestPath();
	vector<Contentor> res;
	res = g.getfloydWarshallPath(Contentor(1, "inicio", 0, 0),
			Contentor(7, "fim", 0, 0));
	cout << "Tamanho:" << res.size() << endl;

	showGraph(g);

	newG=newWorkingGraph(g);

	showGraph(newG);

	cin.get();

	return 0;
}

Graph<Contentor> newWorkingGraph(Graph<Contentor> &grafo) {

	Graph<Contentor> workingGraph;

	vector<Contentor> contentorPrioritarios;

	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {

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
		for (unsigned int j=0; j < contentorPrioritarios.size(); j++) {
			if (j == i) {
				continue;
			} else {
				//Se existir arestas entre os vertices
				res = grafo.getfloydWarshallPath(contentorPrioritarios[i],
						contentorPrioritarios[j]);

				if (res.size() > 0) {
					int peso =grafo.getfloydWarshallWeigth(contentorPrioritarios[i],contentorPrioritarios[j]);
					//cout<<"Peso:"<<peso<<endl;
					workingGraph.addEdge(contentorPrioritarios[i],
							contentorPrioritarios[j], peso);
				}
			}
		}
	}
	return workingGraph;
}




