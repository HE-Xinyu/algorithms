#define _USE_MATH_DEFINES
#include <algorithm>
#include <complex>
#include <cfloat>
#include <vector>
#include <cmath>
#include <iostream>
#include <math.h>

namespace fft {
	using std::vector;
	using std::exp;
	using Complex = std::complex<double>;
	using ComplexIterator = vector<Complex>::iterator;
	using std::cout;
	using std::endl;
	using std::max;
	using std::swap;

	class Polynomial {
	private:
		void dft_recursive_internal(ComplexIterator begin, ComplexIterator end, int sign) {
			size_t n = end - begin;
			if (n == 1) return;

			vector<Complex> temp(begin, end);

			ComplexIterator mid = begin + n / 2;
			for (int i = 0; i < n; i++) {
				if (i & 1) {
					*(mid + i / 2) = temp[i];
				}
				else {
					*(begin + i / 2) = temp[i];
				}
			}

			dft_recursive_internal(begin, mid, sign);
			dft_recursive_internal(mid, end, sign);

			Complex cur(1, 0);
			Complex step = exp(Complex(0, 1) * (2 * M_PI * sign / n));

			for (size_t k = 0; k < n / 2; k++) {
				temp[k] = *(begin + k) + cur * *(mid + k);
				temp[k + n / 2] = *(begin + k) - cur * *(mid + k);
				cur *= step;
			}

			for (int i = 0; i < n; i++) {
				*(begin + i) = temp[i];
			}
		}

		// https://oi-wiki.org/math/poly/fft/
		void bit_reverse() {
			size_t n = coef.size();
			vector<int> reverse(n, 0);
			for (size_t i = 0; i < n; i++) {
				reverse[i] = reverse[i >> 1] >> 1;
				if (i & 1) {
					reverse[i] |= (n >> 1);
				}
			}
			for (size_t i = 0; i < n; i++) {
				if (i < reverse[i]) {
					swap(coef[i], coef[reverse[i]]);
				}
			}
		}
	public:
		vector<Complex> coef;
		// padding coef with zeros to achieve size of 2^k. 
		Polynomial(vector<Complex> _coef) : coef(_coef) {
			size_t n = coef.size();
			if (n == 0) {
				// not allowing empty vector.
				throw;
			}
			size_t new_size = 1;
			while (new_size < n) {
				new_size <<= 1;
			}
			coef.resize(new_size);
		};

		void dft_recursive(int sign) {
			size_t n = coef.size();
			if (n == 1) return;
			dft_recursive_internal(coef.begin(), coef.end(), sign);
		}

		void dft(int sign) {
			size_t n = coef.size();
			bit_reverse();
			for (size_t k = 2; k <= n; k <<= 1) {
				Complex step = exp(Complex(0, 1) * (2 * M_PI * sign / k));
				for (size_t j = 0; j < n; j += k) {
					Complex cur(1, 0);
					for (size_t i = j; i < j + k / 2; i++) {
						Complex u = coef[i];
						Complex t = cur * coef[i + k / 2];
						coef[i] = u + t;
						coef[i + k / 2] = u - t;
						cur *= step;
					}
				}
			}
		}

		void scale() {
			size_t n = coef.size();
			for (auto& num : coef) {
				num /= static_cast<Complex>(n);
			}
		}

		Polynomial& operator*=(Polynomial& rhs) {
			/*
			 * NOTE: For saving space, rhs can be modified.
			 */

			size_t len = max(coef.size(), rhs.coef.size()) * 2;
		
			coef.resize(len);
			rhs.coef.resize(len);

			dft(1);
			rhs.dft(1);

			for (int i = 0; i < len; i++) {
				coef[i] *= rhs.coef[i];
			}

			dft(-1);
			scale();

			return *this;
		}
	};

} // namespace fft