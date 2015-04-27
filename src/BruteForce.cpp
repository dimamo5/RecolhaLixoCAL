#include "algoritmos.h"
#include <algorithm>

void iguala_arrays(int v[], int a[], int size) {

	for (int i = 0; i < size; i++) {
		v[i] = a[i];
	}
}

void brute_force(Graph<Contentor> &grafo,Camiao &c) {

	int sum = 0, min_dist = INT_INFINITY;
	int size = grafo.getNumVertex();

	int route[size], vert[size];

	for (int i = 0; i < size; i++) {
		vert[i] = i;
	}

	while (std::next_permutation(vert + 1, vert + size - 1)) {

		for (int i = 0; i < size - 1; i++) {

			if (grafo.getW()[vert[i]][vert[i + 1]] == INT_INFINITY)
				sum = INT_INFINITY;

			if (sum != INT_INFINITY)
				sum += grafo.getW()[vert[i]][vert[i + 1]];
			else break; //se der porcaria e por causa disto
		}

		if (sum < min_dist) {
			min_dist = sum;
			iguala_arrays(route, vert, size);
		}
		sum = 0;
	}

	for (unsigned int i = 0; i < size - 1; i++) {
		grafo.getVertexSet()[route[i]]->path = grafo.getVertexSet()[route[i + 1]];
		c.addContentor(grafo.getVertexSet()[route[i]]->getInfo());
	}


}

/*void brute_force_camiao(Graph<Contentor> &grafo,Camiao &c) {

	int size =0,indice;

	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {
		grafo.getVertexSet()[i]->path = NULL;
		if(grafo.getVertexSet()[i]->getInfo().isPrioritario())
			size++;
	}

	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {
		grafo.getVertexSet()[i]->path = NULL;
		if(grafo.getVertexSet()[i]->getInfo().isPrioritario())
			size++;
	}


	int sum = 0, max_peso = 0;//, indice=size-1;

	int route[size], vert[size];

	for (int i = 0; i < size; i++) {
		vert[i] = i;
	}

	while (std::next_permutation(vert + 1, vert + size - 1)) {

		for (int i = 0; i < size - 1; i++) {

			if(sum + grafo.getVertexSet()[vert[i]]->getInfo().getQuantidadeLixo() <= c.getCapacidadeMaxima()){
				sum += grafo.getVertexSet()[vert[i]]->getInfo().getQuantidadeLixo();
			}
			else {
				indice = i;
				break;
			}
		}

		if (sum > max_peso) {
			max_peso = sum;
			iguala_arrays(route, vert, size);
		}
		sum = 0;
	}

	bool cenas = true;
	if(indice+1 < size){ //actualiza posicao da recolha na rota
		route[indice+1] = size-1;
		cenas = false
				;
	}

	cout << "peso " << max_peso << endl;
	cout << "size " << size << endl;
	cout << "ind  " << indice << endl;



	for (unsigned int i = 0; i <= indice; i++) {

		if(cenas){
			cenas = false;
			indice == size-1;
			indice--;
		}


		if(grafo.getVertexSet()[route[i]]->getInfo().getQuantidadeLixo() != 0 ){
			c.addContentor(grafo.getVertexSet()[route[i]]->getInfo());
			grafo.getVertexSet()[route[i]]->getInfo().setQuantidadeLixo(0);
			grafo.getVertexSet()[route[i]]->path = grafo.getVertexSet()[route[i + 1]];
		}
		else if (i == 0){

			for(int j=0; j < size; j++){ //verificar isto

				if(grafo.getVertexSet()[route[i]]->getInfo().isPrioritario()){
					c.addContentor(grafo.getVertexSet()[route[i]]->getInfo());
					grafo.getVertexSet()[route[i]]->path = grafo.getVertexSet()[route[j]];
				}
			}


		}
		else if (i == size-1){
			c.addContentor(grafo.getVertexSet()[route[i]]->getInfo());
			grafo.getVertexSet()[route[indice-1]]->path = grafo.getVertexSet()[route[i]];
		}
	}

	cout <<"capacidade camiao " <<  c.getQuantidadeLixo() << endl;
}
*/
