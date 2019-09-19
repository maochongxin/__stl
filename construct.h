//
// Created by 毛崇鑫 on 2019/9/19.
//

#ifndef STL_CONSTRUCT_H
#define STL_CONSTRUCT_H

#include <new>
#include "typetratis.h"

namespace STD {
	template <typename T1, typename T2>
	inline void construct(T1* ptr1, const T2& value) {
		new(ptr1) T1(value);
	}
	template <typename T>
	inline void destroy(T* ptr) {
		ptr->~T();
	}

	template <typename ForwardIterator>
	inline void _destroy(ForwardIterator first, ForwardIterator last, _true_type) {}

	template <typename ForwardIterator>
	inline void _destroy(ForwardIterator first, ForwardIterator last, _false_type) {
		for (; first != last; ++first) {
			destory(&*first);
		}
	}
	template <typename ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last) {
		using is_POD_type = typename _type_traits<ForwardIterator>::is_POD_type;
		_destroy(first, last, is_POD_type());
	}
}
#endif //STL_CONSTRUCT_H
