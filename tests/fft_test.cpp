#include <vector>
#include <complex>
#include <cmath>
#include "pch.h"
#include "../src/fft.hpp"

TEST(DftTest, BasicTest) {
	// basic round trip.
	// DFT -> IDFT -> scale should yield the same result.
	using fft::Complex;
	using fft::Polynomial;
	using std::vector;
	using std::real;
	using std::imag;
	using std::round;

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