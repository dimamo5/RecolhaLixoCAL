#include "Contentor.h"

unsigned int Contentor::nextId=1; //Id Comeca a 1

Contentor::Contentor(){
	this->id=nextId;
	nextId++;
	this->quantidadeLixo=0;
	this->rua="Rua XPTO";
}
Contentor::Contentor(unsigned int id,string rua,unsigned int quantidadeLixo,unsigned int quantidadeMaxima):id(id),rua(rua),quantidadeLixo(quantidadeLixo),quantidadeMaxima(quantidadeMaxima){
}


bool Contentor::operator==(const Contentor &c2) const{
	if(this->id==c2.id){
		return true;
	}else{
		return false;
	}
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
	Contentor::nextId = nextId;
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

bool Contentor::isPrioritario() {
	if(quantidadeMaxima==0){
		return false;
	}

	if(((double)quantidadeLixo/quantidadeMaxima)>limite){
		return true;

	}else return false;
}
