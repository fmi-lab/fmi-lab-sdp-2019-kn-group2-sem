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

	void addBiDirectionalRelation(V v1, V v2, COST cost = DEFAULT_COST) {
		addRelation(v1, v2, cost);
		addRelation(v2, v1, cost);
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

	COST findShortestPath(V from, V to) {
		int fromIndex = findIndex(from);
		int toIndex = findIndex(to);

		return findShortestPathByIndex(fromIndex, toIndex);
	}

	vector<V> findPathBFS(V from, V to) {
		int fromIndex = findIndex(from);
		int toIndex = findIndex(to);

		return findPathBFSByIndex(fromIndex, toIndex);
	}

	vector<V> findPathBFSv2(V from, V to) {
		int fromIndex = findIndex(from);
		int toIndex = findIndex(to);

		return findPathBFSByIndexPathByQueue(fromIndex, toIndex);
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

	vector<V> findPathBFSByIndexPathByQueue(int from, int to) {
		vector<bool> visited;
		visited.resize(vertexes.size());
		
		queue<vector<int> > nextSteps;
		nextSteps.push(vectorOf(from));

		visited[from] = true;

		while (!nextSteps.empty()) {
			vector<int> currentPath = nextSteps.front();
			int currentIndex = currentPath[currentPath.size() - 1];

			nextSteps.pop();
			if (currentIndex == to) {
				return toVertexes(currentPath);
			}

			visited[currentIndex] = true;
			for (auto neighbour : relations[currentIndex]) {
				int neighbourIndex = neighbour.first;
				if (!visited[neighbourIndex]) {
					nextSteps.push(extendWith(currentPath, neighbourIndex));
					visited[neighbourIndex] = true;
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

	vector<V> toVertexes(vector<int> indexes) {
		vector<V> result;
		for (auto index : indexes) {
			result.push_back(vertexes[index]);
		}
		return result;
	}

	vector<int> vectorOf(int elem) {
		vector<int> result;
		result.push_back(elem);
		return result;
	}

	vector<int> extendWith(vector<int> v, int elem) {
		v.push_back(elem);
		return v;
	}

	int getCheapestNotVisitedIndex(vector<COST>& cost, vector<bool>& visited) {
		int cheapestIndex = -1;
		int cheapestCost = -1;
		for (int i = 0; i < cost.size(); i++) {
			if (visited[i]) {
				continue;
			}
			if (cost[i] == -1) {
				continue;
			}
			if (cheapestCost == -1 || cheapestCost > cost[i]) {
				cheapestIndex = i;
				cheapestCost = cost[i];
			}
		}
		return cheapestIndex;
	}


	COST findShortestPathByIndex(int fromIndex, int toIndex) {
		vector<COST> cost;
		cost.resize(vertexes.size(), -1);

		vector<bool> visited;
		visited.resize(vertexes.size(), false);

		cost[fromIndex] = 0;

		while (true) {
			int currentIndex = getCheapestNotVisitedIndex(cost, visited);
			cout << "currentIndex: " << currentIndex << endl;
			for (int i = 0; i < cost.size(); i++) {
				cout << i << " | " << cost[i] << " | " << (visited[i] ? "visited" : "not")  << endl;
			}
			if (currentIndex == -1) {
				break;
			}

			visited[currentIndex] = true;
			vector<pair<int, COST> > neighbours = relations[currentIndex];
			for (auto neighbour : neighbours) {
				int neighbourIndex = neighbour.first;
				int neighbourCost = neighbour.second;

				if (cost[neighbourIndex] == - 1 || neighbourCost + cost[currentIndex] < cost[neighbourIndex]) {
					cost[neighbourIndex] = neighbourCost + cost[currentIndex];
				}
			}
		}


		return cost[toIndex];
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

void testFindPath() {
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
		cout << "Path with: Recursive DFS" << endl;
		auto path = graph.findPath(pesho, dragan);
		printPath(path);
	}

	{ // BFS
		cout << "Path with: BFS" << endl;
		auto path = graph.findPathBFS(gogo, dragan);
		printPath(path);
	}

	{ // BFS (with full path in queue)
		cout << "Path with: BFS (with full path in queue)" << endl;
		auto path = graph.findPathBFSv2(gogo, dragan);
		printPath(path);
	}


	{ // DFS with Stack
		cout << "Path with: DFS with Stack" << endl;
		auto path = graph.findPathDFS(gogo, dragan);
		printPath(path);
	}
}

void testShortestPath() {
	Graph<string> graph;
	string a = "A";
	graph.addVertex("A");
	string x1 = "x1";
	graph.addVertex("x1");
	string x2 = "x2";
	graph.addVertex("x2");
	string x3 = "x3";
	graph.addVertex("x3");
	string x4 = "x4";
	graph.addVertex("x4");
	string x5 = "x5";
	graph.addVertex("x5");
	string x6 = "x6";
	graph.addVertex("x6");
	string x7 = "x7";
	graph.addVertex("x7");
	string x8 = "x8";
	graph.addVertex("x8");
	string b = "B";
	graph.addVertex("B");

	graph.addBiDirectionalRelation(a, x1, 1);
	graph.addBiDirectionalRelation(a, x2, 5);
	graph.addBiDirectionalRelation(a, x3, 120);

	graph.addBiDirectionalRelation(x1, x4, 100);
	graph.addBiDirectionalRelation(x2, x5, 120);
	graph.addBiDirectionalRelation(x3, x8, 100);

	graph.addBiDirectionalRelation(x4, x6, 1);
	graph.addBiDirectionalRelation(x5, x6, 3);
	graph.addBiDirectionalRelation(x5, x7, 10);
	graph.addBiDirectionalRelation(x5, x8, 7);

	graph.addBiDirectionalRelation(x6, b, 1);
	graph.addBiDirectionalRelation(x7, b, 5);
	graph.addBiDirectionalRelation(x8, b, 3);

	cout << "Shortest path A->B: " << endl;
	cout << graph.findShortestPath(a, b) << endl;
}

int main() {
	// testFindPath();
	testShortestPath();

	return 0;
}

