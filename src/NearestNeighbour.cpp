#include "algoritmos.h"

/**
 * Aplicacao de o algoritmo Nearest Neighbour ao Grafo par resolucao do TSP com camiao de tamanho ilimitado
 */
void nearestNeighbour(Graph<Contentor> &grafo,Camiao &c) {
	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {
		grafo.getVertexSet()[i]->setVisited(false);
	}
	Vertex<Contentor>* actual = grafo.getVertexSet()[0];
	c.addContentor(actual->getInfo());
	Vertex<Contentor>* proximo;
	unsigned int pesoMinimo = INT_INFINITY;
	actual->setVisited(true);

	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {
		for (unsigned int j = 0; j < actual->getAdj().size(); j++) {
			if (actual->getAdj()[j].getWeight() < pesoMinimo && !actual->getAdj()[j].getDest()->isVisited()) {
				if ((actual->getAdj()[j].getDest()->getInfo().getQuantidadeMaxima() == 0) && i < grafo.getNumVertex() - 1) {
					continue;
				} else {
					pesoMinimo = actual->getAdj()[j].getWeight();
					proximo = actual->getAdj()[j].getDest();
				}
			}
		}
		if (!(proximo->getInfo() == actual->getInfo())) {
			actual->path = proximo;
			c.addContentor(proximo->getInfo());
		}
		actual = proximo;
		actual->setVisited(true);
		pesoMinimo = INT_INFINITY;

	}

}

/**
 * Aplicacao de o algoritmo Nearest Neighbour ao Grafo par resolucao do TSP com camiao de tamanho limitado
 */
void nearestNeighbourCamiao(Graph<Contentor> &grafo, Camiao &c) {
	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {
		grafo.getVertexSet()[i]->path = NULL;
	}

	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {
		grafo.getVertexSet()[i]->setVisited(false);
	}

	Vertex<Contentor>* actual = grafo.getVertexSet()[0];
	c.addContentor(actual->getInfo());
	Vertex<Contentor>* proximo;
	unsigned int lixoMaior = 0;
	actual->setVisited(true);

	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {
		for (unsigned int j = 0; j < actual->getAdj().size(); j++) {

			if (actual->getAdj()[j].getDest()->getInfo().getQuantidadeLixo() > lixoMaior && !(actual->getAdj()[j].getDest()->isVisited())) {
				if ((actual->getAdj()[j].getDest()->getInfo().getQuantidadeMaxima() == 0)) {
					continue;
				} else {
					if ((actual->getAdj()[j].getDest()->getInfo().getQuantidadeLixo() + c.getQuantidadeLixo()) < c.getCapacidadeMaxima()) {
						lixoMaior = actual->getAdj()[j].getDest()->getInfo().getQuantidadeLixo();
						proximo = actual->getAdj()[j].getDest();
					}
				}
			}
		}

		actual->setVisited(true);

		//Acabou apanhar lixo
		if (actual->getInfo() == proximo->getInfo()) {
			actual->path = grafo.getVertexSet()[grafo.getNumVertex() - 1];
			c.addContentor(findVertexId(grafo, grafo.getVertexSet()[grafo.getNumVertex() - 1]->getInfo().getId())->getInfo());
			return;
		}

		if (!(proximo->getInfo() == actual->getInfo())) {
			actual->path = proximo;
			c.addContentor(proximo->getInfo());
			proximo->getInfo().setQuantidadeLixo(0);
		}

		actual = proximo;
		lixoMaior = 0;
	}

}

/**
 * Encontra um vertice no grafo pelo seu id e retorna a posicao de memoria
 */
Vertex<Contentor>* findVertexId(Graph<Contentor> &grafo, int id) {
	for (unsigned int j = 0; j < grafo.getVertexSet().size(); j++) {
		if (id == grafo.getVertexSet()[j]->getInfo().getId()) {
			return grafo.getVertexSet()[j];
		}
	}
	return NULL;
}
