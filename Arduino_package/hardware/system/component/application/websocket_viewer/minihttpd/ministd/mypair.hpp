#pragma once

namespace ministd {
	template <typename T1, typename T2> class pair {
		public:
			T1 first;
			T2 second;

		public:
			pair(T1 _first, T2 _second):first(_first), second(_second) {}
			pair(const pair &p) { first = p.first; second = p.second; }
			pair &operator=(pair &p) { first = p.first; second = p.second; return *this; }
	};
}
