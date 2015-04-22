/*
 * Camiao.h
 *
 *  Created on: 21/04/2015
 *      Author: Diogo Moura
 */

#ifndef CAMIAO_H_
#define CAMIAO_H_

class Camiao {
private:
	static unsigned int nextId;
	unsigned int id;
	unsigned int quantidadeLixo;
	unsigned int capacidadeMaxima;
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
};

#endif /* CAMIAO_H_ */
