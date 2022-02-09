#ifndef FT_RBTREE_HPP
# define FT_RBTREE_HPP

namespace	ft

{

namespace	rb	//tree
{

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

}

}

#endif
