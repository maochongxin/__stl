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
				equal_to<typename STD::iterator_traits<ForwardIterator>::value_type>());
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
	// count
	template <typename InputIterator, typename T>
	typename STD::iterator_traits<InputIterator>::difference_type
	count (InputIterator first, InputIterator last, const T& val) {
		typename STD::iterator_traits<InputIterator>::difference_type n = 0;
		for (; first != last; ++first) {
			if (*first == val) { ++n; }
		}
		return n;
	}

	// count_if
	template <typename InputIterator, typename UnaryPredicate>
	typename STD::iterator_traits<InputIterator>::difference_type
	count_if (InputIterator first, InputIterator last, UnaryPredicate pred) {
		typename STD::iterator_traits<InputIterator>::difference_type n = 0;
		for (; first != last; ++first) {
			if (pred(*first)) { ++n; }
		}
		return n;
	}

	// mismatch
	template <typename InputIterator1, typename InputIterator2>
	STD::pair<InputIterator1, InputIterator2>
	        mismatch (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
	        	for (; first1 != last1; ++first1, ++first2) {
	        		if (*first1 != *first2) { break; }
	        	}
				return STD::make_pair(first1, first2);
	        }
	template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	STD::pair<InputIterator1, InputIterator2>
	        mismatch (InputIterator1 first1, InputIterator1 last1,
	        		InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred) {
	        	for (; first1 != last1; ++first1, ++first2) {
	        		if (!pred(*first1, *first2)) { break; }
	        	}
	        	return STD::make_pair(first1, first2);
	        }

	// equal
	template <typename InputIterator1, typename InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2) {
		return STD::equal(first1, last1, STD::equal_to<typename STD::iterator_traits<InputIterator1>::value_type>());
	}
	template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, BinaryPredicate pred) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!pred(*first1, *first2)) { return false; }
		}
		return true;
	}

	// is_permutation
	template <typename ForwardIterator1, typename ForwardIterator2>
	bool is_permutation (ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2) {
		return STD::is_permutation(first1, last1, first2,
				STD::equal_to<typename STD::iterator_traits<ForwardIterator1>::value_type>());
	}
	template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	bool is_permutation (ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, BinaryPredicate pred) {
		auto res = STD::mismatch(first1, last1, first2, pred);
		first1 = res.first;
		first2 = res.second;
		auto last2 =first2;
		advance(last2, distance(first1, last1));
		for (auto it1 = first1; it1 != last1; ++it1) {
			if (STD::find_if(first1, it1, [&](decltype(*first1) val) {
				return pred(val, *it1);
			}) == it1) {
				auto n = STD::count(first2, last2, *it1);
				if (n == 0 || STD::count(it1, last1, *it1) != n) {
					return false;
				}
			}
		}
		return true;
	}
	// search
	template <typename ForwardIterator1, typename ForwardIterator2>
	ForwardIterator1 search (ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2) {
		return STD::search(first1, last1, first2, last2,
				STD::equal_to<typename STD::iterator_traits<ForwardIterator1>::value_type>());
	}
	template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	ForwardIterator1 search (ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred) {
		while (first1 != last1) {
			auto it1 = first1;
			auto it2 = first2;
			while (it1 != last1 && it2 != last2) {
				if (pred(*it1, *it2)) {
					++it1, ++it2;
				} else {
					break;
				}
			}
			if (it2 == last2) { return first1; }
			if (it1 == last1) { return last1; }
			++first1;
		}
		return last1;
	}
	// advance
	namespace {
		template <typename InputIterator, typename Distance>
		void _advance (InputIterator& it, Distance n, input_iterator_tag) {
			assert(n >= 0);
			while (n--) { ++it; }
		}

		template <typename BidirectionIterator, typename Distance>
		void _advance (BidirectionIterator& it, Distance n, bidirectional_iterator_tag) {
			if (n < 0) {
				while (n++) { --it; }
			} else {
				while (n--) { ++it; }
			}
		}
		template <typename RandomAccessIterator, typename Distance>
		void _advance (RandomAccessIterator& it, Distance n, random_access_iterator_tag) {
			if (n < 0) { it -= (-n); }
			else { it += n; }
		}
	}
	template <typename InputIterator, typename Distance>
	void advance (InputIterator& it, Distance n) {
		using iterator_category = typename STD::iterator_traits<InputIterator>::iterator_category;
		STD::_advance(it, n, iterator_category());
	}

	namespace {
		template<typename RandomAccessIterator, typename BinaryPredicate>
		typename STD::iterator_traits<RandomAccessIterator>::value_type
		mid3(RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred) {
			auto mid = first + (last + 1 - first) / 2;
			if (pred(*mid, *first)) { STD::swap(*mid, *first); }
			if (pred(*last, *mid)) { STD::swap(*last, *mid); }
			if (pred(*last, *first)) { STD::swap(*last, *first); }
			auto res = *mid;
			STD::swap(*mid, *(last - 1));
			return res;
		}

		template<typename RandomAccessIterator, typename BinaryPredicate>
		void bubble_sort(RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred) {
			auto len = last - first;
			for (auto i = len; i != 0; --i) {
				bool swaped = false;
				for (auto p = first; p != (first + i - 1); ++p) {
					if (pred(*(p + 1), *p)) {
						STD::swap(*(p + 1), *p);
						swaped = true;
					}
				}
				if (!swaped) { break; }
			}
		}
	}
	template <typename RandomAccessIterator>
	void sort(RandomAccessIterator first, RandomAccessIterator last) {
		return sort(first, last, less<typename STD::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <typename RandomAccessIterator, typename BinaryPredicate>
	void sort(RandomAccessIterator first, RandomAccessIterator last, BinaryPredicate pred) {
		if (first >= last || first + 1 == last) { return; }
		if (last - first <= 20) {
			return bubble_sort(first, last, pred);
		}
		auto mid = mid3(first, last, pred);
		auto p1 = first, p2 = last - 2;
		while (p1 < p2) {
			while (pred(*p1, mid) && (p1 < p2)) { ++p1; }
			while (!pred(*p2, mid) && (p1 < p2)) { --p2; }
			if (p1 < p2) { STD::swap(*p1, *p2); }
		}
		swap(*p1, *(last - 2));
		sort(first, p1, pred);
		sort(p1 + 1, last, pred);
	}

	// generate
	template <typename InputIterator, typename Function>
	void generate (InputIterator first, InputIterator last, Function func) {
		for (; first != last; ++first) {
			*first = func();
		}
	}

	// generate_n
	template <typename OutputIterator, typename Size, typename Generator>
	void generate_n (OutputIterator first, Size n, Generator gen) {
		while (n--) {
			*first = gen();
			++first;
		}
	}
	// distance
	template <typename InputIterator>
	typename STD::iterator_traits<InputIterator>::difference_type
	_distance (InputIterator first, InputIterator last, input_iterator_tag) {
		typename STD::iterator_traits<InputIterator>::difference_type dist = 0;
		while (first++ != last) { ++dist; }
		return dist;
	}
	template <typename RandomAccessIterator>
	typename STD::iterator_traits<RandomAccessIterator>::difference_type
	_distance (RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
		auto dist = last - first;
		return dist;
	}
	template <typename Iterator>
	typename STD::iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last) {
		using iterator_category = typename STD::iterator_traits<Iterator>::iterator_category;
		return _distance(first, last, iterator_category());
	}

	// copy
	template <typename InputIterator, typename OutputIterator>
	OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, STD::_true_type) {
		auto dist = distance(first, last);
		memcpy(result, first, sizeof(*first) * dist);
		advance(result, dist);
		return result;
	}
	template <typename InputIterator, typename OutputIterator>
	OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, STD::_false_type) {
		while (first != last) { *result++ = *first++; }
		return result;
	}
	template <typename InputIterator, typename OutputIterator, typename T>
	OutputIterator _copy(InputIterator first, InputIterator last, OutputIterator result, T*) {
		using is_pod = typename STD::_type_traits<T>::is_POD_type;
		return __copy(first, last, result, is_pod());
	}
	template <typename InputIterator, typename OutputIterator>
	OutputIterator copy (InputIterator first, InputIterator last, OutputIterator result) {
		return _copy(first, last, result, value_type(first));
	}
	template <>
	inline char* copy (char* first, char* last, char* result) {
		auto dist = last - first;
		memcpy(result, first, sizeof(*first) * dist);
		return result + dist;
	}
	template <>
	inline wchar_t* copy (wchar_t* first, wchar_t* last, wchar_t* result) {
		auto dist = last - first;
		memcpy(result, first, sizeof(first) * dist);
		return result + dist;
	}


}


#endif //STL_ALGORITHM_H
