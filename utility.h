//
// Created by 毛崇鑫 on 2019/9/20.
//

#ifndef STL_UTILITY_H
#define STL_UTILITY_H
namespace STD {
	template <typename T>
	void swap(T& a, T& b) {
		T tmp = a;
		a = b;
		b = tmp;
	}
	template <typename T1, typename T2>
	struct pair {
	public:
		using first_type  = T1;
		using second_type = T2;
	public:
		pair() {}
		template <typename A, typename B>
		pair(const pair<A, B>& rhs);
		pair(const first_type& first, const second_type& second);
		pair& operator= (const pair& rhs);
		void swap(pair& pr);
	public:
		template <typename L, typename R>
		friend bool operator== (const pair<L, R>& lhs, const pair<L, T2>& rhs);
		template <typename L, typename R>
		friend bool operator!= (const pair<L, R>& lhs, const pair<L, R>& rhs);
		template <typename L, typename R>
		friend bool operator< (const pair<L, R>& lhs, const pair<L, R>& rhs);
		template <typename L, typename R>
		friend bool operator<= (const pair<L, R>& lhs, const pair<L, R>& rhs);
		template <typename L, typename R>
		friend bool operator> (const pair<L, R>& lhs, const pair<L, R>& rhs);
		template <typename L, typename R>
		friend bool operator>= (const pair<L, R>& lhs, const pair<L, R>& rhs);
	public:
		T1 first;
		T2 second;
	};
	template <typename T1, typename T2>
	template <typename A, typename B>
	pair<T1, T2>::pair(const pair<A, B> &rhs): first(rhs.first), second(rhs.first){}

	template <typename T1, typename T2>
	pair<T1, T2>::pair(const first_type &first, const second_type &second): first(first), second(second) {}

	template <typename T1, typename T2>
	pair<T1, T2>& pair<T1, T2>::operator=(const pair<T1, T2>& rhs) {
		if (&rhs != this) {
			first = rhs.first;
			second = rhs.second;
		}
		return *this;
	}
	template <typename T1, typename T2>
	void pair<T1, T2>::swap(pair<T1, T2> &pr) {
		STD::swap(first, pr.first);
		STD::swap(second, pr.second);
	}

	template <typename L, typename R>
	bool operator== (const pair<L, R>& lhs, const pair<L, R>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <typename L, typename R>
	bool operator!= (const pair<L, R>& lhs, const pair<L, R>& rhs) {
		return !(lhs == rhs);
	}

	template <typename L, typename R>
	bool operator< (const pair<L, R>& lhs, const pair<L, R>& rhs) {
		return lhs.first < rhs.first && lhs.second < rhs.second;
	}
	template <typename L, typename R>
	bool operator<= (const pair<L, R>& lhs, const pair<L, R>& rhs) {
		return lhs.first <= rhs.first && lhs.second < rhs.second;
	}
	template <typename L, typename R>
	bool operator> (const pair<L, R>& lhs, const pair<L, R>& rhs) {
		return lhs.first > rhs.first && lhs.second > rhs.second;
	}
	template <typename L, typename R>
	bool operator>= (const pair<L, R>& lhs, const pair<L, R>& rhs) {
		return lhs.first >= rhs->first && lhs.second >= rhs->second;
	}
	template <typename T1, typename T2>
	void swap(pair<T1, T2>& lhs, pair<T1, T2>& rhs) {
		STD::swap(lhs.first, rhs.first);
		STD::swap(lhs.second, rhs.second);
	}
	template <typename T1, typename T2>
	pair<T1, T2> make_pair(const T1& a, const T2& b) {
		return pair<T1, T2> (a, b);
	}
}
#endif //STL_UTILITY_H
