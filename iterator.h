//
// Created by 毛崇鑫 on 2019/9/19.
//

#ifndef STL_ITERATOR_H
#define STL_ITERATOR_H

#include <mach/vm_types.h>

namespace STD {
	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	template <typename T, typename Distance> struct input_iterator {
		using iterator_category = input_iterator_tag;
		using value_type 		= T;
		using difference_type 	= Distance;
		using pointer 			= T*;
		using reference			= T&;
	};
	struct output_iterator {
		using iterator_category = output_iterator_tag;
		using value_type 		= void;
		using difference_type 	= void;
		using pointer			= void*;
		using reference			= void;
	};
	template <typename T, typename Distance> struct forward_iterator {
		using iterator_category = forward_iterator_tag;
		using value_type 		= T;
		using difference_type 	= Distance;
		using pointer			= T*;
		using reference			= T&;
	};
	template <typename T, typename Distance> struct bidirectional_iterator {
		using iterator_category = bidirectional_iterator_tag;
		using value_type 		= T;
		using difference_type	= Distance;
		using pointer 			= T*;
		using reference			= T&;
	};
	template <typename T, typename Distance> struct random_access_iterator {
		using iterator_category = random_access_iterator_tag;
		using value_type 		= T;
		using difference_type 	= Distance;
		using pointer 			= T*;
		using reference			= T&;
	};
	template <typename Category, typename T, typename Distance = __darwin_ptrdiff_t,
			typename Pointer = T*, typename Reference = T&>
	struct iterator {
		using iterator_category = Category;
		using value_type 		= T;
		using difference_type	= Distance;
		using pointer 			= Pointer;
		using reference			= Reference;
	};
	template <typename Iterator>
	struct iterator_traits {
		using iterator_category = typename Iterator::iterator_category;
		using value_type		= typename Iterator::value_type;
		using difference_type 	= typename Iterator::difference_type;
		using pointer 			= typename Iterator::pointer;
		using reference			= typename Iterator::reference;
	};
	template <typename T>
	struct iterator_traits<T*> {
		using iterator_category = random_access_iterator_tag;
		using value_type 		= T;
		using difference_type 	= __darwin_ptrdiff_t;
		using pointer 			= T*;
		using reference 		= T&;
	};
	template <typename T>
	struct iterator_traits<const T*> {
		using iterator_category = random_access_iterator_tag;
		using value_type 		= T;
		using difference_type 	= __darwin_ptrdiff_t;
		using pointer			= const T*;
		using reference 		= const T&;
	};
	template <typename Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
	iterator_category(const Iterator& It) {
		using category = typename iterator_traits<Iterator>::iterator_category;
		return category();
	}
	template <typename Iterator>
	inline typename iterator_traits<Iterator>::value_type
	value_type(const Iterator& It) {
		return static_cast<typename iterator_traits<Iterator>::value_type*> (0);
	}
	template <typename Iterator>
	inline typename iterator_traits<Iterator>::difference_type
	difference_type(const Iterator& It) {
		return static_cast<typename iterator_traits<Iterator>::difference_type*> (0);
	}


}
#endif //STL_ITERATOR_H
