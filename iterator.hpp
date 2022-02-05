#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft

{

struct output_iterator_tag												{ };
struct input_iterator_tag												{ };
struct forward_iterator_tag			: public input_iterator_tag			{ };
struct bidirectional_iterator_tag	: public forward_iterator_tag		{ };
struct random_access_iterator_tag	: public bidirectional_iterator_tag	{ };

template < class Iterator >
struct iterator_traits
{
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template < class T >
struct iterator_traits< T * >
{
	typedef ptrdiff_t					difference_type;
	typedef T							value_type;
	typedef T *							pointer;
	typedef T &							reference;
	typedef random_access_iterator_tag	iterator_category;
};

template < class T >
struct iterator_traits< T const * >
{
	typedef ptrdiff_t					difference_type;
	typedef T const						value_type;
	typedef T const *					pointer;
	typedef T const &					reference;
	typedef random_access_iterator_tag	iterator_category;
};

template < class Iterator >
class iterator
{
	public:
		typedef Iterator													iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type	diff_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;

	protected:
		iterator_type	_it;

	public:
		iterator() : _it(NULL)						{ }
		iterator(iterator const & other)			{ *this = other; }
		// iterator(pointer const ptr) : _it(ptr)	{ }
		iterator(iterator_type const it) : _it(it)	{ }
		~iterator()									{ }

		iterator &		operator = (iterator const & other)
		{
			if (this != &other) {
				_it = other._it;
			}
			return *this;
		}

		iterator_type	base() const						{ return _it; }

		reference		operator * () const					{ return *_it; }
		pointer			operator -> () const				{ return _it; }
		reference		operator [] (diff_type n) const		{ return _it[n]; }
		iterator &		operator ++ ()						{ _it++; return *this; }
		iterator		operator ++ (int)					{ iterator tmp(*this); _it++; return tmp; }
		iterator		operator + (diff_type n) const		{ iterator tmp(*this); tmp += n; return tmp; }
		iterator &		operator += (diff_type n)			{ _it += n; return *this; }
		iterator &		operator -- ()						{ _it--; return *this; }
		iterator		operator -- (int)					{ iterator tmp(*this); _it--; return tmp; }
		iterator		operator - (diff_type n) const		{ iterator tmp(*this); tmp -= n; return tmp; }
		iterator &		operator -= (diff_type n)			{ _it -= n; return *this; }

		friend iterator		operator + (diff_type n, iterator const & iter)				{ iterator ret(iter); ret += n; return ret; }
		friend diff_type	operator - (iterator const & it1, iterator const & it2)		{ return it1.base() - it2.base(); }
		friend bool			operator == (iterator const & lhs, iterator const & rhs)	{ return lhs._it == rhs._it; }
		friend bool			operator != (iterator const & lhs, iterator const & rhs)	{ return !(lhs == rhs); }
		friend bool			operator < (iterator const & lhs, iterator const & rhs)		{ return lhs._it < rhs._it; }
		friend bool			operator > (iterator const & lhs, iterator const & rhs)		{ return rhs < lhs; }
		friend bool			operator <= (iterator const & lhs, iterator const & rhs)	{ return !(rhs < lhs); }
		friend bool			operator >= (iterator const & lhs, iterator const & rhs)	{ return !(lhs < rhs); }
};

}

#endif
