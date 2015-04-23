/*
 * Camiao.cpp
 *
 *  Created on: 21/04/2015
 *      Author: Utilizador
 */

#include "Camiao.h"

unsigned int Camiao::nextId=1;

Camiao::Camiao() {
	this->id=nextId;
	nextId++;
	this->quantidadeLixo=0;
	this->capacidadeMaxima=1000;
}

Camiao::Camiao(unsigned int id, unsigned int quantidadeLixo,
		unsigned int capacidadeMaxima):id(id),quantidadeLixo(quantidadeLixo),capacidadeMaxima(capacidadeMaxima) {

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

void Camiao::addContentor(Contentor c){
	this->quantidadeLixo+=c.getQuantidadeLixo();

	rota.push_back(c);
}

vector<Contentor> Camiao::getRota() const{
	return rota;
}

