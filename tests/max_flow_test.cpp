#include "pch.h"
#include "../src/max_flow.cpp"

TEST(MaxFlowTest, BasicTest) {
	int n = 4;
	vector<vector<double>> cap(n, vector<double>(n, 0));
	vector<vector<int>> adj = { {1, 2}, {0, 2, 3}, {0, 1, 3}, {1, 2} };
	cap[0][1] = 10.1;
	cap[0][2] = 5.1;
	cap[1][3] = 5.1;
	cap[2][3] = 10.1;
	cap[1][2] = 15.1;
	EdmondsKarp<double> EK(adj, cap, 0, 3);
	PushToFront<double> PTF(adj, cap, 0, 3);
	double result_ek = EK.compute();
	double result_ptf = PTF.compute();
	EXPECT_EQ(result_ek, 15.2);
	EXPECT_EQ(result_ptf, result_ek);
}