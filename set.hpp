#ifndef SET_HPP
# define SET_HPP

# include <memory>

# include "RBtree.hpp"
# include "utils.hpp"

namespace	ft

{

template	<	class Key,
				class Compare = less<Key>,
				class Allocator = std::allocator<Key>
			>
class	set
{
	// Type definitions
	public:
		typedef Key											key_type;
		typedef Key											value_type;
		typedef Compare										key_compare;
		typedef Compare										value_compare;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

	private:
		typedef rb::RedBlackTree <	key_type,
									value_type,
									identity<value_type>,
									key_compare,
									Allocator	>			tree_type;

	public:
		typedef ft::rb::const_tree_iterator<value_type>		iterator;
		typedef ft::rb::const_tree_iterator<value_type>		const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef typename tree_type::iterator				tree_iter;

	// Tree
	private:
		tree_type		_tree;

	// Constructors
	public:
		explicit set (key_compare const & comp = key_compare(),
					  allocator_type const & alloc= allocator_type())
			: _tree(comp, alloc)							{ }

		template < class InputIterator >
		set (InputIterator first, InputIterator last,
			 key_compare const & comp = key_compare(),
			 allocator_type const & alloc = allocator_type(),
			 typename enable_if<!is_integral<InputIterator>::value>::type * = 0)
			: _tree(comp, alloc)
		{
			_tree.insert_unique(first, last);
		}

		set (set const & other)	: _tree(other._tree)		{ }

		~set ()												{ }

		set &	operator = (set const & rhs)
		{
			_tree = rhs._tree;
			return *this;
		}

	// Iterators
		iterator			begin() const		{ return _tree.begin(); }
		iterator			end() const			{ return _tree.end(); }
		reverse_iterator	rbegin() const		{ return _tree.rbegin(); }
		reverse_iterator	rend() const		{ return _tree.rend(); }

	// Capacity
		bool				empty() const		{ return _tree.empty(); }
		size_type			size() const		{ return _tree.size(); }
		size_type			max_size() const	{ return _tree.max_size(); }

	// Modifiers
		pair<iterator,bool>	insert(value_type const & value)
		{
			pair<tree_iter, bool>	p = _tree.insert_unique(value);

			return pair<iterator, bool>(p.first, p.second);
		}

		iterator		insert(iterator pos, value_type const & value)
		{
			return _tree.insert_unique((tree_iter &)pos, value);
		}

		template < class InputIterator >
		void			insert(InputIterator first, InputIterator last,
							   typename enable_if<!is_integral<InputIterator>::value>::type * = 0)
		{
			return _tree.insert_unique(first, last);
		}

		void			erase(iterator pos)						{ return _tree.erase((tree_iter &)pos); }
		size_type		erase(key_type const & key)				{ return _tree.erase(key); }
		void			erase(iterator first, iterator last)	{ return _tree.erase((tree_iter &)first, (tree_iter &)last); }
		void			clear()									{ _tree.clear(); }

		void			swap(set & s)							{ _tree.swap(s._tree); }

	// Observers
		allocator_type	get_allocator() const					{ return _tree.get_allocator(); }
		key_compare		key_comp() const						{ return _tree.key_comp(); }
		value_compare	value_comp() const						{ return _tree.key_comp(); }

	// Operations
		iterator		find(key_type const & key) const		{ return _tree.find(key); }
		size_type		count(key_type const & key) const		{ return _tree.find(key) == _tree.end() ? 0 : 1; }
		iterator		lower_bound(key_type const & key) const	{ return _tree.lower_bound(key); }
		iterator		upper_bound(key_type const & key) const	{ return _tree.upper_bound(key); }

		pair<iterator,iterator>					equal_range(key_type const & key) const {
			return _tree.equal_range(key);
		}

	// Non-member overloads
	public:
		friend	bool	operator == (set const & lhs, set const & rhs) {
			return lhs._tree == rhs._tree;
		}
		friend	bool	operator != (set const & lhs, set const & rhs) {
			return lhs._tree != rhs._tree;
		}
		friend	bool	operator < (set const & lhs, set const & rhs) {
			return lhs._tree < rhs._tree;
		}
		friend	bool	operator <= (set const & lhs, set const & rhs) {
			return lhs._tree <= rhs._tree;
		}
		friend	bool	operator > (set const & lhs, set const & rhs) {
			return lhs._tree > rhs._tree;
		}
		friend	bool	operator >= (set const & lhs, set const & rhs) {
			return lhs._tree >= rhs._tree;
		}
};

	template < class Key, class Comp, class Alloc >
	void		swap(set<Key, Comp, Alloc> & lhs, set<Key, Comp, Alloc> & rhs)
	{
		lhs.swap(rhs);
	}

}

#endif
