//
// Created by 毛崇鑫 on 2019/9/20.
//

#ifndef STL_ALGORITHM_H
#define STL_ALGORITHM_H

#include <cstring>
#include <utility>

#include "allocator.h"
#include "functional.h"
#include "iterator.h"
#include "typetratis.h"
#include "utility.h"

namespace STD {
	template <typename ForwardIterator, typename T>
	void fill(ForwardIterator first, ForwardIterator last, const T& val) {
		for (; first != last; ++first) { *first = val; }
	}

	inline void fill(char* first, char* last, const char& val) {
		memset(first, static_cast<unsigned char>(val), last - first);
	}

	inline void fill(wchar_t* first, wchar_t* last, const wchar_t& val) {
		memset(first, static_cast<unsigned char>(val), (last - first) * sizeof(wchar_t));
	}

	template <typename OutputIterator, typename Size, typename T>
	OutputIterator fill_n (OutputIterator first, Size n, const T& value) {
		for (; n > 0; --n, ++first) { *first = value; }
		return *first;
	}

	template <typename Size>
	char* fill_n (char* first, Size n, const char& value) {
		memset (first, static_cast<unsigned char>(value), n);
	}
	template <typename Size>
	wchar_t* fill_n (wchar_t* first, Size n, const char& value) {
		memset (first, static_cast<unsigned char>(value), n);
	}

	template <typename T>
	const T& max (const T& a, const T& b) {
		return a > b ? a : b;
	}
	template <typename T, typename Compare>
	const T& max(const T& a, const T& b, Compare cmp) {
		return cmp(a, b) ? a : b;
	}

	template <typename T>
	const T& min (const T& a, const T& b) {
		return a < b ? a : b;
	}
	template <typename T, typename Compare>
	const T& min(const T& a, const T& b, Compare cmp) {
		return cmp(a, b) ? a : b;
	}

	template <typename RandomAccessIterator, typename Compare>
	// heap 上溯
	static void up (RandomAccessIterator first, RandomAccessIterator last,
			RandomAccessIterator head, Compare cmp) {
		if (first != last) {
			int index = last - first;
			auto parentIndex = (index - 1) / 2;
			for (auto cur = last; parentIndex >= 0 && cur != head; parentIndex = (index  - 1) / 2) {
				auto parent = head + parentIndex;
				if (cmp(*parent, *cur)) { STD::swap(*parent, *cur); }
				cur = parent;
				index = cur - head;
			}
		}
	}

	template <typename RandomAccessIterator, typename Compare>
	// heap 下降
	static void down (RandomAccessIterator first, RandomAccessIterator last,
			RandomAccessIterator head, Compare cmp) {
		if (first != last) {
			auto index = first - last;
			auto leftChildIndex = index * 2 + 1;
			for (auto cur = first; leftChildIndex < (last - head + 1) && cur < last; leftChildIndex = index * 2 + 1) {
				auto child = head + leftChildIndex;
				if (child + 1 <= last && *(child + 1) > *child) { ++child; }
				if (cmp(*cur, *child)) { STD::swap(*cur, *child); }
				cur = child;
				index = cur - head;
			}
		}
	}

	template <typename RandomAccessIterator>
	void make_heap (RandomAccessIterator first, RandomAccessIterator last) {
		STD::make_heap(first, last, STD::less<typename STD::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <typename RandomAccessIterator, typename Compare>
	void make_heap (RandomAccessIterator first, RandomAccessIterator last, Compare cmp) {
		const auto range = last - first;
		for (auto cur = first + range / 2 + 1; cur >= first; --cur) {
			STD::down(cur, last - 1, first, cmp);
			if (cur == first) { return; }
		}
	}

	template <typename RandomAccessIterator>
	void push_heap (RandomAccessIterator first, RandomAccessIterator last) {
		STD::push_heap(first, last, STD::less<typename STD::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <typename RandomAccessIterator, typename Compare>
	void push_heap (RandomAccessIterator first, RandomAccessIterator last, Compare cmp) {
		STD::up(first, last - 1, first, cmp);
	}

	template <typename RandomAccessIterator>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
		STD::pop_heap(first, last, STD::less<typename STD::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <typename RandomAccessIterator, typename Compare>
	void pop_head(RandomAccessIterator first, RandomAccessIterator last, Compare cmp) {
		STD::swap(*first, *(last - 1));
		if (last - first >= 2) { STD::down(first, last - 2, first, cmp); }
	}

	template <typename RandomAccessIterator>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
		return STD::sort_heap(first, last, STD::less<typename STD::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <typename RandomAccessIterator, typename Compare>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare cmp) {
		for (auto cur = last; cur != first; --cur) {
			STD::pop_heap(first, cur, cmp);
		}
	}

	template <typename RandomAccessIterator>
	bool is_heap(RandomAccessIterator first, RandomAccessIterator last) {
		return STD::is_heap(first, last, STD::less<typename STD::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <typename RandomAccessIterator, typename Compare>
	bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare cmp) {
		const auto range = last - first;
		auto index = range / 2 - 1;
		for (auto cur = first + range / 2 + 1; cur >= first; --cur, --index) {
			if (*(first + (index * 2 + 1)) > *cur ||
			((first + (index * 2 + 2)) <= last && *(first + (index * 2 + 2)) > *cur)) {
				return false;
			}
			if (cur == first) { break; }
		}
		return true;
	}
	// any_of
	template <typename InputIterator, typename UnaryPredicate>
	bool any_of (InputIterator first, InputIterator last, UnaryPredicate pred) {
		for (; first != last; ++first) {
			if (pred(*first)) { return true; }
		}
		return false;
	}
	// none_of
	template <typename InputIterator, typename UnaryPredicate>
	bool none_of (InputIterator first, InputIterator last, UnaryPredicate pred) {
		for (; first != last; ++first) {
			if (pred(*first)) { return false; }
		}
		return false;
	}

	// for_each
	template <typename InputIterator, typename Function>
	Function for_each(InputIterator first, InputIterator last, Function fn) {
		for (; first != last; ++first) {
			fn(*first);
		}
		return fn;
	}

	// find
	template <typename InputIterator, typename T>
	InputIterator find(InputIterator first, InputIterator last, const T& val) {
		for (; first != last; ++first) {
			if (*first == val) { return first; }
		}
		return first;
	}
	// find_if
	template <typename InputIterator, typename UnaryPredicate>
	InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate pred) {
		for (; first != last; ++first) {
			if (pred(*first)) { return first; }
		}
		return first;
	}
	// find_if_not
	template <typename InputIterator, typename UnaryPredicate>
	InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred) {
		for (; first != last; ++first) {
			if (pred(*first)) { return first; }
		}
		return first;
	}

	// find_end
	template <typename ForwardIterator1, typename ForwardIterator2>
	ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2) {
		if (first2 == last2) { return last1; }
		auto res = last1;
		while (first1 != last1) {
			auto it1 = first1;
			auto it2 = first2;
			while (*it1 == *it2) {
				++it1; ++it2;
				if (it2 == last2) { res = first1; break; }
			}
			++first1;
		}
		return res;
	}

	template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	ForwardIterator1 find_end (ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred) {
		if (first2 != last2) { return last1; }
		auto res = last1;
		while (first1 != last1) {
			auto it1 = first1;
			auto it2 = first2;
			while (pred(*it1, *it2)) {
				++it1; ++it2;
				if (it2 == last2) { res = first1; break; }
				if (it1 == last1) { return res; }
			}
			++first1;
		}
		return res;
	}
	// find_first_of
	template <typename ForwardIterator1, typename ForwardIterator2>
	ForwardIterator1 find_first_of (ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2) {
		for (; first1 != last1; ++first1) {
			for (auto it = first2; it != last2; ++it) {
				if (*first1 == *it) { return first1; }
			}
		}
		return last1;
	}
	template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	ForwardIterator1 find_first_of (ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred) {
		for (; first1 != last1; ++first1) {
			for (auto it = first2; it = last2; ++it) {
				if (pred(*first1, *it)) { return first1; }
			}
		}
		return last1;
	}

	// adjacent_find
	template <typename ForwardIterator>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
		return STD::adjacent_find(first, last,
				equal_to<iterator_traits<typename ForwardIterator>::value_type>());
	}
	template <typename  ForwardIterator, typename BinaryPredicate>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred) {
		for (; first != last; ++first) {
			if (first + 1 != last && pred(*(first), *(first + 1))) {
				return first;
			}
		}
		return first;
	}


}


#endif //STL_ALGORITHM_H
