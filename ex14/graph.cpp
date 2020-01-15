#include <iostream>
#include <vector>
#include <queue>
#include <stack>

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

	vector<V> findPath(V from, V to) {
		int fromIndex = findIndex(from);
		int toIndex = findIndex(to);

		vector<bool> visited;
		visited.resize(vertexes.size());

		/* Option 2
		for (int i = 0; i < vertexes.size(); i++) {
		visited.push_back(false);
		}*/

		return findPathByIndex(fromIndex, toIndex, visited);
	}

	vector<V> findPathBFS(V from, V to) {
		int fromIndex = findIndex(from);
		int toIndex = findIndex(to);

		return findPathBFSByIndex(fromIndex, toIndex);
	}

	vector<V> findPathDFS(V from, V to) {
		int fromIndex = findIndex(from);
		int toIndex = findIndex(to);

		return findPathDFSByIndex(fromIndex, toIndex);
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

	// Depth First Search
	vector<V> findPathByIndex(int from, int to, vector<bool>& visited) {
		if (visited[from]) {
			return vector<V>();
		}
		if (from == to) {
			vector<V> result;
			result.push_back(vertexes[from]);
			return result;
		}

		visited[from] = true;
		for (auto neighbour : relations[from]) {
			int neighbourIndex = neighbour.first;
			vector<V> path = findPathByIndex(neighbourIndex, to, visited);
			if (!path.empty()) {
				path.insert(path.begin(), vertexes[from]);
				return path;
			}
		}
		return vector<V>();
	}

	vector<V> buildPathVector(const vector<int>& prev, int idx) {
		vector<V> path;
		while (prev[idx] != -1) {
			path.insert(path.begin(), vertexes[idx]);
			idx = prev[idx];
		}
		path.insert(path.begin(), vertexes[idx]);
		return path;
	}

	vector<V> findPathDFSByIndex(int from, int to) {
		vector<bool> visited;
		visited.resize(vertexes.size());
		vector<int> prev;
		prev.resize(vertexes.size(), -1);

		stack<int> nextSteps;
		nextSteps.push(from);

		while (!nextSteps.empty()) {
			int currentIndex = nextSteps.top();
			nextSteps.pop();
			if (currentIndex == to) {
				return buildPathVector(prev, currentIndex);
			}

			if (visited[currentIndex]) {
				continue;
			}

			visited[currentIndex] = true;
			for (auto neighbour : relations[currentIndex]) {
				int neighbourIndex = neighbour.first;
				if (!visited[neighbourIndex]) {
					prev[neighbourIndex] = currentIndex;
					nextSteps.push(neighbourIndex);
				}
			}
		}
		return vector<V>();
	}

	vector<V> findPathBFSByIndex(int from, int to) {
		vector<bool> visited;
		visited.resize(vertexes.size());
		vector<int> prev;
		prev.resize(vertexes.size(), -1);

		queue<int> nextSteps;
		nextSteps.push(from);
		visited[from] = true;

		while (!nextSteps.empty()) {
			int currentIndex = nextSteps.front();
			nextSteps.pop();
			if (currentIndex == to) {
				return buildPathVector(prev, currentIndex);
			}

			visited[currentIndex] = true;
			for (auto neighbour : relations[currentIndex]) {
				int neighbourIndex = neighbour.first;
				if (!visited[neighbourIndex]) {
					prev[neighbourIndex] = currentIndex;
					nextSteps.push(neighbourIndex);
					visited[neighbourIndex] = true;
				}
			}
		}
		return vector<V>();
	}

private:
	vector<V> vertexes;
	vector<vector<pair<int, COST> > > relations;
};

void printPath(vector<string> path) {
	cout << "Path exists? " << (!path.empty()) << endl;
	for (auto step : path) {
		cout << step << " ";
	}
	cout << endl;
}

int main() {
	Graph<string> graph;
	string pesho = "pesho";
	graph.addVertex(pesho);

	string mimi = "mimi";
	graph.addVertex(mimi);

	string petya = "petya";
	graph.addVertex(petya);

	string ivan = "ivan";
	graph.addVertex(ivan);

	string dragan = "dragan";
	graph.addVertex(dragan);

	string gogo = "gogo";
	graph.addVertex(gogo);

	graph.addRelation(pesho, gogo);
	graph.addRelation(gogo, pesho);

	graph.addRelation(pesho, mimi);
	graph.addRelation(mimi, pesho);

	graph.addRelation(mimi, petya);
	graph.addRelation(petya, mimi);

	graph.addRelation(petya, ivan);

	graph.addRelation(mimi, ivan);
	graph.addRelation(ivan, mimi);

	graph.addRelation(ivan, dragan);


	{ // Recursive DFS
		auto path = graph.findPath(pesho, dragan);
		printPath(path);
	}

	{ // BFS
		auto path = graph.findPathBFS(gogo, dragan);
		printPath(path);
	}

	{ // DFS with Stack
		auto path = graph.findPathDFS(gogo, dragan);
		printPath(path);
	}

	return 0;
}