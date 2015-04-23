/*
 * Camiao.h
 *
 *  Created on: 21/04/2015
 *      Author: Diogo Moura
 */

#ifndef CAMIAO_H_
#define CAMIAO_H_

#include "Contentor.h"
#include <vector>

class Camiao {
private:
	static unsigned int nextId;
	unsigned int id;
	unsigned int quantidadeLixo;
	unsigned int capacidadeMaxima;

	vector<Contentor> rota;
public:
	Camiao();
	Camiao(unsigned int id,unsigned int quantidadeLixo,unsigned int capacidadeMaxima);
	unsigned int getCapacidadeMaxima() const;
	void setCapacidadeMaxima(unsigned int capacidadeMaxima);
	unsigned int getId() const;
	void setId(unsigned int id);
	unsigned int getQuantidadeLixo() const;
	void setQuantidadeLixo(unsigned int quantidadeLixo);
	static unsigned int getNextId();
	static void setNextId(unsigned int nextId);
	void addContentor(Contentor c);
	vector<Contentor> getRota() const;
};

#endif /* CAMIAO_H_ */
