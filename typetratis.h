//
// Created by 毛崇鑫 on 2019/9/19.
//

#ifndef STL_TYPETRATIS_H
#define STL_TYPETRATIS_H

namespace STD {
	namespace {
		template <bool, typename Ta, typename Tb>
		struct IfThenElse;
		template <typename Ta, typename Tb>
		struct IfThenElse <true, Ta, Tb> {
			using result = Ta;
		};
	}

	struct _true_type {};
	struct _false_type {};

	template <typename T>
	struct _type_traits {
		using has_trival_default_constructor = _false_type;
		using has_trival_copy_constructor = _false_type;
		using has_trival_assignment_operator = _false_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _false_type;
	};
	template <>
	struct _type_traits<bool> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assigment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<unsigned char> {
		using has_trival_default_consructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<char> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<signed char> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<wchar_t> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<short> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<signed short> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<int> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<unsigned int> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<long> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<unsigned long> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<long long> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<unsigned long long> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<float> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<double> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<long double> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <typename T>
	struct _type_traits<T*> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <typename T>
	struct _type_traits<const T*> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<char*> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<unsigned char*> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<signed char*> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<const char*> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<const unsigned char*> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
	template <>
	struct _type_traits<const signed char*> {
		using has_trival_constructor = _true_type;
		using has_trival_copy_constructor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _true_type;
		using is_POD_type = _true_type;
	};
}


#endif //STL_TYPETRATIS_H
