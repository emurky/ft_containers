#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <memory>

# include <vector> // delete

# include "iterator.hpp"

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
		// typedef std::reverse_iterator<iterator>				reverse_iterator;
		// typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;

	// Private members
	private:
		pointer			_start;
		pointer			_end;
		pointer			_end_cap;
		// size_type		_size;
		// size_type		_capacity;
		allocator_type	_alloc;

	// Member functions
	public:
		size_type	size() { return _end - _start; }
		size_type	capacity() { return _end_cap - _start; }

//Capacity
	// size
	// max_size
	// resize
	// capacity
	// empty
	// reserve
//Modifiers
	// assign
	// push_back
	// pop_back
	// insert
	// erase
	// swap
	// clear
//Element access
	// operator[]
	// at
	// front
	// back
	// data

// allocator_type get_allocator() const;

	// Constructors
	public:
		explicit vector	(const allocator_type & alloc = allocator_type()) :
			_start(NULL), _end(NULL), _end_cap(NULL), _alloc(alloc)
		{
		}

		explicit vector	(size_type count, const value_type & value = value_type(),
						const allocator_type & alloc = allocator_type()) :
			_alloc(alloc)
		{
			_start = _alloc.allocate(count);
			_end = _start + count;
			_end_cap = _end;
			for (pointer it = _start; it < _end; it++) //iterator???????????????????????
			{
				_alloc.construct(it, value);
			}
		}

		template < class InputIterator >
		vector	(InputIterator first, InputIterator last,
				const allocator_type & alloc = allocator_type())
		{
			_start = first;
			_end = last;
			_end_cap = _end;
			_alloc = alloc;
			_start = _alloc.allocate(capacity());
			for (pointer it = _start; it != _end; it++) //iterator????????????????????
			{
				_alloc.construct(it, *it);
			}
		}

		vector (vector const & other);

		// vector &	operator = (vector const & other)
		// {

		// }

};

}


#endif
