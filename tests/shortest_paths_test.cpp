#include <vector>

#include "pch.h"
#include "../src/shortest_paths.hpp"

TEST(BellmanFordTest, BasicTest) {
	using shortest_path::BellmanFord;
	using std::vector;
	using std::pair;
	

	vector<vector<pair<int, int>>> adj = { { {1, 2} }, { { 2, 3 } }, { { 0, -6 } } };
	BellmanFord<int> BF(adj);
	auto result = BF.sssp(0);

	EXPECT_EQ(result.second, true);

	adj = { { {1, 2} }, { { 2, 3 } }, { { 0, 4 } } };
	BF = BellmanFord<int>(adj);
	result = BF.sssp(0);
	vector<int> ans = { 0, 2, 5 };
	for (int i = 0; i < 3; i++) {
		EXPECT_EQ(result.first[i], ans[i]);
	}
	EXPECT_EQ(result.second, false);
}