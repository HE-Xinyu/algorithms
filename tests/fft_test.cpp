#include <algorithm>
#include <vector>
#include <complex>
#include <cmath>
#include "pch.h"
#include "../src/fft.hpp"

using fft::Complex;
using fft::Polynomial;
using std::vector;
using std::real;
using std::imag;
using std::round;
using std::max;

TEST(DftTest, BasicTest) {
	// basic round trip.
	// DFT -> IDFT -> scale should yield the same result.
	vector<Complex> coef(4);
	coef[0] = { 1, 0 };
	coef[1] = { 2, 0 };
	coef[2] = { 3, 0 };
	coef[3] = { 4, 0 };

	Polynomial p(coef);
	p.dft_recursive(1);
	p.dft_recursive(-1);
	p.scale();

	for (int i = 0; i < 4; i++) {
		EXPECT_EQ(round(real(p.coef[i])), double(i + 1));
		EXPECT_EQ(round(imag(p.coef[i])), 0.0);
	}
}

TEST(PolynomialMultiplyTest, BasicTest) {
	// Test multiplying two polynomials.
	// (1 + 2x + 3x^2 + 4x^3 + 5x^4) * (5 + 4x + 3x^2 + 2x^3 + 1x^4) = 
	// 5 + 14x + 26x^2 + 40x^3 + 55x^4 + 40x^5 + 26x^6 + 14x^7 + 5x^8

	int n = 5;
	vector<Complex> coef_1(n), coef_2(n);
	for (int i = 0; i < n; i++) {
		coef_1[i] = { i + 1.0, 0 };
		coef_2[i] = { (double)n - i, 0 };
	}

	Polynomial p1(coef_1), p2(coef_2);

	p1 *= p2;

	vector<double> ans = { 5.0, 14.0, 26.0, 40.0, 55.0, 40.0, 26.0, 14.0, 5.0 };
	size_t nn = 16;
	EXPECT_EQ(p1.coef.size(), nn);
	for (int i = 0; i < nn; i++) {
		if (i < ans.size())
			EXPECT_EQ(round(real(p1.coef[i])), ans[i]);
		else
			EXPECT_EQ(round(real(p1.coef[i])), 0.0);

		EXPECT_EQ(round(imag(p1.coef[i])), 0.0);
	}
}
