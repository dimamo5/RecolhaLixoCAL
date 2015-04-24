#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "showgraph.h"
#include "../Contentor.h"
#include "../Graph.h"

using namespace std;

void showGraph(Graph<Contentor> &grafo) {
	GraphViewer *gv = new GraphViewer(800, 800, true);

	gv->createWindow(800, 800);

	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	unsigned int id1, id2;
	string s;
	stringstream ss;

	for (unsigned int i = 0; i < grafo.getVertexSet().size(); i++) {
		id1 = grafo.getVertexSet()[i]->getInfo().getId();
		s = grafo.getVertexSet()[i]->getInfo().getRua();
		gv->addNode(id1);
		gv->setVertexLabel(id1, s);

		if (grafo.getVertexSet()[i]->getInfo().isPrioritario()) {
			gv->setVertexColor(id1, "yellow");
		} else if (grafo.getVertexSet()[i]->getInfo().getQuantidadeMaxima() == 0) {
			gv->setVertexColor(id1, "red");
		}
	}

	gv->rearrange();

	for (unsigned int vert = 0; vert < grafo.getVertexSet().size(); vert++) {
		for (unsigned int edge = 0; edge < grafo.getVertexSet()[vert]->getAdj().size(); edge++) {
			id1 = grafo.getVertexSet()[vert]->getInfo().getId();
			id2 = grafo.getVertexSet()[vert]->getAdj()[edge].getDest()->getInfo().getId();

			if (grafo.getVertexSet()[vert]->path != NULL && grafo.getVertexSet()[vert]->path->getInfo().getId() == id2) {
				gv->setEdgeColor(id1 * 100 + id2, "green");
				gv->setEdgeThickness(id1 * 100 + id2, 3);
			}

			gv->addEdge(id1 * 100 + id2, id1, id2, EdgeType::DIRECTED);

			gv->setEdgeWeight(id1 * 100 + id2, grafo.getVertexSet()[vert]->getAdj()[edge].getWeight());
			ss.str("");
		}
	}

#ifdef __linux__
	sleep(1);
#else
	Sleep(100); // use sleep(1) in linux ; Sleep(100) on Windows
#endif

	gv->rearrange();

}

