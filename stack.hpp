#ifndef FT_STACK_HPP
# define FT_STACK_HPP

# include "vector.hpp"

namespace	ft

{

template < class T, class Container = ft::vector<T> >
class stack
{
	public:
		typedef Container								container_type;
		typedef typename Container::value_type			value_type;
		typedef typename Container::size_type			size_type;
		typedef typename Container::reference			reference;
		typedef typename Container::const_reference		const_reference;

	protected:
		container_type		c;

	public:
		explicit stack(const container_type & cont = container_type()) : c(cont) { }

		stack &		operator = (stack const & other) { c = other.c; return *this; }

		~stack() { }

	public:
		bool				empty() const					{ return c.empty(); }
		size_type			size() const					{ return c.size(); }

		reference			top()							{ return c.back(); }
		const_reference		top() const						{ return c.back(); }
		void				push(value_type const & value)	{ return c.push_back(value); }
		void				pop()							{ c.pop_back(); }

	public:
		friend bool	operator == (stack const & lhs, stack const & rhs)	{ return lhs.c == rhs.c; }
		friend bool	operator != (stack const & lhs, stack const & rhs)	{ return lhs.c != rhs.c; }
		friend bool	operator < (stack const & lhs, stack const & rhs)	{ return lhs.c < rhs.c; }
		friend bool	operator <= (stack const & lhs, stack const & rhs)	{ return lhs.c <= rhs.c; }
		friend bool	operator > (stack const & lhs, stack const & rhs)	{ return lhs.c > rhs.c; }
		friend bool	operator >= (stack const & lhs, stack const & rhs)	{ return lhs.c >= rhs.c; }

};

}

#endif
