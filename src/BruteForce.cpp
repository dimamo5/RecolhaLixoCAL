#include "algoritmos.h"
#include <algorithm>

void iguala_arrays(int v[], int a[], int size) {

	for (int i = 0; i < size; i++) {
		v[i] = a[i];
	}
}

void brute_force(Graph<Contentor> &grafo) {

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
	}
}

void brute_force_camiao(Graph<Contentor> &grafo,Camiao &c) {

	int sum = 0, max_peso = 0 ;
	int size =  grafo.getNumVertex(),indice = size-1;
	int route[size], vert[size];

	for (unsigned int i = 0; i < grafo.getNumVertex(); i++) {

		grafo.getVertexSet()[i]->path = NULL;
		vert[i] = i;
	}

	for(int i = 0; i < size; i++)
		cout << vert[i] << " ";

	cout << "size " << size << endl;
	cin.get();

	//int indice_glob;

	while (std::next_permutation(vert+1, vert + size-1)) {

		for (int i = 0; i < size-1; i++) {

			if(sum + grafo.getVertexSet()[vert[i]]->getInfo().getQuantidadeLixo() <= c.getCapacidadeMaxima()){
				sum += grafo.getVertexSet()[vert[i]]->getInfo().getQuantidadeLixo();
				indice = i;
			}
			else {
				indice = i;
				break;
			}
		}

		if (sum > max_peso) {
			//		indice_glob = indice;
			max_peso = sum;
			iguala_arrays(route, vert, size);
		}
		sum = 0;
	}

	if(indice +1 < size){
		route[indice+1] = size -1 ;
	}
	else if (indice == size-1)
		indice--;

	cout << "peso " << max_peso << endl;
	cout << "size " << size << endl;
	cout << "indice" << indice << endl;

	int ultimo_ind,counter = indice+1;

	for (unsigned int i = 0; i < size-1, counter > 0; i++) {

		cout << grafo.getVertexSet()[route[i]]->getInfo().getId() << endl;

		if(grafo.getVertexSet()[route[i]]->getInfo().isPrioritario() || i == 0 || i == indice){
			ultimo_ind = i;
			counter--;

			c.addContentor(grafo.getVertexSet()[route[i]]->getInfo());
			grafo.getVertexSet()[route[i]]->getInfo().setQuantidadeLixo(0);

			if(grafo.getVertexSet()[route[i + 1]]->getInfo().isPrioritario()){
				grafo.getVertexSet()[route[i]]->path = grafo.getVertexSet()[route[i + 1]];
				continue;
			}

			for(int j = i; j <= indice; j++){

				if(grafo.getVertexSet()[route[j+1]]->getInfo().isPrioritario()){
					grafo.getVertexSet()[route[i]]->path = grafo.getVertexSet()[route[j + 1]];
					break;
				}
			}
		}
	}

	cout <<"capacidade camiao " <<  c.getQuantidadeLixo() << endl;
}

void brute_force_camiao_aux(Graph<Contentor> &grafo,Camiao &c) {

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

	//até aqui está tudo bem
	for(int i = 0; i < size; i++)
		cout << route[i] << " ";

	cout << "ind_glob "<< indice_glob << endl;

	if( indice_glob < size){
		cout << "entra"<<endl;
		route[indice_glob] = grafo.getNumVertex()-1 ;
	}

	cout << "peso " << max_peso << endl;
	cout << "size " << size << endl;
	cout << "indice " << indice_glob << endl;

	for(int i = 0; i < size; i++)
		cout << route[i] << " ";
	cin.get();

	for (unsigned int i = 0; i < indice_glob ; i++) {

		cout <<"id:"<<grafo.getVertexSet()[route[i]]->getInfo().getId() << endl;

		c.addContentor(grafo.getVertexSet()[route[i]]->getInfo());
		grafo.getVertexSet()[route[i]]->getInfo().setQuantidadeLixo(0);

		if(i != indice_glob)
			grafo.getVertexSet()[route[i]]->path = grafo.getVertexSet()[route[i + 1]];
	}

	cout <<"capacidade camiao " <<  c.getQuantidadeLixo() << endl;
}
