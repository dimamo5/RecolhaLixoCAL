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

	g.floydWarshallShortestPath();
	vector<Contentor> res;
	res = g.getfloydWarshallPath(Contentor(1, "inicio", 0, 0),
			Contentor(5, "fim", 0, 0));
	cout << "Tamanho:" << res.size() << endl;

	//	cout<<res[0].getId()<<endl;
//	cout<<res[1].getId()<<endl;
//	cout<<res[2].getId()<<endl;

	showGraph(g);

	cin.get();

	return 0;
}
