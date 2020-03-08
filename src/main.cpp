#include <iostream>
#include <vector>
#include "max_flow.hpp"

using namespace std;

int main()
{
	int n = 4;
	vector<vector<double>> cap(n, vector<double>(n, 0));
	vector<vector<int>> adj = { {1, 2}, {0, 2, 3}, {0, 1, 3}, {1, 2} };
	cap[0][1] = 10.1;
	cap[0][2] = 5.1;
	cap[1][3] = 5.1;
	cap[2][3] = 10.1;
	cap[1][2] = 15.1;
	PushToFront<double> PTF(adj, cap, 0, 3);
	std::cout << PTF.compute() << endl;
}
