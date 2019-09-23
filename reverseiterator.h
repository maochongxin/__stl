//
// Created by 毛崇鑫 on 2019/9/23.
//

#ifndef STL_REVERSEITERATOR_H
#define STL_REVERSEITERATOR_H

#include "iterator.h"

namespace STD {
	template<typename Iterator>
	class reverse_iterator_t {
	public:
		using iterator_type = Iterator;
		using iterator_category = typename iterator_traits<Iterator>::iterator_category;
		using value_type = typename iterator_traits<Iterator>::value_type;
		using difference_type = typename iterator_traits<Iterator>::difference_type;
		using pointer = typename iterator_traits<Iterator>::pointer;
		using const_pointer = const pointer;
		using reference = typename iterator_traits<Iterator>::reference;
		using const_reference = const reference;
	private:
		Iterator base_;
		Iterator cur_;
	public:
		reverse_iterator_t() : base_(0), cur_(0) {}

		explicit reverse_iterator_t(const iterator_type &it) : base_(it) {
			auto tmp = it;
			cur_ = --tmp;
		}

		template<typename Iter>
		explicit reverse_iterator_t(const reverse_iterator_t<Iter> &rev_it) {
			base_ = (iterator_type) rev_it.base();
			auto tmp = base_;
			cur_ = --tmp;
		}

		iterator_type base() { return base_; }

		reference operator*() { return *cur_; }

		const_reference operator*() const { return *cur_; }

		pointer operator->() { return &(operator*()); }

		const_pointer operator->() const { return &(operator*()); }

		reverse_iterator_t &operator++() {
			--base_;
			--cur_;
			return *this;
		}

		const reverse_iterator_t<Iterator> operator++(int) {
			reverse_iterator_t tmp = *this;
			++(*this);
			return tmp;
		}

		reverse_iterator_t &operator--() {
			++base_;
			++cur_;
			return *this;
		}

		const reverse_iterator_t<Iterator> operator--(int) {
			reverse_iterator_t tmp = *this;
			--(*this);
			return tmp;
		}

		reference operator[](difference_type n) {
			return base()[-n - 1];
		}

		reverse_iterator_t operator+(difference_type n) const;

		reverse_iterator_t &operator+=(difference_type n);

		reverse_iterator_t operator-(difference_type n) const;

		reverse_iterator_t &operator-=(difference_type n);

	private:
		Iterator advanceNStep(Iterator it, difference_type n, bool right, random_access_iterator_tag) {
			right ? it += n : it -= n;
			return it;
		}

		Iterator advanceNStep(Iterator it, difference_type n, bool right, bidirectional_iterator_tag) {
			difference_type i;
			difference_type absN = n >= 0 ? n : -n;
			if ((right && n > 0) || (!right && n < 0)) {
				for (i = 0; i != absN; ++i) {
					++it;
				}
			} else if ((!right && n > 0) || (right && n < 0)) {
				for (i = 0; i != absN; ++i) {
					--it;
				}
			}
			return it;
		}

	public:

		friend bool operator==(const reverse_iterator_t<Iterator> &lhs,
							   const reverse_iterator_t<Iterator> &rhs);

		friend bool operator!=(const reverse_iterator_t<Iterator> &lhs,
							   const reverse_iterator_t<Iterator> &rhs);

		friend bool operator<(const reverse_iterator_t<Iterator> &lhs,
							  const reverse_iterator_t<Iterator> &rhs);

		friend bool operator<=(const reverse_iterator_t<Iterator> &lhs,
							   const reverse_iterator_t<Iterator> &rhs);

		friend bool operator>(const reverse_iterator_t<Iterator> &lhs,
							  const reverse_iterator_t<Iterator> &rhs);

		friend reverse_iterator_t<Iterator> operator+(
				typename reverse_iterator_t<Iterator>::difference_type n,
				const reverse_iterator_t<Iterator> &rev_t);

		friend typename reverse_iterator_t<Iterator>::difference_type operator-(
				const reverse_iterator_t<Iterator>& lhs,
				const reverse_iterator_t<Iterator>& rhs);
	};


	template<typename Iterator>
	reverse_iterator_t<Iterator> reverse_iterator_t<Iterator>::operator+(reverse_iterator_t::difference_type n) const {
		reverse_iterator_t<Iterator> res = *this;
		res += n;
		return res;
	}

	template<typename Iterator>
	reverse_iterator_t<Iterator> &reverse_iterator_t<Iterator>::operator+=(reverse_iterator_t::difference_type n) {
		base_ = advanceNStep(base_, n, false, iterator_category());
		cur_ = advanceNStep(cur_, n, false, iterator_category());
		return *this;
	}

	template<typename Iterator>
	reverse_iterator_t<Iterator> reverse_iterator_t<Iterator>::operator-(reverse_iterator_t::difference_type n) const {
		reverse_iterator_t<Iterator> res = *this;
		res -= n;
		return res;
	}

	template<typename Iterator>
	reverse_iterator_t<Iterator> &reverse_iterator_t<Iterator>::operator-=(reverse_iterator_t::difference_type n) {
		base_ = advanceNStep(base_, n, true, iterator_category());
		cur_ = advanceNStep(cur_, n, true, iterator_category());
		return *this;
	}

	template<typename Iterator>
	bool operator==(const reverse_iterator_t<Iterator> &lhs, const reverse_iterator_t<Iterator> &rhs) {
		return lhs.cur_ == rhs.cur_;
	}

	template<typename Iterator>
	bool operator!=(const reverse_iterator_t<Iterator> &lhs, const reverse_iterator_t<Iterator> &rhs) {
		return !(lhs.cur_ == rhs.cur_);
	}

	template<typename Iterator>
	bool operator<(const reverse_iterator_t<Iterator> &lhs, const reverse_iterator_t<Iterator> &rhs) {
		return lhs.cur_ < rhs.cur_;
	}

	template<typename Iterator>
	bool operator<=(const reverse_iterator_t<Iterator> &lhs, const reverse_iterator_t<Iterator> &rhs) {
		return !(lhs > rhs);
	}

	template<typename Iterator>
	bool operator>(const reverse_iterator_t<Iterator> &lhs, const reverse_iterator_t<Iterator> &rhs) {
		return lhs.cur_ > rhs.cur_;
	}

	template<typename Iterator>
	bool operator>=(const reverse_iterator_t<Iterator> &lhs, const reverse_iterator_t<Iterator> &rhs) {
		return !(lhs < rhs);
	}

	template <typename Iterator>
	reverse_iterator_t<Iterator> operator+ (
			typename reverse_iterator_t<Iterator>::difference_type n,
			const reverse_iterator_t<Iterator>& rev_it) {
		return rev_it + n;
	}
	template <typename Iterator>
	typename reverse_iterator_t<Iterator>::difference_type operator- (
			const reverse_iterator_t<Iterator>& lhs,
			const reverse_iterator_t<Iterator>& rhs) {
		return lhs.cur_ - rhs.cur_;
	}
}

#endif //STL_REVERSEITERATOR_H
