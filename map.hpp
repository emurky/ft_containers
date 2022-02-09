#ifndef FT_MAP_HPP
# define FT_MAP_HPP

# include <memory>

# include "RBtree.hpp"
# include "utils.hpp"

namespace	ft

{

template	<	class Key,
				class T,
				class Compare = less<Key>,
				class Allocator = std::allocator< pair<Key const, T> >
			>
class	map
{
	// Type definitions
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef pair<key_type const, mapped_type>			value_type;
		typedef Compare										key_compare;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

		typedef ft::rb::tree_iterator<value_type>			iterator;
		typedef ft::rb::const_tree_iterator<value_type>		const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		class	value_compare : public binary_function<value_type, value_type, bool>
		{
			friend class map;
			protected:
				key_compare	_comp;
				value_compare(key_compare c) : _comp(c)	{ }

			public:
				bool	operator () (value_type const & lhs, value_type const & rhs) const {
					return comp(lhs.first, rhs.first);
				}
		};

	// Constructors
		explicit map (key_compare const & comp = key_compare(),
					  allocator_type const & alloc= allocator_type())	{ (void)comp; (void)alloc; }

		template < class InputIterator >
		map (InputIterator first, InputIterator last,
			 key_compare const & comp = key_compare(),
			 allocator_type const & = allocator_type(),
			 typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0);

		map (map const & other);

		~map ()			{ }

		map &	operator = (map const & other);

	// Iterators:
		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;

		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

	// Capacity:
		bool				empty() const;
		size_type			size() const;
		size_type			max_size() const;

	// Element access:
		mapped_type &		operator [] (key_type const & key);
		mapped_type &		at(key_type const & key);
		mapped_type const &	at(key_type const & key) const;

	// Modifiers:
		pair<iterator,bool>	insert(value_type const & value);

		iterator			insert(iterator pos, value_type const & value);

		template < class InputIterator >
		void				insert(InputIterator first, InputIterator last,
								   typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0);

		void				erase(iterator pos);
		size_type			erase(key_type const & key);
		void				erase(iterator first, iterator last);

		void				clear();

		void				swap(map & m);

	// Observers:
		allocator_type		get_allocator() const;
		key_compare			key_comp() const;
		value_compare		value_comp() const;

	// Operations:
		iterator			find(key_type const & key);
		const_iterator		find(key_type const & key) const;


		size_type			count(key_type const & key) const;

		iterator			lower_bound(key_type const & key);
		const_iterator		lower_bound(key_type const & key) const;

		iterator			upper_bound(key_type const & key);
		const_iterator		upper_bound(key_type const & key) const;

		pair<iterator,iterator>					equal_range(key_type const & key);
		pair<const_iterator,const_iterator>		equal_range(key_type const & key) const;
};

}


#endif
