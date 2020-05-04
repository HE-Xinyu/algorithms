#include <iostream>
#include <vector>
#include "max_flow.hpp"
#include "matching.hpp"
#include "fft.hpp"

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

	vector<pair<int, int>> e = { {0, 1}, {1, 3}, {0, 2}, {4, 5}, {3, 5} };
	MaximumBipartiteMatching MBP(e);
	cout << MBP.compute().size() << endl;

	using fft::Complex;

	n = 5;
	vector<Complex> coef(n);
	for (int i = 0; i < n; i++) {
		coef[i] = { i + 1.0, 0 };
	}
	fft::Polynomial poly(coef);
	
	fft::Polynomial poly2(coef);

	poly *= poly2;
	for (int i = 0; i < 16; i++) {
		cout << real(poly.coef[i]) << " " << imag(poly.coef[i]) << endl;
	}
}
