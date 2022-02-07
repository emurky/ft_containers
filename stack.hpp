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
		container_type		_c;

	public:
		explicit stack(const container_type & cont = container_type()) : _c(cont) { }

		stack &		operator = (stack const & other) { _c = other._c; return *this; }

		~stack() { }

	public:
		bool				empty() const					{ return _c.empty(); }
		size_type			size() const					{ return _c.size(); }

		reference			top()							{ return _c.back(); }
		const_reference		top() const						{ return _c.back(); }
		void				push(value_type const & value)	{ return _c.push_back(value); }
		void				pop()							{ _c.pop_back(); }

	public:
		friend bool	operator == (stack const & lhs, stack const & rhs)	{ return lhs._c == rhs._c; }
		friend bool	operator != (stack const & lhs, stack const & rhs)	{ return lhs._c != rhs._c; }
		friend bool	operator < (stack const & lhs, stack const & rhs)	{ return lhs._c < rhs._c; }
		friend bool	operator <= (stack const & lhs, stack const & rhs)	{ return lhs._c <= rhs._c; }
		friend bool	operator > (stack const & lhs, stack const & rhs)	{ return lhs._c > rhs._c; }
		friend bool	operator >= (stack const & lhs, stack const & rhs)	{ return lhs._c >= rhs._c; }

};

}

#endif
