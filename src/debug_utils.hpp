#include <vector>
#include <iostream>

namespace debug_utils {
	using std::vector;
	using std::ostream;
	using std::endl;
	using std::pair;

	template<typename T>
	ostream& _print(ostream& os, const vector<T>& v) {
#ifdef _DEBUG
		os << '[';
		for (size_t i = 0; i < v.size(); i++) {
			os << v[i];
			if (i < v.size() - 1) os << ',';
		}
		os << ']';
#endif
		return os;
	}

	template<typename T1, typename T2>
	ostream& _print(ostream& os, const pair<T1, T2>& v) {
#ifdef _DEBUG
		os << '{' << v.first << ',' << v.second << '}';
#endif
		return os;
	}

	template<typename T>
	ostream& _print(ostream& os, const T& v) {
#ifdef _DEBUG
		os << v;
#endif
		return os;
	}

	template<typename T>
	ostream& operator<<(ostream& os, const vector<T>& v) {
#ifdef _DEBUG
		os << '[';
		for (size_t i = 0; i < v.size(); i++) {
			_print(os, v[i]);
			if (i < v.size() - 1) os << ',';
		}
		os << ']' << endl;
#endif
		return os;
	}

	template<typename T1, typename T2>
	ostream& operator<<(ostream& os, const pair<T1, T2>& v) {
#ifdef _DEBUG
		_print(os, v);
		os << endl;
#endif
		return os;
	}
}
