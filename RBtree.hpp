#ifndef FT_RBTREE_HPP
# define FT_RBTREE_HPP

# include <memory>

# include "utils.hpp"

namespace	ft

{

namespace	rb	// Red-Black tree
{

// Nodes
enum	node_color	{ red = false, black = true };

struct	node_base
{
	typedef node_base *			pointer;
	typedef node_base const *	const_pointer;

	node_color	color;
	pointer		parent;
	pointer		left;
	pointer		right;

	static pointer			grandparent(pointer n)
	{
		if (n && n->parent)
			return n->parent->parent;
		else
			return NULL;
	}

	static pointer			uncle(pointer n)
	{
		pointer	g = grandparent(n);
		if (!g)
			return NULL;
		if (n->parent == g->left)
			return g->right;
		else
			return g->left;
	}

	static pointer			sibling(pointer n)
	{
		if (n == n->parent->left)
			return n->parent->right;
		else
			return n->parent->left;
	}

	static pointer			min(pointer n)
	{
		while (n->left)
			n = n->left;
		return n;
	}

	static const_pointer	min(const_pointer n)
	{
		while (n->left)
			n = n->left;
		return n;
	}

	static pointer			max(pointer n)
	{
		while (n->right)
			n = n->right;
		return n;
	}

	static const_pointer	max(const_pointer n)
	{
		while (n->right)
			n = n->right;
		return n;
	}

	static pointer			increment(pointer n)
	{
		if (n->right) {
			n = n->right;
			while (n->left) {
				n = n->left;
			}
		}
		else {
			pointer	upper = n->parent;
			while (n == upper->right) {
				n = upper;
				upper = upper->parent;
			}
			if (n->right != upper) {
				n = upper;
			}
		}
		return n;
	}

	static const_pointer	increment(const_pointer n) {
		return increment(const_cast<pointer>(n));
	}

	static pointer			decrement(pointer n)
	{
		if (n->color == red && n->grandparent(n) == n) {
			n = n->right;
		}
		else if (n->left) {
			pointer	p = n->left;
			while (p->right) {
				p = p->right;
			}
			n = p;
		}
		else {
			pointer p = n->parent;
			while (n == p->left) {
				n = p;
				p = p->parent;
			}
			n = p;
		}
		return n;
	}

	static const_pointer	decrement(const_pointer n) {
		return decrement(const_cast<pointer>(n));
	}
};

template < typename Value >
struct	node : public	node_base
{
	typedef node<Value>	link_type;

	Value				value;
};

// Iterators
template < typename T >
struct	tree_iterator
{
	typedef bidirectional_iterator_tag	iterator_category;
	typedef T							value_type;
	typedef T &							reference;
	typedef T *							pointer;
	typedef ptrdiff_t					difference_type;

	typedef tree_iterator<T>			iter;
	typedef node_base::pointer			base_pointer;
	typedef node<T> *					link_type;

	base_pointer						node;

	tree_iterator()				: node()	{ }
	tree_iterator(link_type n)	: node(n)	{ }

	reference	operator * () const  { return static_cast<link_type>(node)->value; }
	pointer		operator -> () const { return &static_cast<link_type>(node)->value; }

	iter &		operator ++ ()
	{
		node = node_base::increment(node);
		return *this;
	}

	iter		operator ++ (int)
	{
		iter	tmp = *this;
		node = node_base::increment(node);
		return tmp;
	}

	iter &		operator -- ()
	{
		node = node_base::decrement(node);
		return *this;
	}

	iter		operator -- (int)
	{
		iter	tmp = *this;
		node = node_base::decrement(node);
		return tmp;
	}

	bool		operator == (iter const & rhs) const	{ return node == rhs.node; }
	bool		operator != (iter const & rhs) const	{ return node != rhs.node; }
};

template < typename T >
struct	const_tree_iterator
{
	typedef bidirectional_iterator_tag	iterator_category;
	typedef T							value_type;
	typedef T const &					reference;
	typedef T const *					pointer;
	typedef ptrdiff_t					difference_type;

	typedef tree_iterator<T>			iter;
	typedef const_tree_iterator<T>		const_iter;
	typedef node_base::const_pointer	base_pointer;
	typedef node<T> *					link_type;

	base_pointer						node;

	const_tree_iterator()					: node()		{ }
	const_tree_iterator(link_type n)		: node(n)		{ }
	const_tree_iterator(iter const & it)	: node(it.node)	{ }

	reference		operator * () const  { return static_cast<link_type>(node)->value; }
	pointer			operator -> () const { return &static_cast<link_type>(node)->value; }

	const_iter &	operator ++ ()
	{
		node = node_base::increment(node);
		return *this;
	}

	const_iter		operator ++ (int)
	{
		const_iter	tmp = *this;
		node = node_base::increment(node);
		return tmp;
	}

	const_iter &	operator -- ()
	{
		node = node_base::decrement(node);
		return *this;
	}

	const_iter		operator -- (int)
	{
		const_iter	tmp = *this;
		node = node_base::decrement(node);
		return tmp;
	}

	bool			operator == (const_iter const & rhs) const	{ return node == rhs.node; }
	bool			operator != (const_iter const & rhs) const	{ return node != rhs.node; }

	friend	bool	operator == (iter const & lhs, const_iter const & rhs)	{ return lhs.node == rhs.node; }
	friend	bool	operator != (iter const & lhs, const_iter const & rhs)	{ return lhs.node != rhs.node; }
};

// RBTree class itself
template <	typename Key, typename Value, typename KeyOfValue, typename Compare,
			typename Alloc = std::allocator<Value>	>
class	RedBlackTree
{
	typedef typename Alloc::template rebind< node<Value> >::other	node_allocator;

	public:
		typedef Key							key_type;
		typedef Value						value_type;
		typedef value_type *				pointer;
		typedef value_type const *			const_pointer;
		typedef value_type &				reference;
		typedef value_type const &			const_reference;
		typedef node<Value> *				link_type;
		typedef node<Value> const *			const_link_type;
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;
		typedef Alloc						allocator_type;

		typedef tree_iterator<value_type>				iterator;
		typedef const_tree_iterator<value_type>			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	protected:
		typedef node_base::pointer			base_pointer;
		typedef node_base::const_pointer	const_base_pointer;
		typedef node<Value>					node;

		template < typename KeyCompare >
		struct	tree		: public node_allocator
		{
			KeyCompare		key_compare;
			node_base		header;
			size_type		node_count;

			tree(node_allocator const & alloc = node_allocator(),
				 KeyCompare const & comp = KeyCompare()) :
			node_allocator(alloc), key_compare(comp), node_count(0)
			{
				header.color = red;
				header.parent = NULL;
				header.left = &header;
				header.right = &header;
			}
		};

	public:
		allocator_type		get_allocator() const {
			return *static_cast<node_allocator const *>(&_tree);
		}

	protected:
		tree<Compare>		_tree;

		node *		get_node()
		{
			return _tree.node_allocator::allocate(1);
		}

		void		put_node(node * p)
		{
			_tree.node_allocator::deallocate(p, 1);
		}

		link_type	create_node(value_type const & n)
		{
			link_type	tmp = get_node();
			get_allocator().construct(&tmp->value, n);
			return tmp;
		}

		link_type	clone_node(const_link_type n)
		{
			link_type	tmp = create_node(n->value);
			tmp->color = n->color;
			tmp->left = NULL;
			tmp->right = NULL;
			return tmp;
		}

		void		destroy_node(link_type p)
		{
			get_allocator().destroy(&p->value);
			put_node(p);
		}

	protected:
		base_pointer &				root()				{ return _tree.header.parent; }
		const_base_pointer			root() const		{ return _tree.header.parent; }
		base_pointer &				leftmost()			{ return _tree.header.left; }
		const_base_pointer			leftmost() const	{ return _tree.header.left; }
		base_pointer &				rightmost()			{ return _tree.header.right; }
		const_base_pointer			rightmost() const	{ return _tree.header.right; }

		link_type					begin() {
			return static_cast<link_type>(_tree.header.parent);
		}
		const_link_type				begin() const {
			return static_cast<const_link_type>(_tree.header.parent);
		}
		link_type					end() {
			return static_cast<link_type>(&_tree.header);
		}
		const_link_type				end() const {
			return static_cast<const_link_type>(&_tree.header);
		}
		static link_type			left(base_pointer n) {
			return static_cast<link_type>(n->left);
		}
		static const_link_type		left(const_base_pointer n) {
			return static_cast<const_link_type>(n->left);
		}
		static link_type			right(base_pointer n) {
			return static_cast<link_type>(n->right);
		}
		static const_link_type		right(const_base_pointer n) {
			return static_cast<const_link_type>(n->right);
		}
		static const_reference		value(const_link_type n) {
			return n->value;
		}
		static const_reference		value(const_base_pointer n) {
			return static_cast<const_link_type>(n)->value;
		}
		static Key const &			key(const_link_type n) {
			return KeyOfValue()(value(n));
		}
		static Key const &			key(const_base_pointer n) {
			return KeyOfValue()(value(n));
		}
		static base_pointer			min(base_pointer n) {
			return node_base::min(n);
		}
		static const_base_pointer	min(const_base_pointer n) {
			return node_base::min(n);
		}
		static base_pointer			max(base_pointer n) {
			return node_base::max(n);
		}
		static const_base_pointer	max(const_base_pointer n) {
			return node_base::max(n);
		}
};

}

}

#endif
