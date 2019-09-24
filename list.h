//
// Created by 毛崇鑫 on 2019/9/24.
//

#ifndef STL_LIST_H
#define STL_LIST_H

#include "allocator.h"
#include "iterator.h"
#include "reverseiterator.h"
#include "uninitializedfunctions.h"
#include "typetratis.h"

namespace STD {
	template <typename T>
	class list;
	namespace Detail {
		template <typename T>
		struct node {
			T data_;
			node* prev_;
			node* next_;
			list<T>* container_;
			node(const T& data, node* prev, node* next, list<T>* container):
				data_(data), prev_(prev), next_(next), container_(container) {}
			bool operator== (const node& n) {
				return data_ == n.data_ && prev_ == n.prev_ && next_ ==  n.next_ && container_ == n.container_;
			}
		};

		template <typename T>
		struct listIterator: public iterator<bidirectional_iterator_tag, T> {
			friend class list;
		public:
			using nodePtr = node<T>*;
			nodePtr p;
		public:
			explicit listIterator(nodePtr ptr = nullptr): p(ptr) {}

			listIterator& operator++();
			listIterator& operator--();
			listIterator& operator++(int);
			listIterator& operator--(int);
			T& operator*() { return p->data_; }
			T* operator->() { return &(operator*()); }

			friend bool operator== (const listIterator<T>& lhs, const listIterator<T>& rhs);
			friend bool operator!= (const listIterator<T>& lhs, const listIterator<T>& rhs);
		};
	} // end of namespace

	template <typename T>
	class list {
		friend struct Detail::listIterator<T>;
	private:
		using nodeAllocator = allocator<Detail::node<T>>;
		using nodePtr = Detail::node<T>*;
	public:
		using value_type = T;
		using iterator = Detail::listIterator<T>;
		using const_iterator = Detail::listIterator<const T>;

	};


} // end of namespace
#endif //STL_LIST_H
