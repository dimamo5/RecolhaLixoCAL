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
