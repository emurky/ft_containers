#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <memory>

# include <vector> // delete

namespace	ft

{

template < class T, class Allocator = std::allocator<T> >
class vector
{
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

	private:
		pointer			_start;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_allocator;

	public:
		explicit vector (const allocator_type & alloc = allocator_type()) :
			_array(NULL), _size(0), _capacity(0), _allocator(alloc)
		{
		}

		explicit vector (size_type count, const value_type & value = value_type(),
						const allocator_type & alloc = allocator_type()) :
			_size(count), _capacity(count), _allocator(alloc)
		{
			_array = _allocator.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
			{
				_allocator.construct(_array + i, value);
			}
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
				const allocator_type & alloc = allocator_type())
		{
			_size = last - first;
			_capacity = _size;
			_allocator = alloc;
			_array = _allocator.allocate(_capacity);
			for (size_type i = 0; first != last; i++, first++)
			{
				_allocator.construct(_array + i, *first);
			}
		}

		vector (const vector & other);
};

}


#endif
