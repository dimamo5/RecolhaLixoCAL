/*
 * LoadGraph.h
 *
 *  Created on: 21/04/2015
 *      Author: Utilizador
 */

#ifndef LOADGRAPH_H_
#define LOADGRAPH_H_

#include <vector>
#include "Graph.h"
#include "Camiao.h"
#include "Contentor.h"

using namespace std;

class LoadGraph {
public:
	bool loadContentores(Graph<Contentor> &grafo);
	bool loadCamioes(vector<Camiao> &camioes);
	bool loadAdjacentes(Graph<Contentor> &grafo);


};

#endif /* LOADGRAPH_H_ */
