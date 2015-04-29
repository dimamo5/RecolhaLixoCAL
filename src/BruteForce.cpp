#include "algoritmos.h"
#include <algorithm>

/**
 * Iguala todos os elementos de 2 arrays
 */
void iguala_arrays(int v[], int a[], int size) {

	for (int i = 0; i < size; i++) {
		v[i] = a[i];
	}
}

/**
 * Algoritmo de brute-force com premutações para resolução de um problema do tipo TSP
 */
void brute_force(Graph<Contentor> &grafo,Camiao &c) {

	int sum = 0, min_dist = INT_INFINITY;
	int size = grafo.getNumVertex();

	int route[size], vert[size];

	for (int i = 0; i < size; i++) {
		vert[i] = i;
	}

	//Enquanto for possivel permutar elementos
	while (std::next_permutation(vert + 1, vert + size - 1)) {

		//começa a somar as distâncias entre vértices e verifica se são menores que as anteriores
		for (int i = 0; i < size - 1; i++) {

			if (grafo.getW()[vert[i]][vert[i + 1]] == INT_INFINITY)
				sum = INT_INFINITY;

			if (sum != INT_INFINITY)
				sum += grafo.getW()[vert[i]][vert[i + 1]];
			else break; //se der porcaria e por causa disto
		}

		//se o somatório for menor que a distancia minima anterior passa a ser ela a nova min_dist
		if (sum < min_dist) {
			min_dist = sum;
			iguala_arrays(route, vert, size);
		}
		sum = 0;
	}
//construção do caminho
	for (unsigned int i = 0; i < size - 1; i++) {
		grafo.getVertexSet()[route[i]]->path = grafo.getVertexSet()[route[i + 1]];
		c.addContentor(grafo.getVertexSet()[route[i]]->getInfo());
	}
}

void brute_force_camiao(Graph<Contentor> &grafo,Camiao &c) {

	int sum = 0, max_peso = 0 ,size =0, indice, indice_glob;

	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {

		grafo.getVertexSet()[i]->path = NULL;

		if(grafo.getVertexSet()[i]->getInfo().isPrioritario())
			size++;
	}

	size+=2; //+2: central + recolha

	int route[size], vert[size];

	vert[0] = 0;
	vert[size-1] = grafo.getNumVertex()-1;

	for (unsigned int i = 1, j=1; i < grafo.getNumVertex()-1; i++) {//inicializa vert array

		if(grafo.getVertexSet()[i]->getInfo().isPrioritario()){
			vert[j] = i;
			j++;
		}
	}

	while (std::next_permutation(vert+1, vert + size-1)) {

		for (int i = 0; i < size; i++) {

			if(sum + grafo.getVertexSet()[vert[i]]->getInfo().getQuantidadeLixo() <= c.getCapacidadeMaxima()){
				sum += grafo.getVertexSet()[vert[i]]->getInfo().getQuantidadeLixo();
				indice = i;
				if(sum == c.getCapacidadeMaxima()){
					break;
				}

			}
			else {
				indice = i;
				break;
			}
		}

		if (sum > max_peso) {
			indice_glob = indice;
			max_peso = sum;
			iguala_arrays(route, vert, size);
		}
		sum = 0;
	}

	if( indice_glob < size){
		route[indice_glob] = grafo.getNumVertex()-1 ;
	}

	for (unsigned int i = 0; i < indice_glob ; i++) {

		c.addContentor(grafo.getVertexSet()[route[i]]->getInfo());
		grafo.getVertexSet()[route[i]]->getInfo().setQuantidadeLixo(0);

		if(i != indice_glob){
			grafo.getVertexSet()[route[i]]->path = grafo.getVertexSet()[route[i + 1]];
		}
	}
	c.addContentor(grafo.getVertexSet()[grafo.getNumVertex()-1]->getInfo());
}
