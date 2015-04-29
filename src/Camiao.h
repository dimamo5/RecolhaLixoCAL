/*
 * Camiao.h
 *
 *  Created on: 21/04/2015
 *      Author: Diogo Moura
 */

#ifndef CAMIAO_H_
#define CAMIAO_H_

#include "Contentor.h"
#include "Graph.h"
#include <vector>

/**
 * Classe representativa de um camiao
 * Cada camiao contem uma capacidade maxima comum a todos os camioes, a quantidade de lixo no momento,
 * a distancia que percorreu, e a rota
 */
class Camiao {
private:
	static int capacidadeMaxima;
	static unsigned int nextId;
	unsigned int id;
	unsigned int quantidadeLixo;
	unsigned int distanciaPercorrida;
	vector<Contentor> rota;

public:
	Camiao();
	Camiao(unsigned int id,unsigned int quantidadeLixo);
	static unsigned int getCapacidadeMaxima();
	static void setCapacidadeMaxima(unsigned int cMaxima);
	unsigned int getId() const;
	void setId(unsigned int id);
	unsigned int getQuantidadeLixo() const;
	void setQuantidadeLixo(unsigned int quantidadeLixo);
	static unsigned int getNextId();
	static void setNextId(unsigned int nextId);
	vector<Contentor> getRota() const;
	void addContentor(Contentor c);
	void addDist(unsigned int d);
	unsigned int getDist() const;
	void calcRotaCamiao(Graph<Contentor> &grafo);
	void print();


};

#endif /* CAMIAO_H_ */
