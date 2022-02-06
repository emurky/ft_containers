#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <memory>

// # include <vector> // delete

# include "iterator.hpp"
# include "utils.hpp"

namespace	ft

{

template < class T, class Allocator = std::allocator<T> >
class vector
{
	// Type definitions
	public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::iterator<pointer>						iterator;
		typedef ft::iterator<const_pointer>					const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	// Private members
	private:
		pointer			_start;
		pointer			_end;
		pointer			_end_cap;
		allocator_type	_alloc;

	// Private member functions
	private:
		void			_destroy_after_pos(pointer pos)
		{
			while (pos != _end)
				_alloc.destroy(--_end);
		}

	// Member functions
	public:

	//Iterators
		iterator				begin()				{ return iterator(_start); }
		const_iterator			begin() const		{ return iterator(_start); }
		iterator				end()				{ return iterator(_end); }
		const_iterator			end() const			{ return iterator(_end); }
		reverse_iterator		rbegin()			{ return reverse_iterator(_end); }
		const_reverse_iterator	rbegin() const		{ return reverse_iterator(_end); }
		reverse_iterator		rend()				{ return reverse_iterator(_start); }
		const_reverse_iterator	rend() const		{ return reverse_iterator(_start); }

	//Capacity
		size_type		size() const		{ return static_cast<size_type>(_end - _start); }
		size_type		capacity() const	{ return static_cast<size_type>(_end_cap - _start); }
		size_type		max_size() const	{ return _alloc.max_size(); }
		bool			empty() const		{ return _start == _end; }

		void			resize (size_type n, value_type val = value_type())
		{
			size_type	size = size();
			if (n < size) {
				_destroy_after_pos(_start + n);
			}
			else if (n > capacity()) {
				reserve(n);
			}
			while (size < n) {
				_alloc.construct(_start + size, val);
				size++;
			}
			_end = _start + size;
		}

		void			reserve(size_type n)
		{
			pointer		new_ptr;
			size_type	size = this->size();

			if (n <= capacity())
				return ;
			if (n > max_size())
				throw std::length_error("reserve()::length_error");
			new_ptr = _alloc.allocate(n);
			for (size_type i = 0; i < size; i++) {
				_alloc.construct(new_ptr + i, *(_start + i));
				_alloc.destroy(_start + i);
			}
			_alloc.deallocate(_start, capacity());
			_start = new_ptr;
			_end = _start + size;
			_end_cap = _start + n;
		}

	//Modifiers
		// assign
		void			push_back(value_type const & value)
		{
			size_type	cap = capacity();
			if (cap == 0) {
				reserve(1);
			}
			else if (size() + 1 > cap) {
				reserve(2 * cap);
			}
			_alloc.construct(_end, value);
			_end++;
		}

		void			pop_back()
		{
			_end--;
			_alloc.destroy(_end);
		}

		// insert
		// erase
		// swap
		void			clear()							{ _destroy_after_pos(_start); }

	//Element access
		reference		front()							{ return *_start; }
		const_reference	front() const					{ return *_start; }
		reference		operator [] (size_type n)		{ return _start[n]; }
		const_reference	operator [] (size_type n) const	{ return _start[n]; }
		reference		back()							{ return *(_end - 1); }
		const_reference	back() const					{ return *(_end - 1); }

		reference		at (size_type n) {
			if (n >= size())
				throw std::out_of_range("vector");
			return	_start;
		}

		const_reference	at (size_type n) const {
			if (n >= size())
				throw std::out_of_range("vector");
			return	_start;
		}

		// value_type *		data()							{ return _start; }
		// value_type const *	data() const					{ return _start; }

		allocator_type	get_allocator() const			{ return _alloc; }

	// Constructors
	public:
		explicit vector	(const allocator_type & alloc = allocator_type()) :
			_start(NULL), _end(NULL), _end_cap(NULL), _alloc(alloc)
		{
		}

		explicit vector	(size_type count, const value_type & value = value_type(),
						const allocator_type & alloc = allocator_type())
		{
			_alloc = alloc;
			_start = _alloc.allocate(count);
			_end = _start + count;
			_end_cap = _end;
			for (pointer it = _start; it < _end; it++)
			{
				_alloc.construct(it, value);
			}
		}

		template < class InputIterator >
		vector	(InputIterator first, InputIterator last,
				const allocator_type & alloc = allocator_type())
				// typename ft::enable_if<ft::is_integral<InputIterator>::value>::type * = 0)
		{
			size_type		cap = 0;
			InputIterator	iter = first;

			while (iter != last) {
				cap++;
				iter++;
			}
			_alloc = alloc;
			_start = _alloc.allocate(cap);
			_end = _start;
			while (first != last) {
				_alloc.construct(_end, *first);
				first++;
				_end++;
			}
			_end_cap = _end;
		}

		vector	(vector const & other);

		vector &	operator = (vector const & other)
		{
			if (this != &other)
			{
				clear();
				_alloc.deallocate(_start, capacity());
				_start = NULL;
				_end = NULL;
				_end_cap = NULL;
			}
			return *this;
		}//????????????????????????

		~vector() { }
};

}


#endif
