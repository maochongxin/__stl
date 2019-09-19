//
// Created by 毛崇鑫 on 2019/9/19.
//

#ifndef STL_ALLOCATOR_H
#define STL_ALLOCATOR_H

#include <cassert>
#include <new>

#include "alloc.h"
#include "construct.h"

namespace STD {
	template <typename T>
	class allocator {
	public:
		using value_type 	  = T;
		using pointer	 	  = T*;
		using const_pointer   = const T*;
		using reference 	  = T&;
		using const_reference = const T&;
		using size_type		  = size_t;
		using difference_type = ptrdiff_t;
	public:
		static T* allocate();
		static T* allocate(size_t n);
		static void deallocate(T* ptr);
		static void deallocate(T* ptr, size_t n);

		static void construct(T* ptr);
		static void construct(T* ptr, const T& value);
		static void destroy(T* ptr);
		static void destroy(T* first, T* last);
	};

	template <typename T>
	T* allocator<T>::allocate() {
		return static_cast<T*> (alloc::allocate(sizeof(T)));
	}
	template <typename T>
	T* allocator<T>::allocate(size_t n) {
		if (n == 0) return 0;
		return static_cast<T*> (alloc::allocate(sizeof(T) * n));
	}
	template <typename T>
	void allocator<T>::deallocate(T *ptr) {
		alloc::deallocate(static_cast<void*>(ptr), sizeof(T));
	}
	template <typename T>
	void allocator<T>::deallocate(T *ptr, size_t n) {
		if (n == 0) return;
		alloc::deallocate(static_cast<void*>(ptr), sizeof(T) * n);
	}

	template <typename T>
	void allocator<T>::construct(T *ptr) {
		new(ptr)T();
	}
	template <typename T>
	void allocator<T>::construct(T *ptr, const T &value) {
		new(ptr)T(value);
	}
	template <typename T>
	void allocator<T>::destroy(T *ptr) {
		ptr->~T();
	}
	template <typename T>
	void allocator<T>::destroy(T *first, T* last) {
		for (; first != last; ++first) {
			first->~T();
		}
	}
}

#endif //STL_ALLOCATOR_H
