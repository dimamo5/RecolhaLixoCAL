/*
 * Camiao.cpp
 *
 *  Created on: 21/04/2015
 *      Author: Utilizador
 */

#include "Camiao.h"

unsigned int Camiao::nextId = 1;

Camiao::Camiao() {
	this->id = nextId;
	nextId++;
	this->quantidadeLixo = 0;
	this->capacidadeMaxima = 1000;
	this->distanciaPercorrida=0;
}

Camiao::Camiao(unsigned int id, unsigned int quantidadeLixo, unsigned int capacidadeMaxima) :
		id(id), quantidadeLixo(quantidadeLixo), capacidadeMaxima(capacidadeMaxima) {
	this->distanciaPercorrida=0;

}

unsigned int Camiao::getCapacidadeMaxima() const {
	return capacidadeMaxima;
}

void Camiao::setCapacidadeMaxima(unsigned int capacidadeMaxima) {
	this->capacidadeMaxima = capacidadeMaxima;
}

unsigned int Camiao::getId() const {
	return id;
}

void Camiao::setId(unsigned int id) {
	this->id = id;
}

unsigned int Camiao::getQuantidadeLixo() const {
	return quantidadeLixo;
}

void Camiao::setQuantidadeLixo(unsigned int quantidadeLixo) {
	this->quantidadeLixo = quantidadeLixo;
}

unsigned int Camiao::getNextId() {
	return nextId;
}

void Camiao::setNextId(unsigned int nextId) {
	Camiao::nextId = nextId;
}

void Camiao::addContentor(Contentor c) {
	this->quantidadeLixo += c.getQuantidadeLixo();

	rota.push_back(c);
}

vector<Contentor> Camiao::getRota() const {
	return rota;
}

void Camiao::addDist(unsigned int d) {
	this->distanciaPercorrida += d;
}

unsigned int Camiao::getDist() const {
	return distanciaPercorrida;
}

void Camiao::calcRotaCamiao(Graph<Contentor> &grafo) {

	Vertex<Contentor>* actual = grafo.getVertexSet()[0];

	this->addContentor(actual->getInfo());

	while (actual->path != NULL) {

		for (unsigned int i = 0; i < actual->getAdj().size(); i++) {
			if (actual->path->getInfo().getId() == actual->getAdj()[i].getDest()->getInfo().getId()) {
				this->addDist(actual->getAdj()[i].getWeight());
				break;
			}
		}

		this->addContentor(actual->path->getInfo());
		actual = actual->path;
	}
}
