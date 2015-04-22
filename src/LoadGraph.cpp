/*
 * LoadGraph.cpp
 *
 *  Created on: 21/04/2015
 *      Author: Utilizador
 */

#include "LoadGraph.h"
#include <sstream>
#include <fstream>
#include <string>

bool LoadGraph::loadContentores(Graph<Contentor> &grafo) {
	ifstream fcaixotes;
	fcaixotes.open("resources/caixotes.txt");
	if (!fcaixotes.is_open()) {
		cerr << "Erro abrir ficheiro Caixotes";
		return false;
	}
	unsigned int id, quantidadeLixo, quantidadeMaxima;
	string s, rua;
	stringstream ss;
	getline(fcaixotes, s);
	ss << s;
	ss >> id;
	Contentor::setNextId(id);

	while (!fcaixotes.eof()) {
		getline(fcaixotes, s, ',');
		stringstream(s) >> id;

		getline(fcaixotes, rua, ',');

		getline(fcaixotes, s, ',');
		stringstream(s) >> quantidadeLixo;

		getline(fcaixotes, s);
		stringstream(s) >> quantidadeMaxima;

		//cout << id << " " << rua << " " << quantidadeLixo << " "
		//		<< quantidadeMaxima << endl;

		grafo.addVertex(
				*new Contentor(id, rua, quantidadeLixo, quantidadeMaxima));

	}

	return true;

}

bool LoadGraph::loadCamioes(vector<Camiao> &camioes) {
	ifstream fcamioes;
	fcamioes.open("resources/camioes.txt");
	if (!fcamioes.is_open()) {
		cerr << "Erro abrir ficheiro Caixotes";
		return false;
	}
	unsigned int id, capacidadeMaxima;
	string s;
	stringstream ss;
	getline(fcamioes, s);
	ss << s;
	ss >> id;
	Camiao::setNextId(id);

	while (!fcamioes.eof()) {
		getline(fcamioes, s, ',');
		stringstream(s) >> id;

		getline(fcamioes, s);
		stringstream(s) >> capacidadeMaxima;

		//cout << id << " " << capacidadeMaxima << endl;

		camioes.push_back(Camiao(id, 0, capacidadeMaxima));

	}

	return true;
}

bool LoadGraph::loadAdjacentes(Graph<Contentor> &grafo) {
	ifstream fadj;
	fadj.open("resources/adj.txt");
	if (!fadj.is_open()) {
		cerr << "Erro abrir ficheiro Caixotes";
		return false;
	}
	unsigned int idV1, idV2, peso;
	string s;

	while (!fadj.eof()) {
		getline(fadj, s, ',');
		stringstream(s) >> idV1;

		getline(fadj, s, ',');
		stringstream(s) >> idV2;

		getline(fadj, s);
		stringstream(s) >> peso;

		grafo.addEdge(Contentor(idV1, "tempVertex1", 0, 0),
				Contentor(idV2, "tempVertex2", 0, 0), peso,0);

	}

//	cout<<grafo.getNumVertex()<<endl;
//	cout<<grafo.getVertexSet()[0]->getAdj()[0].getDest()->getInfo().getId()<<endl;
//	cout<<grafo.getVertexSet()[0]->getAdj()[1].getDest()->getInfo().getId()<<endl;

	return true;
}
