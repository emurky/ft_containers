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

	// Tree
	private:
		typedef rb::RedBlackTree <	key_type,
									value_type,
									select1st<value_type>,
									key_compare,
									Allocator	>				tree_type;

		tree_type		_tree;

	// Constructors
	public:
		explicit map (key_compare const & comp = key_compare(),
					  allocator_type const & alloc= allocator_type())
			: _tree(comp, alloc)							{ }

		template < class InputIterator >
		map (InputIterator first, InputIterator last,
			 key_compare const & comp = key_compare(),
			 allocator_type const & alloc = allocator_type(),
			 typename enable_if<!is_integral<InputIterator>::value>::type * = 0)
			: _tree(comp, alloc)
		{
			_tree.insert_unique(first, last);
		}

		map (map const & other)	: _tree(other._tree)		{ }

		~map ()												{ }

		map &	operator = (map const & rhs)
		{
			_tree = rhs._tree;
			return *this;
		}

	// Iterators
		iterator				begin()				{ return _tree.begin(); }
		const_iterator			begin() const		{ return _tree.begin(); }
		iterator				end()				{ return _tree.end(); }
		const_iterator			end() const			{ return _tree.end(); }

		reverse_iterator		rbegin()			{ return _tree.rbegin(); }
		const_reverse_iterator	rbegin() const		{ return _tree.rbegin(); }
		reverse_iterator		rend()				{ return _tree.rend(); }
		const_reverse_iterator	rend() const		{ return _tree.rend(); }

	// Capacity
		bool				empty() const			{ return _tree.empty(); }
		size_type			size() const			{ return _tree.size(); }
		size_type			max_size() const		{ return _tree.max_size(); }

	// Element access
		mapped_type &		operator [] (key_type const & key)
		{
			iterator	it = lower_bound(key);

			if (it == end() || key_comp()(key, (*it).first)) {
				it = insert(it, value_type(key, mapped_type()));
			}
			return (*it).second;
		}

	// Modifiers
		pair<iterator,bool>	insert(value_type const & value)
		{
			return _tree.insert_unique(value);
		}

		iterator		insert(iterator pos, value_type const & value)
		{
			return _tree.insert_unique(pos, value);
		}

		template < class InputIterator >
		void			insert(InputIterator first, InputIterator last,
								   typename enable_if<!is_integral<InputIterator>::value>::type * = 0)
		{
			return _tree.insert_unique(first, last);
		}

		void			erase(iterator pos)						{ return _tree.erase(pos); }
		size_type		erase(key_type const & key)				{ return _tree.erase(key); }
		void			erase(iterator first, iterator last)	{ return _tree.erase(first, last); }

		void			clear()									{ _tree.clear(); }

		void			swap(map & m)							{ _tree.swap(m); }

	// Observers
		allocator_type	get_allocator() const					{ return _tree.get_allocator(); }
		key_compare		key_comp() const						{ return _tree.key_comp(); }
		value_compare	value_comp() const						{ return value_compare(_tree.key_comp()); }

	// Operations
		iterator		find(key_type const & key)				{ return _tree.find(key); }
		const_iterator	find(key_type const & key) const		{ return _tree.find(key); }

		size_type		count(key_type const & key) const		{ return _tree.find(key) == _tree.end() ? 0 : 1; }

		iterator		lower_bound(key_type const & key)		{ return _tree.lower_bound(key); }
		const_iterator	lower_bound(key_type const & key) const	{ return _tree.lower_bound(key); }

		iterator		upper_bound(key_type const & key)		{ return _tree.upper_bound(key); }
		const_iterator	upper_bound(key_type const & key) const	{ return _tree.upper_bound(key); }

		pair<iterator,iterator>					equal_range(key_type const & key) {
			return _tree.equal_range(key);
		}
		pair<const_iterator,const_iterator>		equal_range(key_type const & key) const {
			return _tree.equal_range(key);
		}

	// Non-member overloads
	public:
		friend	bool	operator == (map const & lhs, map const & rhs) {
			return lhs._tree == rhs._tree;
		}
		friend	bool	operator != (map const & lhs, map const & rhs) {
			return lhs._tree != rhs._tree;
		}
		friend	bool	operator < (map const & lhs, map const & rhs) {
			return lhs._tree < rhs._tree;
		}
		friend	bool	operator <= (map const & lhs, map const & rhs) {
			return lhs._tree <= rhs._tree;
		}
		friend	bool	operator > (map const & lhs, map const & rhs) {
			return lhs._tree > rhs._tree;
		}
		friend	bool	operator >= (map const & lhs, map const & rhs) {
			return lhs._tree >= rhs._tree;
		}
};

	template < class Key, class T, class Comp, class Alloc >
	void		swap(map<Key, T, Comp, Alloc> & lhs, map<Key, T, Comp, Alloc> & rhs)
	{
		lhs.swap(rhs);
	}

}


#endif
