/*
 * LoadGraph.cpp
 *
 *  Created on: 21/04/2015
 *      Author: Utilizador
 */

#include "LoadGraph.h"
#include <sstream>
#include <string>

using namespace std;

LoadGraph::LoadGraph() {
}

bool LoadGraph::loadContentores(Graph<Contentor> grafo) {
	fcaixotes.open("resources/caixotes");
	if (!fcaixotes.is_open()) {
		cerr << "Erro abrir ficheiro Caixotes";
		return false;
	}
	unsigned int teste;
	string s;
	stringstream ss;
	getline(fcaixotes, s);
	ss << s;
	ss >> teste;
	Contentor::setNextId(teste);

	while(!fcaixotes.EOF){
		getline(fcaixotes, s);

	}

}

bool LoadGraph::loadCamioes(vector<Camiao> camioes) {
}

bool LoadGraph::loadAdjacentes(Graph<Contentor> grafo) {
}
