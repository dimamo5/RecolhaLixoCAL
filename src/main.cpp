#include "LoadGraph.h"
#include "Visualizador/showgraph.h"

using namespace std;

int main() {
	Graph<Contentor> g;
	vector<Camiao> camioes;
	LoadGraph lg;

	lg.loadContentores(g);
	g.getVertexSet().size();
	lg.loadCamioes(camioes);
	lg.loadAdjacentes(g);

	showGraph(g);

	cin.get();

	//return 0;
}
