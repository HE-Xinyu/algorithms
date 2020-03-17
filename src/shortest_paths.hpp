#include <vector>
#include <type_traits>
#include <climits>

namespace shortest_path {
	using std::vector;
	using std::pair;
	using std::is_same;
	using std::min;

	template<typename Weight>
	class Base {
	public:
		using AdjacencyList = vector<vector<pair<int, Weight>>>;
		Base(AdjacencyList _adj) : adj(_adj) {}

		// single-source shortest path
		// returns a pair: (1D shortest weight vertex, whether the graph has negative cycle) 
		virtual pair<vector<Weight>, bool> sssp(int s) const = 0;

		// single-source shortest path
		// returns a pair: (2D shortest weight vertex, whether the graph has negative cycle)
		virtual pair<vector<vector<Weight>>, bool> apsp(int s) const = 0;

	protected:
		// adjacency list and the weight of each edge.
		AdjacencyList adj;
	};

	template<typename Weight>
	class BellmanFord : public Base<Weight> {
		
	public:
		using AdjacencyList = vector<vector<pair<int, Weight>>>;
		BellmanFord(AdjacencyList _adj) : Base<Weight>(_adj) {}

		pair<vector<Weight>, bool> sssp(int s) const override {
			size_t n = this->adj.size();
			vector<Weight> dist;
			if (is_same<Weight, int>::value) {
				dist = vector<Weight>(n, INT_MAX / 2);
			}
			else if (is_same<Weight, double>::value) {
				dist = vector<Weight>(n, DBL_MAX / 2.0);
			}
			else {
				// not implemented.
				throw;
			}

			dist[s] = 0;

			for (int k = 0; k < n - 1; k++) {
				for (int u = 0; u < n; u++) {
					for (auto p : this->adj[u]) {
						dist[p.first] = min(dist[p.first], dist[u] + p.second);
					}
				}
			}
			
			// run one more loop.
			// if any distance is going to update, then there exists a negative cycle.
			for (int u = 0; u < n; u++) {
				for (auto p : this->adj[u]) {
					if (dist[p.first] > dist[u] + p.second) {
						return { dist, true };
					}
				}
			}
			return { dist, false };
		}

		pair<vector<vector<Weight>>, bool> apsp(int s) const override {
			throw;
		}

	};
}  // end of namespace shortest_path

