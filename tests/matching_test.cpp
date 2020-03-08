#include "pch.h"
#include "../src/matching.hpp"

TEST(MatchingTest, BasicTest) {
	vector<pair<int, int>> e = { {0, 1}, {1, 3}, {4, 2}, {4, 5} };
	MaximumBipartiteMatching MBP(e);
	ASSERT_EQ(MBP.compute(), 2);

	vector<pair<int, int>> e2 = { {0, 1}, {1, 3}, {0, 2}, {4, 5}, {3, 5} };
	MaximumBipartiteMatching MBP2(e2);
	ASSERT_EQ(MBP2.compute(), 3);
}