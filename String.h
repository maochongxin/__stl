//
// Created by 毛崇鑫 on 2019/9/23.
//

#ifndef STL_STRING_H
#define STL_STRING_H

#include "allocator.h"
#include "reverseiterator.h"
#include "uninitializedfunctions.h"
#include "utility.h"

#include <cstring>
#include <type_traits>
#include <iostream>

namespace STD {
	class string {
	public:
		using value_type 			 = char;
		using iterator 				 = char*;
		using const_iterator 		 = const char*;
		using reverse_iterator 		 = reverse_iterator_t<char*>;
		using const_reverse_iterator = reverse_iterator_t<const char*>;
		using reference 			 = char&;
		using const_reference 		 = const char&;
		using size_type 			 = size_t;
		using difference_type 		 = ptrdiff_t;

		static const size_t npos = -1;
	private:
		char* start_;
		char* finish_;
		char* endOfStorage_;

		using dataAllocator = STD::allocator<char>;
	public:
		string (): start_(0), finish_(0), endOfStorage_(0) {}
		string (const string& str);
		string (string&& str);
		string (const string& str, size_t pos, size_t len = npos);
		string (const char* s);
		string (const char* s, size_t n);
		string (size_t n, char c);
		template <typename InputIterator>
		string (InputIterator first, InputIterator last);

		string& operator= (const string& str);
		string& operator= (string&& str);
		string& operator= (const char* s);
		string& operator= (char c);

		~string();

		iterator begin() { return start_; }
		iterator begin() const { return start_; }
		const_iterator cbegin() const { return start_; }
		iterator end() { return finish_; }
		iterator end() const { return finish_; }
		const_iterator cend() const { return finish_; }
		reverse_iterator rbegin() { return reverse_iterator(finish_); }
		const_reverse_iterator crbegin() const { return const_reverse_iterator(finish_); }
		reverse_iterator rend() { return reverse_iterator(start_); }
		const_reverse_iterator crend() const { return const_reverse_iterator(start_); }
		size_t size() const { return finish_ - start_; }
		size_t length() const { return size(); }
		size_t capacity() const { return endOfStorage_ - start_;}
		void clear() {
			dataAllocator::destroy(start_, finish_);
			start_ = finish_;
		}
		bool empty() const { return begin() == end(); }
		void resize(size_t n);
		void resize(size_t n, char c);
		void reserve(size_t n = 0);
		void shrink_to_fit() {
			dataAllocator::deallocate(finish_, endOfStorage_ - finish_);
			endOfStorage_ = finish_;
		}

		char& operator[] (size_t pos) { return *(start_ + pos); }
		const char& operator[] (size_t pos) const { return *(start_ + pos); }
		char& back() const { return *(finish_ - 1); }
		char& front() { return *start_; }
		const char& front() const { return *start_; }

		void push_back(char c) { insert(end(), c); }
		string& insert(size_t pos, const string& str);
		string& insert(size_t pos, const string& str, size_t subpos, size_t sublen = npos);
		string& insert(size_t pos, const char* s);
		string& insert(size_t pos, const char* s, size_t n);
		string& insert(size_t pos, size_t n, char c);
		iterator insert(iterator p, size_t n, char c);
		iterator insert(iterator p, char c);
		template <typename InputIterator>
		iterator insert(iterator p, InputIterator first, InputIterator last);
		string& append(const string& str);
		string& append(const string& str, size_t subpos, size_t sublen = npos);
		string& append(const char* s);
		string& append(const char* s, size_t n);
		string& append(size_t n, char c);
		template <typename InputIterator>
		string& append(InputIterator first, InputIterator last);
		string& operator+= (const string& str);
		string& operator+= (const char* s);
		string& operator+= (char c);

		void pop_back() { erase(end() - 1, end()); }
		string& erase(size_t pos = 0, size_t len = npos);
		iterator erase(iterator p);
		iterator erase(iterator first, iterator last);

		string& replace(size_t pos, size_t len, const string& str);
		string& replace(iterator i1, iterator i2, const string& str);
		string& replace(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen = npos);
		string& replace(size_t pos, size_t len, const char* s);
		string& replace(iterator i1, iterator i2, const char* s);
		string& replace(size_t pos, size_t len, const char* s, size_t n);
		string& replace(iterator i1, iterator i2, const char* s, size_t n);
		string& replace(size_t pos, size_t len, size_t n, char c);
		string& replace(iterator i1, iterator i2, size_t n, char c);
		template <typename InputIterator>
		string& replace(iterator i1, iterator i2, InputIterator first, InputIterator last);

		void swap(string& str) {
			STD::swap(start_, str.start_);
			STD::swap(finish_, str.finish_);
			STD::swap(endOfStorage_, str.endOfStorage_);
		}
		size_t copy(char* s, size_t len, size_t pos = 0) const {
			auto ptr = STD::uninitialized_copy(begin() + pos, begin() + pos + len, s);
			return (size_t)(ptr - s);
		}

		size_t find(const string& str, size_t pos = 0) const;
		size_t find(const char* s, size_t pos = 0) const;
		size_t find(const char* s, size_t pos, size_t n) const;
		size_t find(char c, size_t pos = 0) const;
		size_t rfind(const string& str, size_t pos = npos) const;
		size_t rfind(const char* s, size_t pos = npos) const;
		size_t rfind(const char* s, size_t pos, size_t n) const;
		size_t rfind(char c, size_t pos = npos) const;
		size_t find_first_of(const string& str, size_t pos = 0) const;
		size_t find_first_of(const char* s, size_t pos = 0) const;
		size_t find_first_of(const char* s, size_t pos, size_t n) const;
		size_t find_first_of(char c, size_t pos = 0) const;
		size_t find_last_of(const string& str, size_t pos = npos) const;
		size_t find_last_of(const char* s, size_t pos = npos) const;
		size_t find_last_of(const char* s, size_t pos, size_t n) const;
		size_t find_last_of(char c, size_t pos = npos) const;
		size_t find_first_not_of(const string& str, size_t pos = 0) const;
		size_t find_first_not_of(const char* s, size_t pos = 0) const;
		size_t find_first_not_of(const char* s, size_t pos, size_t n) const;
		size_t find_first_not_of(char c, size_t pos = 0) const;
		size_t find_last_not_of(const string& str, size_t pos = npos) const;
		size_t find_last_not_of(const char* s, size_t pos = npos) const;
		size_t find_last_not_of(const char* s, size_t pos, size_t n) const;
		size_t find_last_not_of(char c, size_t pos = npos) const;

		string substr(size_t pos = 0, size_t len = npos) const{
			len = changeVarWhenEuqalNPOS(len, size(), pos);
			return string(begin() + pos, begin() + pos + len);
		}

		int compare(const string& str) const;
		int compare(size_t pos, size_t len, const string& str) const;
		int compare(size_t pos, size_t len, const string& str,
					size_t subpos, size_t sublen = npos) const;
		int compare(const char* s) const;
		int compare(size_t pos, size_t len, const char* s) const;
		int compare(size_t pos, size_t len, const char* s, size_t n) const;
	private:
		void moveData(string& str);
		// 插入时空间不足的情况
		template<class InputIterator>
		iterator insert_aux_copy(iterator p, InputIterator first, InputIterator last);
		// 插入时空间不足的情况
		iterator insert_aux_filln(iterator p, size_t n, value_type c);
		size_type getNewCapacity(size_type len)const;
		void allocateAndFillN(size_t n, char c);
		template<class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last);
		void string_aux(size_t n, char c, std::true_type);
		template<class InputIterator>
		void string_aux(InputIterator first, InputIterator last, std::false_type);
		void destroyAndDeallocate();
		size_t rfind_aux(const_iterator cit, size_t pos, size_t lengthOfS, int cond)const;
		size_t find_aux(const_iterator cit, size_t pos, size_t lengthOfS, size_t cond)const;
		int compare_aux(size_t pos, size_t len, const_iterator cit, size_t subpos, size_t sublen)const;
		bool isContained(char ch, const_iterator first, const_iterator last)const;
		size_t changeVarWhenEuqalNPOS(size_t var, size_t minuend, size_t minue)const;
	public:
		friend std::ostream& operator <<(std::ostream& os, const string&str);
		friend std::istream& operator >> (std::istream& is, string& str);
		friend string operator+ (const string& lhs, const string& rhs);
		friend string operator+ (const string& lhs, const char* rhs);
		friend string operator+ (const char* lhs, const string& rhs);
		friend string operator+ (const string& lhs, char rhs);
		friend string operator+ (char lhs, const string& rhs);
		friend bool operator== (const string& lhs, const string& rhs);
		friend bool operator== (const char*   lhs, const string& rhs);
		friend bool operator== (const string& lhs, const char*   rhs);
		friend bool operator!= (const string& lhs, const string& rhs);
		friend bool operator!= (const char*   lhs, const string& rhs);
		friend bool operator!= (const string& lhs, const char*   rhs);
		friend bool operator<  (const string& lhs, const string& rhs);
		friend bool operator<  (const char*   lhs, const string& rhs);
		friend bool operator<  (const string& lhs, const char*   rhs);
		friend bool operator<= (const string& lhs, const string& rhs);
		friend bool operator<= (const char*   lhs, const string& rhs);
		friend bool operator<= (const string& lhs, const char*   rhs);
		friend bool operator>  (const string& lhs, const string& rhs);
		friend bool operator>  (const char*   lhs, const string& rhs);
		friend bool operator>  (const string& lhs, const char*   rhs);
		friend bool operator>= (const string& lhs, const string& rhs);
		friend bool operator>= (const char*   lhs, const string& rhs);
		friend bool operator>= (const string& lhs, const char*   rhs);
		friend void swap(string& x, string& y);
		friend std::istream& getline(std::istream& is, string& str, char delim);
		friend std::istream& getline(std::istream& is, string& str);
	};
	template <typename InputIterator>
	string::string(InputIterator first, InputIterator last) {
		string_aux(first, last, typename std::is_integral<InputIterator>::type());
	}
	template <typename InputIterator>
	string::iterator string::insert_aux_copy(STD::string::iterator p, InputIterator first, InputIterator last) {
		size_t lengthOfInsert = last - first;
		auto newCapacity = getNewCapacity(lengthOfInsert);
		iterator newStart = dataAllocator::allocate(newCapacity);
		iterator newFinish = STD::uninitialized_copy(start_, p, newStart);
		auto res = newFinish;
		newFinish = STD::uninitialized_copy(first, last, newFinish);

		destroyAndDeallocate();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = start_ + newCapacity;
		return res;
	}

	template <typename InputIterator>
	string::iterator string::insert(iterator p, InputIterator first, InputIterator last) {
		auto lengthOfLeft = capacity() - size();
		size_t lengthOfInsert = distance(first, last);
		if (lengthOfInsert <= lengthOfLeft) {
			for (iterator it = finish_ - 1; it >= p; --it) {
				*(it + lengthOfInsert) = *it;
			}
			STD::uninitialized_copy(first, last, p);
			finish_ += lengthOfInsert;
			return p + lengthOfInsert;
		} else {
			return insert_aux_copy(p, first, last);
		}
	}
	template <typename InputIterator>
	string& string::append(InputIterator first, InputIterator last) {
		insert(end(), first, last);
		return *this;
	}
	template <typename InputIterator>
	string& string::replace(STD::string::iterator i1, STD::string::iterator i2, InputIterator first,
							InputIterator last) {
		auto ptr = erase(i1, i2);
		insert(ptr, first, last);
		return *this;
	}
	template <typename InputIterator>
	void string::allocateAndCopy(InputIterator first, InputIterator last) {
		start_ = dataAllocator::allocate(last - first);
		finish_ = STD::uninitialized_copy(first, last, start_);
		endOfStorage_ = finish_;
	}
	template <typename InputIterator>
	void string::string_aux(InputIterator first, InputIterator last, std::false_type) {
		allocateAndCopy(first, last);
	}
}


#endif //STL_STRING_H
