#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft

{

template < bool Cond, class T = void >
struct enable_if				{ };

template < class T >
struct enable_if < true, T >	{ typedef T type; };

template < class T >	struct is_integral					{ static const bool value = false; };

template < >	struct is_integral < bool >					{ static const bool value = true; };
template < >	struct is_integral < char >					{ static const bool value = true; };
template < >	struct is_integral < char16_t >				{ static const bool value = true; };
template < >	struct is_integral < char32_t >				{ static const bool value = true; };
template < >	struct is_integral < wchar_t >				{ static const bool value = true; };
template < >	struct is_integral < signed char >			{ static const bool value = true; };
template < >	struct is_integral < short >				{ static const bool value = true; };
template < >	struct is_integral < int >					{ static const bool value = true; };
template < >	struct is_integral < long >					{ static const bool value = true; };
template < >	struct is_integral < long long >			{ static const bool value = true; };
template < >	struct is_integral < unsigned char >		{ static const bool value = true; };
template < >	struct is_integral < unsigned short >		{ static const bool value = true; };
template < >	struct is_integral < unsigned int >			{ static const bool value = true; };
template < >	struct is_integral < unsigned long >		{ static const bool value = true; };
template < >	struct is_integral < unsigned long long >	{ static const bool value = true; };


template < class InputIterator1, class InputIterator2 >
bool		lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1) {
		if (first2 == last2 || *first2 < *first1)
			return false;
		else if (*first1 < *first2)
			return true;
		++first1; ++first2;
	}
	return (first2 != last2);
}

template < class InputIterator1, class InputIterator2, class Compare >
bool		lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2,
									Compare comp)
{
	while (first1 != last1) {
		if (first2 == last2 || comp(*first2, *first1))
			return false;
		else if (comp(*first1, *first2))
			return true;
		++first1; ++first2;
	}
	return (first2 != last2);
}

template < class InputIterator1, class InputIterator2 >
bool		equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	while (first1 != last1) {
		if (!(*first1 == *first2))
			return false;
		++first1; ++first2;
	}
	return true;
}

template < class InputIterator1, class InputIterator2, class BinaryPredicate >
bool		equal(InputIterator1 first1, InputIterator1 last1,
					InputIterator2 first2, BinaryPredicate pred)
{
	while (first1 != last1) {
		if (!pred(*first1, *first2))
			return false;
		++first1; ++first2;
	}
	return true;
}


template < class T1, class T2 >
struct pair
{
	typedef T1		first_type;
	typedef T2		second_type;

	first_type		first;
	second_type		second;

	pair()								: first(), second()					 { }

	pair (T1 const & a, T2 const & b)	: first(a), second(b)				 { }

	template < class U1, class U2 >
	pair (pair<U1,U2> const & pr)		: first(pr.first), second(pr.second) { }

	pair &	operator = (pair const & other)
	{
		first = other.first;
		second = other.second;
		return *this;
	}

	friend bool		operator == (pair const & lhs, pair const & rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	friend bool		operator != (pair const & lhs, pair const & rhs) {
		return !(lhs == rhs);
	}

	friend bool		operator < (pair const & lhs, pair const & rhs) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	friend bool		operator <= (pair const & lhs, pair const & rhs) {
		return !(rhs < lhs);
	}

	friend bool		operator > (pair const & lhs, pair const & rhs) {
		return rhs < lhs;
	}

	friend bool		operator >= (pair const & lhs, pair const & rhs) {
		return !(lhs < rhs);
	}

};

template < class T1,class T2 >
pair<T1,T2>	make_pair(T1 x, T2 y)
{
	return (pair<T1,T2>(x, y));
}


template <class Arg1, class Arg2, class Result>
struct binary_function
{
	typedef Arg1		first_argument_type;
	typedef Arg2		second_argument_type;
	typedef Result		result_type;
};

template < class T >
struct		less : public binary_function<T, T, bool>
{
	bool	operator() (T const & lhs, T const & rhs) const {
		return lhs < rhs;
	}
};


template < typename T >
void		swap(T & a, T & b)
{
	T	tmp = a;

	a = b;
	b = tmp;
}

}

#endif
