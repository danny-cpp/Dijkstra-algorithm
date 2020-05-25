#include "dijkstra.h"
#include "heap.h"
#include <utility>
#include <unordered_set>

#include <unordered_map>
#include "wdigraph.h"

using namespace std;

// for brevity
// typedef introduces a synonym (alias) 
// for the type specified
typedef pair<int, long long> PIL;

// again, for brevity
// used to store a vertex v and its predecessor pair (u,d) on the search
// where u is the node prior to v on a path to v of cost d
// eg. PIPIL x;
// x.first is "v", x.second.first is "u" and x.second.second is "d" from this
typedef pair<int, PIL> PIPIL;

typedef pair<int, int> Edge;

typedef pair<Edge, long long> Edge_w_Cost;

void dijkstra(const WDigraph& graph, int startVertex, unordered_map<int, PIL>& tree) {

	// Use heap class to store edges associate with length, thus, has heap property. The root will always have
	// the lowest distance
	BinaryHeap<Edge, long long> my_heap;
	Edge temp = make_pair(startVertex, startVertex);

	my_heap.insert(temp, 0);

	while (my_heap.size() > 0) {
		
		// Pop the root, which guarantees the lowest distance
		auto temp = my_heap.min();
		my_heap.popMin();

		// The rest follows dijkstra pseudocode, but with re-pairing edge-dist or vertex-(vertex-dist)
		int v = temp.item.second;
		int u = temp.item.first;
		long long time = temp.key;

		auto finder = tree.find(v); 
		if (finder == tree.end()) {
			tree[v] = PIL(u, time);
			
			for (auto iter = graph.neighbours(v); iter != graph.endIterator(v); iter++) {
				my_heap.insert(make_pair(v, *iter), time + graph.getCost(v, *iter));
			}
		}
	}


}
