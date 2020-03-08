#include <vector>
#include <queue>
#include <iostream>
#include <list>
#include <iterator>

using std::vector;
using std::pair;
using std::queue;
using std::list;
using std::fill;
using std::min;
using std::cout;
using std::endl;
using std::next;


template<typename Flow>
class MaxFlowBase {
protected:
	// adjacency list
	vector<vector<int>> adj;
	// n * n capacity vertex (non-negative)
	vector<vector<Flow>> cap;
	// start vertex and end vertex
	int s, t;
public:
	MaxFlowBase(vector<vector<int>> _adj, vector<vector<Flow>> _cap, int _s, int _t) : adj(_adj), cap(_cap), s(_s), t(_t) {}
	virtual Flow compute() = 0;
};

template<typename Flow>
class EdmondsKarp : public MaxFlowBase<Flow> {
public:
	EdmondsKarp(vector<vector<int>> _adj, vector<vector<Flow>> _cap, int _s, int _t) : MaxFlowBase<Flow>(_adj, _cap, _s, _t) {}
	
	Flow compute() override {
		Flow ret = 0;
		size_t n = this->cap.size();

		// -1 for unvisited vertices.
		// allocate it outside of the while loop to save memory allocation time
		vector<int> step(n, -1);
		vector<int> prev(n, -1);
		while (true) {
			bool foundAugPath = false;
			// no need to reset prev array, since we only use it to record the path
			fill(step.begin(), step.end(), -1);
			step[this->s] = 0;
			queue<int> q;
			q.push(this->s);

			// BFS to find the shortest augmenting path
			while (!q.empty()) {
				int cur = q.front();
				q.pop();
				if (cur == this->t) {
					foundAugPath = true;
					break;
				}

				for (int next : this->adj[cur]) {
					if (this->cap[cur][next] && step[next] == -1) {
						// (cur, next) has positive capacity and 'next' is not visited
						step[next] = step[cur] + 1;
						prev[next] = cur;
						q.push(next);
					}
				}
			}

			if (foundAugPath) {
				Flow augValue = -1;
				int cur = this->t;
				// first pass to compute the augment value
				while (prev[cur] != -1) {
					if (augValue != -1) {
						augValue = min(augValue, this->cap[prev[cur]][cur]);
					}
					else {
						augValue = this->cap[prev[cur]][cur];
					}
					cur = prev[cur];
				}

				ret += augValue;

				cur = this->t;
				// second pass to update the capacity matrix
				while (prev[cur] != -1) {
					this->cap[prev[cur]][cur] -= augValue;
					this->cap[cur][prev[cur]] += augValue;
					cur = prev[cur];
				}
			}
			else {
				break;
			}
		}
		return ret;
	}
};


template<typename Flow>
class GeneralPushRelabel : public MaxFlowBase<Flow> {
protected:
	// (f, h) instance
	vector<vector<Flow>> preFlow;
	vector<int> height;
	// save the excess amount to save computation cost
	vector<Flow> excess;
public:
	GeneralPushRelabel(vector<vector<int>> _adj, vector<vector<Flow>> _cap, int _s, int _t) : MaxFlowBase<Flow>(_adj, _cap, _s, _t) {
		size_t n = _cap.size();
		preFlow = vector<vector<Flow>>(n, vector<Flow>(n, 0));
		height = vector<int>(n, 0);
		excess = vector<Flow>(n, 0);
		/*
		 * standard initialization.
		 * the start vertex will have height of n.
		 * make (s, u) have zero residual capacity.
		 */
		height[_s] = static_cast<int>(n);
		for (int v : _adj[_s]) {
			preFlow[_s][v] += _cap[_s][v];
			excess[v] += _cap[_s][v];
		}
	}

	Flow c_f(int u, int v) {
		/*
		 * Return the residual flow of the edge (u, v).
		 */

		return this->cap[u][v] - preFlow[u][v] + preFlow[v][u];
	}

	void push(int u, int v) {
		/*
		 * h(u) = h(v) + 1, and edge (u, v) has residual capacity.
		 * Push flow from u to v as much as we can.
		 * Caller should gaurantee that the PUSH is valid.
		 *
		 * The time complexity is O(1).
		 * 
		 * We apply a simple greedy strategy: first decrease f(v, u) as much as we can, then increase f(u, v).
		 */

		Flow amount = min(c_f(u, v), excess[u]);
		excess[u] -= amount;
		excess[v] += amount;
		Flow amountDecrease = min(amount, preFlow[v][u]);
		preFlow[v][u] -= amountDecrease;
		preFlow[u][v] += (amount - amountDecrease);
	}

	void relabel(int u) {
		/*
		 * Do a relabel on u.
		 * Caller should gaurantee that the RELABEL is valid.
		 * 
		 * Find the lowest vertex v satisfying c_f(u, v) > 0
		 * It should be guaranteed that such v exists, and h(u) <= h(v) for all v before relabel.
		 *
		 * Update h(u) = h(v) + 1
		 * 
		 * Time complexity: O(d(u))
		 */

		int mn = INT_MAX;
		for (int v : this->adj[u]) {
			if (c_f(u, v) > 0) {
				mn = min(mn, height[v]);
			}
		}

		height[u] = mn + 1;
	}
};


template<typename Flow>
class PushToFront : public GeneralPushRelabel<Flow> {
public:
	PushToFront(vector<vector<int>> _adj, vector<vector<Flow>> _cap, int _s, int _t) : GeneralPushRelabel<Flow>(_adj, _cap, _s, _t) {}
	
	bool discharge(int u) {
		/*
		 * Do a DISCHARGE on vertex u.
		 * 
		 * return whether it does a RELABEL.
		 *
		 */

		int v = 0;
		bool is_relabeled = false;
		int idx = 0;
		while (this->excess[u] > 0) {
			if (idx == this->adj[u].size()) {
				this->relabel(u);
				is_relabeled = true;
				idx = 0;
			}
			else {
				int v = this->adj[u][idx];
				if (this->c_f(u, v) > 0 && this->height[u] == this->height[v] + 1) {
					this->push(u, v);
				}
				idx++;
			}
		}
		return is_relabeled;
	}

	Flow compute() override {
		/*
		 * full routine.
		 */

		list<int> l;
		size_t n = this->cap.size();
		// insert all vertices except the end vertex into the list.
		for (int i = 0; i < n; i++) {
			if (i != this->t) {
				l.push_back(i);
			}
		}
		list<int>::iterator iter = l.begin();
		while (iter != l.end()) {
			bool is_relabeled = discharge(*iter);
			if (is_relabeled) {
				// move the current vertex to the front
				l.splice(l.begin(), l, iter, next(iter));
			}
			iter++;
		}
		return this->excess[this->t];
	}
};