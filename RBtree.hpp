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

	pointer		n;

	pointer					grandparent()
	{
		if (n && n->parent)
			return n->parent->parent;
		else
			return NULL;
	}

	pointer					uncle()
	{
		pointer	g = n->grandparent();
		if (!g)
			return NULL;
		if (n->parent == g->left)
			return g->right;
		else
			return g->left;
	}

	pointer					sibling()
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
		if (n->color == red && n->grandparent() == n) {
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

// RBtree class itself
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

		node *		_get_node()
		{
			return _tree.node_allocator::allocate(1);
		}

		void		_put_node(node * p)
		{
			_tree.node_allocator::deallocate(p, 1);
		}

		link_type	_create_node(value_type const & n)
		{
			link_type	tmp = _get_node();
			get_allocator().construct(&tmp->value, n);
			return tmp;
		}

		link_type	_clone_node(const_link_type n)
		{
			link_type	tmp = _create_node(n->value);
			tmp->color = n->color;
			tmp->left = NULL;
			tmp->right = NULL;
			return tmp;
		}

		void		_destroy_node(link_type p)
		{
			get_allocator().destroy(&p->value);
			_put_node(p);
		}

	public:
		RedBlackTree()								{ }

		RedBlackTree(Compare const & comp)
			: _tree(allocator_type(), comp)			{ }

		RedBlackTree(Compare const & comp, allocator_type const & alloc)
			: _tree(alloc, comp)					{ }

		RedBlackTree(RedBlackTree const & other)  // erase template??
			: _tree(other.get_allocator(), other._tree.key_compare)
		{
			if (other._root()) {
				_root() = _copy(other._begin(), _end());
				_leftmost() = _min(_root());
				_rightmost() = _max(_root());
				_tree.node_count = other._tree.node_count;
			}
		}

		~RedBlackTree()
		{
			_erase(_begin());
		}

		RedBlackTree &		operator = (RedBlackTree const & rhs)
		{
			if (this != &rhs) {
				clear();
				_tree.key_compare = rhs._tree.key_compare;
				if (rhs._root()) {
					_root() = _copy(rhs._begin(), _end());
					_leftmost() = _min(_root());
					_rightmost() = _max(_root());
					_tree.node_count = rhs._tree.node_count;
				}
			}
			return *this;
		}

	public:
		Compare						key_comp() const {
			return _tree.key_compare;
		}

		iterator					begin() {
			return static_cast<link_type>(_tree.header.left);
		}
		const_iterator				begin() const {
			return static_cast<const_link_type>(_tree.header.left);
		}
		iterator					end() {
			return static_cast<link_type>(&_tree.header);
		}
		const_iterator				end() const {
			return static_cast<const_link_type>(&_tree.header);
		}

		reverse_iterator			rbegin() {
			return reverse_iterator(end());
		}
		const_reverse_iterator		rbegin() const {
			return const_reverse_iterator(end());
		}
		reverse_iterator			rend() {
			return reverse_iterator(begin());
		}
		const_reverse_iterator		rend() const {
			return const_reverse_iterator(begin());
		}

		bool		empty() const		{ return _tree.node_count == 0; }
		size_type	size() const		{ return _tree.node_count; }
		size_type	max_size() const	{ return get_allocator().max_size(); }

		void		clear()
		{
			_erase(_begin());
			_leftmost() = _end();
			_root() = NULL;
			_rightmost() = _end();
			_tree.node_count = 0;
		}

	protected:
		base_pointer &				_root()				{ return _tree.header.parent; }
		const_base_pointer			_root() const		{ return _tree.header.parent; }
		base_pointer &				_leftmost()			{ return _tree.header.left; }
		const_base_pointer			_leftmost() const	{ return _tree.header.left; }
		base_pointer &				_rightmost()		{ return _tree.header.right; }
		const_base_pointer			_rightmost() const	{ return _tree.header.right; }

		link_type					_begin() {
			return static_cast<link_type>(_tree.header.parent);
		}
		const_link_type				_begin() const {
			return static_cast<const_link_type>(_tree.header.parent);
		}
		link_type					_end() {
			return static_cast<link_type>(&_tree.header);
		}
		const_link_type				_end() const {
			return static_cast<const_link_type>(&_tree.header);
		}
		static link_type			_left(base_pointer n) {
			return static_cast<link_type>(n->left);
		}
		static const_link_type		_left(const_base_pointer n) {
			return static_cast<const_link_type>(n->left);
		}
		static link_type			_right(base_pointer n) {
			return static_cast<link_type>(n->right);
		}
		static const_link_type		_right(const_base_pointer n) {
			return static_cast<const_link_type>(n->right);
		}
		static const_reference		_value(const_link_type n) {
			return n->value;
		}
		static const_reference		_value(const_base_pointer n) {
			return static_cast<const_link_type>(n)->value;
		}
		static Key const &			_key(const_link_type n) {
			return KeyOfValue()(_value(n));
		}
		static Key const &			_key(const_base_pointer n) {
			return KeyOfValue()(_value(n));
		}
		static base_pointer			_min(base_pointer n) {
			return node_base::min(n);
		}
		static const_base_pointer	_min(const_base_pointer n) {
			return node_base::min(n);
		}
		static base_pointer			_max(base_pointer n) {
			return node_base::max(n);
		}
		static const_base_pointer	_max(const_base_pointer n) {
			return node_base::max(n);
		}

	private:
		size_type		_count(const_base_pointer node)
		{
			size_type	sum = 0;

			if (!node) {
				return 0;
			}
			do {
				if (node->color == black) {
					sum++; }
				if (node == _root()) {
					break; }
				node = node->parent;
			}	while (true);
			return sum;
		}

		void			_rotate_left(base_pointer const node)
		{
			base_pointer const	pivot = node->right;
			base_pointer &		root = _root();

			node->right = pivot->left;
			if (pivot->left) {
				pivot->left->parent = node;
			}
			pivot->parent = node->parent;

			if (node == root) {
				root = pivot;										//   can i use _root()?
			}
			else if (node == node->parent->left) {
				node->parent->left = pivot;
			}
			else {
				node->parent->right = pivot;
			}
			pivot->left = node;
			node->parent = pivot;
		}

		void			_rotate_right(base_pointer const node)
		{
			base_pointer const	pivot = node->left;
			base_pointer &		root = _root();

			node->left = pivot->right;
			if (pivot->right) {
				pivot->right->parent = node;
			}
			pivot->parent = node->parent;

			if (node == root) {
				root = pivot;
			}
			else if (node == node->parent->right) {
				node->parent->right = pivot;
			}
			else {
				node->parent->left = pivot;
			}
			pivot->right = node;
			node->parent = pivot;
		}

		void			_rebalance_after_insert(base_pointer node)		// base_pointer parent)
		{
			base_pointer &	root = _tree.header.parent;

			while (node != root && node->parent->color == red) {
				base_pointer const		grandpa = node->grandparent();
				base_pointer const		uncle = node->uncle();				// using my own relatives
				if (node->parent == grandpa->left) {
					if (uncle && uncle->color == red) {
						node->parent->color = black;
						uncle->color = black;
						grandpa->color = red;
						node = grandpa;
					}
					else {
						if (node == node->sibling()) {					// ?
							node = node->parent;
							_rotate_left(node);
						}
						node->parent->color = black;
						grandpa->color = red;
						_rotate_right(grandpa);
					}
				}
				else {
					if (uncle && uncle->color == red) {
						node->parent->color = black;
						uncle->color = black;
						grandpa->color = red;
						node = grandpa;
					}
					else {
						if (node == node->sibling()) {					// ?
							node = node->parent;
							_rotate_right(node);
						}
						node->parent->color = red;
						_rotate_left(grandpa);
					}
				}
			}
			root->color = black;
		}

		iterator		_insert(base_pointer n, base_pointer parent, value_type const & v)
		{
			bool		insert_left = (n || parent == _end() ||
									  _tree.key_compare(KeyOfValue()(v), _key(parent)));
			link_type	new_node = _create_node(v);

			new_node->parent = parent;
			new_node->left = NULL;
			new_node->right = NULL;
			new_node->color = red;

			if (insert_left) {
				parent->left = new_node;
				if (parent == &_tree.header) {
					_tree.header.parent = new_node;
					_tree.header.right = new_node;
				}
				else if (parent == _tree.header.left) {
					_tree.header.left = new_node;
				}
			}
			else {
				parent->right = new_node;
				if (parent == _tree.header.right) {
					_tree.header.right = new_node;
				}
			}

			_rebalance_after_insert(new_node, parent);							// divided in two functions
			_tree.node_count++;
			return iterator(new_node);
		}

		link_type		_copy(const_link_type n, link_type p)
		{
			link_type	top = _clone_node(n);

			top->parent = p;
			if (n->right) {
				top->right = _copy(_right(n), top);
			}
			p = top;
			n = _left(n);
			while (n) {
				link_type	m = _clone_node(n);
				p->left = m;
				m->parent = p;
				if (n->right) {
					m->right = _copy(_right(n), m);
				}
				p = m;
				n = _left(n);
			}
			return top;
		}

		void			_erase(link_type n)
		{
			while (n) {
				_erase(_right(n));
				link_type	m = _left(n);
				_destroy_node(n);
				n = m;
			}
		}
};

}

}

#endif
