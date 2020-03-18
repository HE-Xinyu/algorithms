#include <complex>
#include <cfloat>
#include <vector>
#include <cmath>

namespace fft {
	using std::vector;
	using std::exp;
	using Complex = std::complex<double>;
	using ComplexIterator = vector<Complex>::iterator;

	constexpr auto M_PI = 3.14159265358979323846;

	class Polynomial {
	protected:
		vector<Complex> coef;
	public:
		// here the _coef must be a power of 2.
		Polynomial(vector<Complex> _coef) : coef(_coef) {};

		void dft_recursive(int sign) {
			size_t n = coef.size();
			if (n == 1) return;
			dft_recursive_internal(coef.begin(), coef.end(), sign);
		}

		void dft_recursive_internal(ComplexIterator begin, ComplexIterator end, int sign) {
			int n = end - begin;
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

			for (int k = 0; k < n / 2; k++) {
				temp[k] = *(begin + k) + cur * *(mid + k);
				temp[k + n / 2] = *(begin + k) - cur * *(mid + k);
				cur *= step;
			}

			for (int i = 0; i < n; i++) {
				*(begin + i) = temp[i];
			}
		}
	};
} // namespace fft