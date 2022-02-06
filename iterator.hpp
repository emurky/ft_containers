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
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;

	private:
		iterator_type	_it;

	public:
		iterator() : _it(NULL)						{ }
		template <class Iter>
		iterator(iterator<Iter> const & other)		{ *this = other; }
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

		iterator_type	base() const							{ return _it; }

		reference		operator * () const						{ return *_it; }
		pointer			operator -> () const					{ return _it; }
		reference		operator [] (difference_type n) const	{ return _it[n]; }
		iterator &		operator ++ ()							{ _it++; return *this; }
		iterator		operator ++ (int)						{ iterator tmp(*this); _it++; return tmp; }
		iterator		operator + (difference_type n) const	{ return iterator(_it + n); }
		iterator &		operator += (difference_type n)			{ _it += n; return *this; }
		iterator &		operator -- ()							{ _it--; return *this; }
		iterator		operator -- (int)						{ iterator tmp(*this); _it--; return tmp; }
		iterator		operator - (difference_type n) const	{ return iterator(_it - n); }
		iterator &		operator -= (difference_type n)			{ _it -= n; return *this; }

		friend iterator			operator + (difference_type n, iterator const & iter)	{ return iterator(iter.base() + n); }
		friend difference_type	operator - (iterator const & it1, iterator const & it2)	{ return it1.base() - it2.base(); }

		friend bool			operator == (iterator const & lhs, iterator const & rhs)	{ return lhs._it == rhs._it; }
		friend bool			operator != (iterator const & lhs, iterator const & rhs)	{ return !(lhs == rhs); }
		friend bool			operator < (iterator const & lhs, iterator const & rhs)		{ return lhs._it < rhs._it; }
		friend bool			operator > (iterator const & lhs, iterator const & rhs)		{ return rhs < lhs; }
		friend bool			operator <= (iterator const & lhs, iterator const & rhs)	{ return !(rhs < lhs); }
		friend bool			operator >= (iterator const & lhs, iterator const & rhs)	{ return !(lhs < rhs); }
};

template < class Iterator >
class reverse_iterator
{
	public:
		typedef Iterator													iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;

	private:
		iterator_type	_it;

	public:
		reverse_iterator() : _it(NULL)							{ }
		template <class Iter>
		reverse_iterator(reverse_iterator<Iter> const & other)	{ *this = other; }
		// reverse_iterator(pointer const ptr) : _it(ptr)		{ }
		explicit reverse_iterator(iterator_type it) : _it(it)	{ }
		~reverse_iterator()										{ }

		template <class Iter>
		reverse_iterator &	operator = (reverse_iterator<Iter> const & other)
		{
			if (this != &other) {
				_it = other._it;
			}
			return *this;
		}

		iterator_type		base() const							{ return _it; }

		reference			operator * () const						{ iterator_type tmp = _it; return *--tmp; }
		pointer				operator -> () const					{ iterator_type tmp = _it; return --tmp; }
		reference			operator [] (difference_type n) const	{ return _it[n]; }
		reverse_iterator &	operator ++ ()							{ _it--; return *this; }
		reverse_iterator	operator ++ (int)						{ reverse_iterator tmp(*this); _it--; return tmp; }
		reverse_iterator	operator + (difference_type n) const	{ return reverse_iterator(_it - n); }
		reverse_iterator &	operator += (difference_type n)			{ _it -= n; return *this; }
		reverse_iterator &	operator -- ()							{ _it++; return *this; }
		reverse_iterator	operator -- (int)						{ reverse_iterator tmp(*this); _it++; return tmp; }
		reverse_iterator	operator - (difference_type n) const	{ return reverse_iterator(_it + n); }
		reverse_iterator &	operator -= (difference_type n)			{ _it += n; return *this; }

		friend reverse_iterator	operator + (difference_type n, reverse_iterator const & iter)			{ return reverse_iterator(iter.base() - n); }
		friend difference_type	operator - (reverse_iterator const & it1, reverse_iterator const & it2)	{ return it2.base() - it1.base(); }

		friend bool			operator == (reverse_iterator const & lhs, reverse_iterator const & rhs)	{ return lhs.base() == rhs.base(); }
		friend bool			operator != (reverse_iterator const & lhs, reverse_iterator const & rhs)	{ return lhs.base() != rhs.base(); }
		friend bool			operator < (reverse_iterator const & lhs, reverse_iterator const & rhs)		{ return lhs.base() > rhs.base(); }
		friend bool			operator > (reverse_iterator const & lhs, reverse_iterator const & rhs)		{ return lhs.base() < rhs.base(); }
		friend bool			operator <= (reverse_iterator const & lhs, reverse_iterator const & rhs)	{ return lhs.base() >= rhs.base(); }
		friend bool			operator >= (reverse_iterator const & lhs, reverse_iterator const & rhs)	{ return lhs.base() <= rhs.base(); }
};

}

#endif
