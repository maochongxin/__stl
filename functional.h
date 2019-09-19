//
// Created by 毛崇鑫 on 2019/9/20.
//

#ifndef STL_FUNCTIONAL_H
#define STL_FUNCTIONAL_H
namespace STD {
	template <typename T>
	struct less {
		using first_argument_type  = T;
		using second_argument_type = T;
		using result_type 		   = bool;

		result_type operator()(const first_argument_type& x, const second_argument_type& y) {
			return x < y;
		}
	};
	template <typename T>
	struct greater {
		using first_argument_type  = T;
		using second_argument_type = T;
		using result_type 		   = bool;

		result_type operator()(const first_argument_type& x, const second_argument_type& y) {
			return x > y;
		}
	};

	template <typename T>
	struct equal_to {
		using first_argument_type = T;
		using second_argument_type = T;
		using result_type 		   = bool;

		result_type operator()(const first_argument_type& x, const second_argument_type& y) {
			return x == y;
		}
	};
}

#endif //STL_FUNCTIONAL_H
