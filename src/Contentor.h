#ifndef CONTENTOR_H_
#define CONTENTOR_H_

#include <string>

using namespace std;

class Contentor{
private:
	static unsigned int nextId;
	unsigned int id;
	string rua;
	unsigned int quantidadeLixo,quantidadeMaxima;
	static const unsigned int limite=0.7;
public:
	Contentor();
	Contentor(unsigned int id,string rua,unsigned int quantidadeLixo,unsigned int quantidadeMaxima);
	bool operator==(const Contentor &c2) const;
	unsigned int getId() const;
	void setId(unsigned int id);
	static unsigned int getNextId();
	static void setNextId(unsigned int nextId);
	unsigned int getQuantidadeLixo() const;
	void setQuantidadeLixo(unsigned int quantidadeLixo);
	string getRua() const;
	void setRua(string rua);
	bool isPrioritario();
};
#endif
