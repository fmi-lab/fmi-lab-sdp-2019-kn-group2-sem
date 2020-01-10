#include <iostream>
#include <vector>

using namespace std;


class Person {
};

template <typename V, typename COST = int, COST DEFAULT_COST = 0>
class Graph {
public:
	void addVertex(V vertex) {
		vertexes.push_back(vertex);
		
		// add default empty relations for the current vertex
		vector<pair<int, COST> > emptyRelations;
		relations.push_back(emptyRelations);

		addRelation(vertex, vertex, DEFAULT_COST);
	}

	void addRelation(V v1, V v2, COST cost = DEFAULT_COST) {
		int indexOfV1 = findIndex(v1);
		int indexOfV2 = findIndex(v2);

		removeRelationIfExists(indexOfV1, indexOfV2);
		addRelationByIndex(indexOfV1, indexOfV2, cost);
	}

private:
	void addRelationByIndex(int v1, int v2, COST cost) {
		relations[v1].push_back(pair<int, COST>(v2, cost));
	}

	void removeRelationIfExists(int v1, int v2) {
		vector<pair<int, COST> > v1Neighbours = relations[v1];

		for (int i = 0; i < v1Neighbours.size(); i++) {
			if (v1Neighbours[i].first == v2) {
				v1Neighbours.erase(v1Neighbours.begin() + i);
				return;
			}
		}
	}

	int findIndex(V searchFor) {
		for (int i = 0; i < vertexes.size(); i++) {
			if (searchFor == vertexes[i]) {
				return i;
			}
		}
		return -1;
	}

private:
	vector<V> vertexes;
	vector<vector<pair<int, COST> > > relations;
};

int main() {
	Graph<string> graph;
	string pesho = "pesho";
	graph.addVertex(pesho);

	string mimi = "mimi";
	graph.addVertex(mimi);

	graph.addRelation(pesho, mimi);
	graph.addRelation(mimi, pesho);


	return 0;
}



