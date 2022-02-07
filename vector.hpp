#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <memory>

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
			for (pointer it = _start; it < _end; it++) {
				_alloc.construct(it, value);
			}
		}

		template < class InputIterator >
		vector	(InputIterator first, InputIterator last,
				const allocator_type & alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			_alloc = alloc;
			_start = _alloc.allocate(_get_size(first, last));
			_end = _start;
			while (first != last) {
				_alloc.construct(_end, *first);
				first++;
				_end++;
			}
			_end_cap = _end;
		}

		vector	(vector const & other)
		{
			_alloc = other.get_allocator();
			_start = _alloc.allocate(_get_size(other.begin(), other.end()));
			_end = _start;
			assign(other.begin(), other.end());
			_end_cap = _end;
		}

		vector &		operator = (vector const & other)
		{
			if (this != &other) {
				assign(other.begin(), other.end());
			}
			return *this;
		}

		~vector()
		{
			clear();
			_alloc.deallocate(_start, capacity());
		}

	// Member functions

	// Capacity
		size_type		size() const		{ return static_cast<size_type>(_end - _start); }
		size_type		capacity() const	{ return static_cast<size_type>(_end_cap - _start); }
		size_type		max_size() const	{ return _alloc.max_size(); }
		bool			empty() const		{ return _start == _end; }

		void			resize (size_type n, value_type value = value_type())
		{
			if (n < size()) {
				_destroy_after_pos(_start + n);
			}
			else if (n > capacity()) {
				reserve(n);
			}
			while (_end < _start + n) {
				_alloc.construct(_end, value);
				_end++;
			}
		}

		void			reserve(size_type n)
		{
			pointer		new_ptr;
			size_type	_size = size();

			if (n <= capacity())
				return ;
			if (n > max_size())
				throw std::length_error("vector::reserve()::length_error");
			new_ptr = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(new_ptr + i, *(_start + i));
				_alloc.destroy(_start + i);
			}
			_alloc.deallocate(_start, capacity());
			_start = new_ptr;
			_end = _start + _size;
			_end_cap = _start + n;
		}

	// Modifiers
		template < class InputIterator >
		void			assign(InputIterator first, InputIterator last,
						typename ft::enable_if <!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			size_type	new_size = _get_size(first, last);

			clear();
			if (new_size > capacity()) {
				reserve(new_size);
			}
			while (first != last) {
				_alloc.construct(_end++, *first++);
			}
		}

		void			assign(size_type n, value_type const & value)
		{
			clear();
			if (n > capacity()) {
				reserve(n);
			}
			while (n) {
				_alloc.construct(_end++, value);
				n--;
			}
		}

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

		iterator		insert(iterator pos, value_type const & value)
		{
			size_type	index = static_cast<size_type>(pos - begin());

			insert(pos, 1, value);
			return iterator(_start + index);
		}

		void			insert(iterator pos, size_type count, value_type const & value)
		{
			size_type	new_size = count + size();
			size_type	index = static_cast<size_type>(pos - begin());

			if (new_size > capacity()) {
				if (count == 1) {
					reserve(2 * capacity()); }
				else {
					reserve(new_size); }
			}
			_move_forward(_start + index, _end - 1, count);
			for (size_type i = index; i < count + index; i++) {
				_alloc.construct(_start + i, value);
			}
			_end += count;
		}

		template < class InputIterator >
		void			insert(iterator pos, InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			size_type	count = _get_size(first, last);
			size_type	new_size = count + size();
			size_type	index = static_cast<size_type>(pos - begin());

			if (new_size > capacity()) {
				reserve(new_size);
			}
			_move_forward(_start + index, _end - 1, count);
			for (size_type i = index; i < count + index; i++) {
				_alloc.construct(_start + i, *first++);
			}
			_end += count;
		}

		iterator		erase(iterator pos)
		{
			return erase(pos, pos + 1);
		}

		iterator		erase(iterator first, iterator last)
		{
			size_type	range = last - first;

			iterator it = first;
			while (it < last) {
				_alloc.destroy(it.base());
				it++;
			}
			_move_backward(it.base(), _end, range);
			_end -= range;
			return it - range;
		}

		void			swap(vector & other)
		{
			ft::swap(_start, other._start);
			ft::swap(_end, other._end);
			ft::swap(_end_cap, other._end_cap);
		}

		void			clear()							{ _destroy_after_pos(_start); }
		allocator_type	get_allocator() const			{ return _alloc; }

	// Element access
		reference		front()							{ return *_start; }
		const_reference	front() const					{ return *_start; }
		reference		back()							{ return *(_end - 1); }
		const_reference	back() const					{ return *(_end - 1); }
		reference		operator [] (size_type n)		{ return _start[n]; }
		const_reference	operator [] (size_type n) const	{ return _start[n]; }

		reference		at (size_type n)
		{
			if (n >= size())
				throw std::out_of_range("vector::at()::out_of_range");
			return	_start[n];
		}

		const_reference	at (size_type n) const
		{
			if (n >= size())
				throw std::out_of_range("vector::at()::out_of_range");
			return	_start[n];
		}

		// pointer			data()							{ return _start; }
		// pointer const	data() const					{ return _start; }

	// Iterators
		iterator				begin()			{ return iterator(_start); }
		const_iterator			begin() const	{ return iterator(_start); }
		iterator				end()			{ return iterator(_end); }
		const_iterator			end() const		{ return iterator(_end); }
		reverse_iterator		rbegin()		{ return reverse_iterator(_end); }
		const_reverse_iterator	rbegin() const	{ return reverse_iterator(_end); }
		reverse_iterator		rend()			{ return reverse_iterator(_start); }
		const_reverse_iterator	rend() const	{ return reverse_iterator(_start); }

	// Private member functions
	private:
		void			_destroy_after_pos(pointer pos)
		{
			while (pos != _end)
				_alloc.destroy(--_end);
		}

		template < class Iterator >
		size_type		_get_size(Iterator first, Iterator last)
		{
			size_type	size = 0;

			while (first != last) {
				first++;
				size++;
			}
			return size;
		}

		void			_move_forward(pointer first, pointer last, size_type offset)
		{
			while (first <= last) {
				_alloc.construct(last + offset, *last);
				_alloc.destroy(last);
				last--;
			}
		}

		void			_move_backward(pointer first, pointer last, size_type offset)
		{
			while (first < last) {
				_alloc.construct(first - offset, *first);
				_alloc.destroy(first);
				first++;
			}
		}

	// Non-member overloads
		friend void	swap(vector & lhs, vector & rhs) {
			lhs.swap(rhs);
		}

		friend bool	operator == (vector const & lhs, vector const & rhs) {
			return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		friend bool	operator != (vector const & lhs, vector const & rhs) {
			return !(lhs == rhs);
		}

		friend bool	operator < (vector const & lhs, vector const & rhs) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		friend bool	operator <= (vector const & lhs, vector const & rhs) {
			return	!(rhs < lhs);
		}

		friend bool	operator > (vector const & lhs, vector const & rhs) {
			return rhs < lhs;
		}

		friend bool	operator >= (vector const & lhs, vector const & rhs) {
			return !(lhs < rhs);
		}

};

}


#endif
