#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "showgraph.h"
#include "../Contentor.h"
#include "../Graph.h"

void showGraph(Graph<Contentor> &grafo) {
	GraphViewer *gv = new GraphViewer(600, 600, true);

	//gv->setBackground("resources/merda.jpg");

	gv->createWindow(600, 600);


	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(0);
	gv->addNode(1);
	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);

#ifdef __linux__
	sleep(1);
#else
	Sleep(100); // use sleep(1) in linux ; Sleep(100) on Windows
#endif

	gv->removeEdge(0);
	gv->removeNode(1);
	gv->addNode(2);

	gv->rearrange();

	Sleep(100);

	gv->addEdge(1, 0, 2, EdgeType::UNDIRECTED);

	gv->setVertexLabel(0, "Isto e um no");
	gv->setEdgeLabel(1, "Isto e uma aresta");

	gv->setVertexColor(2, "green");
	gv->setEdgeColor(1, "yellow");

	gv->rearrange();

}
