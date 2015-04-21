#include "Contentor.h"

unsigned int Contentor::nextId=1; //Id Comeca a 1

Contentor::Contentor(){
	this->id=nextId;
	nextId++;
	this->quantidadeLixo=0;
	this->rua="Rua XPTO";
}
Contentor::Contentor(unsigned int id,string rua,unsigned int quantidadeLixo):id(id),rua(rua),quantidadeLixo(quantidadeLixo){
}


unsigned int Contentor::getId() const {
	return id;
}

void Contentor::setId(unsigned int id) {
	this->id = id;
}

unsigned int Contentor::getNextId() {
	return nextId;
}

void Contentor::setNextId(unsigned int nextId) {
	this->nextId = nextId;
}

unsigned int Contentor::getQuantidadeLixo() const {
	return quantidadeLixo;
}

void Contentor::setQuantidadeLixo(unsigned int quantidadeLixo) {
	this->quantidadeLixo = quantidadeLixo;
}

string Contentor::getRua() const {
	return rua;
}

void Contentor::setRua(string rua) {
	this->rua = rua;
}
