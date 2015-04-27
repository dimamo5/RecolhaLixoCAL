#include "algoritmos.h"

int bound, row, col, size, *pencost;

void branchBound(Graph<Contentor> &grafo,Camiao &c) {

	vector<int> path;

	int x[grafo.getNumVertex()];
	pencost = x;

	int row = rowReduction(grafo.getW(), grafo.getNumVertex());
	int col = colReduction(grafo.getW(), grafo.getNumVertex());

	int ** newW = new int *[grafo.getNumVertex()];

	for (int i = 0; i < grafo.getNumVertex(); i++) {
		newW[i] = new int[grafo.getNumVertex()];
		for (int j = 0; j < grafo.getNumVertex(); j++) {
			newW[i][j] = grafo.getW()[i][j];
		}
	}

	path.push_back(0);

	branchBoundRec(grafo, path, 0, newW);

	path.push_back(getVertexIndice(grafo, grafo.getVertexSet()[grafo.getNumVertex() - 1]->getInfo().getId()));

	for (unsigned int i = 0; i < path.size() - 1; i++) {
		grafo.getVertexSet()[path[i]]->path = grafo.getVertexSet()[path[i + 1]];
		c.addContentor(grafo.getVertexSet()[path[i]]->getInfo());
	}

}

void branchBoundRec(Graph<Contentor> &grafo, vector<int> &path, int id, int** W) {

	Vertex<Contentor>* actual = grafo.getVertexSet()[id];

	if (path.size() == grafo.getNumVertex() - 1) {
		return;
	}

	int minBound = INT_MAX, novoId, idComparar;

	for (unsigned int i = 0; i < actual->getAdj().size(); i++) {
		idComparar = getVertexIndice(grafo, actual->getAdj()[i].getDest()->getInfo().getId());

		if (checkBounds(id, idComparar, W, grafo.getNumVertex()) < minBound && !visitedPath(path, idComparar)
				&& idComparar != getVertexIndice(grafo, grafo.getVertexSet()[grafo.getNumVertex() - 1]->getInfo().getId())) {
			minBound = checkBounds(id, getVertexIndice(grafo, actual->getAdj()[i].getDest()->getInfo().getId()), W, grafo.getNumVertex());
			novoId = getVertexIndice(grafo, actual->getAdj()[i].getDest()->getInfo().getId());
		}
	}
	path.push_back(novoId);

	for (int i = 0; i < grafo.getNumVertex(); i++) {
		W[id][i] = INT_INFINITY;
	}

	for (int i = 0; i < grafo.getNumVertex(); i++) {
		W[i][novoId] = INT_INFINITY;
	}

	W[novoId][id] = INT_INFINITY;

	rowReduction(W, grafo.getNumVertex());
	colReduction(W, grafo.getNumVertex());

	branchBoundRec(grafo, path, novoId, W);

}

int checkBounds(int orig, int dest, int**w, int size) {

	pencost[0] = bound;

	int reduced_size = size; //actualizar esta variavel convenientemente
	int ** reduced = new int *[size];

	for (int i = 0; i < size; i++) {
		reduced[i] = new int[size];
		for (int j = 0; j < size; j++) {
			reduced[i][j] = w[i][j];
		}
	}

	for (int i = 0; i < size; i++) {
		reduced[orig][i] = INT_INFINITY;
	}

	for (int i = 0; i < size; i++) {
		reduced[i][dest] = INT_INFINITY;
	}
	reduced[dest][orig] = INT_INFINITY;

	rowReduction(reduced, reduced_size);
	colReduction(reduced, reduced_size);

	pencost[dest] = pencost[orig] + row + col + w[orig][dest];

	return pencost[dest];
}

int calcMinRow(int ** W, int size, int row) {
	unsigned int min = INT_MAX;
	for (unsigned int i = 0; i < size; i++) {
		if (row == i) {
			continue;
		} else if (W[row][i] < min) {
			min = W[row][i];
		}
	}
	return min;
}

int calcMinColumn(int ** W, int size, int col) {
	unsigned int min = INT_MAX;
	for (unsigned int i = 0; i < size; i++) {
		if (col == i) {
			continue;
		} else if (W[i][col] < min) {
			min = W[i][col];
		}
	}

	return min;
}

int rowReduction(int ** w, int size) {

	row = 0;
	int rmin;

	for (int i = 0; i < size; i++) {
		rmin = calcMinRow(w, size, i);

		if (rmin != INT_INFINITY)
			row += rmin;

		for (int j = 0; j < size; j++) {
			if (!(w[i][j] == INT_INFINITY || i == j))
				w[i][j] -= rmin;
		}
	}
	return row;
}

int colReduction(int **w, int size) {

	col = 0;
	int cmin;

	for (int i = 0; i < size; i++) {
		cmin = calcMinColumn(w, size, i);

		if (cmin != INT_INFINITY)
			col += cmin;

		for (int j = 0; j < size; j++) {
			if (!(w[j][i] == INT_INFINITY || i == j))
				w[j][i] -= cmin;
		}
	}
	return col;
}

bool visitedPath(vector<int> &path, int id) {
	for (unsigned int i = 0; i < path.size(); i++) {
		if (id == path[i]) {
			return true;
		}
	}
	return false;
}

int getVertexIndice(Graph<Contentor> &grafo, int id) {
	for (int i = 0; i < grafo.getNumVertex(); i++) {
		if (grafo.getVertexSet()[i]->getInfo().getId() == id) {
			return i;
		}
	}
	return -1;
}
