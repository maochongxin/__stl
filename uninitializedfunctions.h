//
// Created by 毛崇鑫 on 2019/9/23.
//

#ifndef STL_UNINITIALIZEDFUNCTIONS_H
#define STL_UNINITIALIZEDFUNCTIONS_H

#include "algorithm.h"
#include "construct.h"
#include "iterator.h"
#include "typetratis.h"

namespace STD {
	template <typename InputIterator, typename ForwardIterator>
	ForwardIterator _uninitialized_copy_aux (InputIterator first, InputIterator last,
			ForwardIterator result, _true_type);
	template <typename InputIterator, typename ForwardIterator>
	ForwardIterator _uninitialized_copy_aux (InputIterator first, InputIterator last,
			ForwardIterator result, _false_type);

	template <typename InputIterator, typename ForwardIterator>
	ForwardIterator uninitialized_copy (InputIterator first, InputIterator last,
			ForwardIterator result) {
		using is_pod = typename _type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type;
		return _uninitialized_copy_aux(first, last, result, is_pod());
	}
	template <typename InputIterator, typename ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
			ForwardIterator result, _true_type) {
		memcpy(result, first, (last - first) * sizeof(*first));
		return result + (last - first);
	}
	template <typename InputIterator, typename ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
			ForwardIterator result, _false_type) {
		auto i = 0;
		for (; first != last; ++first, ++i) {
			construct(result + i, *first);
		}
		return result + i;
	}

	//
	template <typename ForwardIterator, typename T>
	void _uninitialized_fill_aux (ForwardIterator first, ForwardIterator last,
			const T& value, _true_type);
	template <typename ForwardIterator, typename T>
	void _uninitialized_fill_aux (ForwardIterator first, ForwardIterator last,
			const T& value, _false_type);
	template <typename ForwardIterator, typename T>
	void uninitialized_fill_aux (ForwardIterator first, ForwardIterator last,
			const T& value) {
		using is_pod = typename _type_traits<T>::is_POD_type;
		_uninitialized_fill_aux(first, last, value, is_pod());
	}
	template <typename ForwardIterator, typename T>
	void _uninitialized_fill_aux (ForwardIterator first, ForwardIterator last,
			const T& value, _true_type) {
		fill (first, last, value);
	}
	template <typename ForwardIterator, typename T>
	void _uninitialized_fill_aux (ForwardIterator first, ForwardIterator last,
			const T& value, _false_type) {
		for (; first != last; ++first) {
			construct(first ,value);
		}
	}

	//
	template <typename ForwardIterator, typename Size, typename T>
	ForwardIterator _uninitialized_fill_n_aux (ForwardIterator first,
			Size n, const T& value, _false_type);
	template <typename ForwardIterator, typename Size, typename T>
	ForwardIterator _uninitialized_fill_n_aux (ForwardIterator first,
			Size n, const T& value, _true_type);

	template <typename ForwardIterator, typename Size, typename T>
	inline ForwardIterator uninitialized_fill_n (ForwardIterator first,
			Size n, const T& x) {
		using is_pod = typename _type_traits<T>::is_POD_type;
		return _uninitialized_fill_n_aux(first, n, x, is_pod);
	}
	template <typename ForwardIterator, typename Size, typename T>
	ForwardIterator _uninitialized_fill_n_aux (ForwardIterator first,
			Size n, const T& x, _true_type) {
		return fill_n(first, n, x);
	}
	template <typename ForwardIterator, typename Size, typename T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
			Size n, const T& x, _false_type) {
		auto i = 0;
		for (; i != n; ++i) {
			construct((T*)(first + i), x);
		}
		return first + i;
	}
}

#endif //STL_UNINITIALIZEDFUNCTIONS_H
