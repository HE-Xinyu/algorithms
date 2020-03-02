#include <vector>
#include <queue>
#include <iostream>

using std::vector;
using std::pair;
using std::queue;
using std::fill;
using std::min;
using std::cout;
using std::endl;

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
	
	Flow compute() {
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