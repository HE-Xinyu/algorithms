#include <vector>
#include <unordered_set>
#include "max_flow.hpp"
#pragma once

using std::vector;
using std::pair;
using std::unordered_set;

class MaximumBipartiteMatching {
public:
    /*
     * elements are edges (u, v) in E.
     *
     * It does not need to be (x, y). (y, x) is also fine.
     * The index should be continuous.
     */
    vector<pair<int, int>> e;
    
    MaximumBipartiteMatching(vector<pair<int, int>> _e) : e(_e) {}

    int compute() {
        /*
         * Calculate the maximum matching using the Edmonds-Karp (Ford-Fulkerson) algorithm 
         * 
         * Although for normal graphs the time complexity is O(|E|^2 |V|), in bipartite matching it is 
         * O(|E||V|), because there are only O(|V|) augmenting paths.
         *
         * We denote the bipartite sets of vertices as X and Y. Suppose X + Y is continuous and starting from 0.
         * We have source vertex s = |X| + |Y|, t = |X| + |Y| + 1.
         * We add (s, x) and (y, t) to the graph, each having capacity 1.
         */
        unordered_set<int> X, Y;

        for (const auto& p : e) {
            // if u or v has already been added, 
            // the other vertex has no choice.
            if (X.count(p.first)) {
                Y.insert(p.second);
            }
            else if (X.count(p.second)) {
                Y.insert(p.first);
            }
            else if (Y.count(p.first)) {
                X.insert(p.second);
            }
            else if (Y.count(p.second)) {
                X.insert(p.first);
            }
            else {
                // either u or v is assigned.
                // we can choose arbitrarily.
                X.insert(p.first);
                Y.insert(p.second);
            }
        }

        // The entire graph contains |X| + |Y| + 2 vertices.
        size_t total_num = X.size() + Y.size();
        int s = static_cast<int>(total_num);
        int t = static_cast<int>(total_num + 1);
        vector<vector<int>> adj(total_num + 2);
        vector<vector<int>> cap(total_num + 2, vector<int>(total_num + 2, 0));

        for (const auto& p : e) {
            int u = p.first, v = p.second;
            if (X.count(u)) {
                cap[u][v] = 1;
            }
            else {
                cap[v][u] = 1;
            }

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        for (int x : X) {
            // x -> s is useless.
            cap[s][x] = 1;
            adj[s].push_back(x);
        }

        for (int y : Y) {
            // t -> y is useless.
            cap[y][t] = 1;
            adj[y].push_back(t);
        }

        EdmondsKarp<int> EK(adj, cap, s, t);
        return EK.compute();
    }

};