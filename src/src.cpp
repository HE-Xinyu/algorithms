#include <iostream>
#include <vector>
#include "max_flow.cpp"

using namespace std;

int main()
{
	int n = 4;
	vector<vector<int>> cap(n, vector<int>(n, 0));
	vector<vector<int>> adj = { {1, 2}, {0, 2, 3}, {0, 1, 3}, {1, 2} };
	cap[0][1] = 10;
	cap[0][2] = 5;
	cap[1][3] = 5;
	cap[2][3] = 10;
	cap[1][2] = 15;
	EdmondsKarp<int> EK(adj, cap, 0, 3);
	std::cout << EK.compute() << endl;
}
