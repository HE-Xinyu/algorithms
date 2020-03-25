#include <vector>
#include <type_traits>
#include <climits>
#include <queue>
#include <functional>
#include <tuple>

namespace shortest_path {
	using std::vector;
	using std::pair;
	using std::is_same;
	using std::min;
	// for Dijkstra algorithm
	using std::priority_queue;
	using std::greater;
	using std::tie;

	template<typename Weight>
	class Base {
	public:
		using AdjacencyList = vector<vector<pair<int, Weight>>>;
		Base(AdjacencyList _adj) : adj(_adj) {}

		// single-source shortest path
		// returns a pair: (1D shortest weight vertex, whether the result is correct for sure) 
		virtual pair<vector<Weight>, bool> sssp(int s) const = 0;

		// single-source shortest path
		// returns a pair: (2D shortest weight vertex, whether the result is correct for sure)
		virtual pair<vector<vector<Weight>>, bool> apsp(int s) const = 0;

	protected:
		// adjacency list and the weight of each edge.
		AdjacencyList adj;
	};

	template<typename Weight>
	class BellmanFord : public Base<Weight> {
		
	public:
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
						return { dist, false };
					}
				}
			}
			return { dist, true };
		}

		pair<vector<vector<Weight>>, bool> apsp(int s) const override {
			throw;
		}

	};

	template<typename Weight>
	class Dijkstra : public Base<Weight> {
	public:
		Dijkstra(AdjacencyList _adj) : Base<Weight>(_adj) {};

		pair<vector<Weight>, bool> sssp(int s) const override {
			using Node = pair<Weight, int>;
			size_t n = this->adj.size();
			vector<Weight> dist(n, -1);
			dist[s] = 0;

			vector<bool> visited(n, false);

			priority_queue<Node, vector<Node>, greater<Node>> pq;
			pq.push({ dist[s], s });
			// lazy deletion.
			// see https://stackoverflow.com/questions/9209323/easiest-way-of-using-min-priority-queue-with-key-update-in-c
			while (!pq.empty()) {
				int cur_idx;
				double cur_dist;
				tie(cur_dist, cur_idx) = pq.top();
				pq.pop();
				if (visited[cur_idx]) {
					continue;
				}
				visited[cur_idx] = true;
				for (const pair<int, Weight>& next : this->adj[cur_idx]) {
					int next_idx;
					double edge_weight;
					tie(next_idx, edge_weight) = next;
					if (edge_weight < 0) {
						// The weight of edges should not be negative in Dijkstra algorithm 
						// (at least for vertices reachable from s).
						return { dist, false };
					}
					if (dist[next_idx] == -1 || dist[next_idx] > dist[cur_idx] + edge_weight) {
						dist[next_idx] = dist[cur_idx] + edge_weight;
						pq.push({ dist[next_idx], next_idx });
					}
				}
			}
			return { dist, true };
			
		}

		pair<vector<vector<Weight>>, bool> apsp(int s) const override {
			throw;
		}
	};
}  // end of namespace shortest_path

