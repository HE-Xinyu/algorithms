#include <vector>

#include "pch.h"
#include "../src/shortest_paths.hpp"

using shortest_path::BellmanFord;
using shortest_path::Dijkstra;
using std::vector;
using std::pair;

TEST(BellmanFordTest, BasicTest) {


	vector<vector<pair<int, int>>> adj = { { {1, 2} }, { { 2, 3 } }, { { 0, -6 } } };
	BellmanFord<int> BF(adj);
	auto result = BF.sssp(0);

	EXPECT_EQ(result.second, false);

	adj = { { {1, 2} }, { { 2, 3 } }, { { 0, 4 } } };
	BF = BellmanFord<int>(adj);
	result = BF.sssp(0);
	vector<int> ans = { 0, 2, 5 };
	for (int i = 0; i < 3; i++) {
		EXPECT_EQ(result.first[i], ans[i]);
	}
	EXPECT_EQ(result.second, true);
}


TEST(DijkstraTest, BasicTest) {
	vector<vector<pair<int, double>>> adj = { { {1, 2.0} }, { { 2, 3.0 } }, { { 0, 4.0 } } };
	Dijkstra<double> dij (adj);
	auto result = dij.sssp(0);
	vector<double> ans = { 0.0, 2.0, 5.0 };
	for (int i = 0; i < 3; i++) {
		EXPECT_EQ(result.first[i], ans[i]);
	}
	EXPECT_EQ(result.second, true);
}
