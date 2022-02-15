#include <iostream>
#include <string>
#include <fstream>
#include <deque>

#include "colors.h"

#ifndef SWITCH
# define SWITCH 1
#endif

#define FT	SWITCH
#define STD	!SWITCH

#if		STD //CREATE A REAL STL EXAMPLE
	#include <vector>
	#include <stack>
	#include <map>
	#include <set>
	namespace ft = std;
#elif	FT
	#include "vector.hpp"
	#include "stack.hpp"
	#include "map.hpp"
	#include "set.hpp"
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs)
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

void	print_testing(std::string str)
{
	std::cout << CYAN << str << RESET << std::endl;
}

int main(int argc, char** argv) {
	std::cout	<< ITALIC << GREEN
				<< "Running tests in \"main.cpp\" from intra subject."
				<< RESET << std::endl;
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}

	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl << std::endl;

	std::cout	<< ITALIC << GREEN
				<< "Running vector tests."
				<< RESET << std::endl;

	ft::vector<int>						v_int;
	typedef ft::vector<int>::iterator	iter;

	ft::vector<int>::iterator iter1;
	ft::vector<int>::const_iterator const_iter1;

	const_iter1 = iter1;
	// iter1 = const_iter1;
	print_testing("Iterators assignment done successfully (const_iter = iter)");
	print_testing("Testing capacity methods:");
	std::cout << "v_int.empty(): " << (v_int.empty() ? "yes" : "no") << std::endl;
	std::cout << "v_int.max_size() = " << v_int.max_size() << std::endl;
	std::cout << "v_int.size() = " << v_int.size() << std::endl;
	std::cout << "v_int.capacity() = " << v_int.capacity() << std::endl;
	v_int.assign(12, 42);
	std::cout << "v_int.empty() after assign(): " << (v_int.empty() ? "yes" : "no") << std::endl;
	std::cout << "v_int.size() after assign() = " << v_int.size() << std::endl;
	std::cout << "v_int.capacity() after assign() = " << v_int.capacity() << std::endl;
	for (int i = -42; i <= 21; i++) {
		v_int.push_back(i);
	}
	std::cout << "v_int.size() after push_back() = " << v_int.size() << std::endl;
	std::cout << "v_int.capacity() = " << v_int.capacity() << std::endl;
	print_testing("Testing reverse_iterator:");
	for (ft::vector<int>::reverse_iterator rit = v_int.rbegin(); rit < v_int.rend(); rit++) {
		std::cout << *rit << ' ';
	}
	std::cout << std::endl;
	try {
		print_testing("Testing .at() method:");
		std::cout << v_int.at(12) << std::endl;
		std::cout << v_int.at(0) << std::endl;
		std::cout << v_int.at(21) << std::endl;
		std::cout << v_int.at(-12) << std::endl;
	}
	catch (std::exception const & e) {
		std::cout << "Exception was caught because of a range error from at()" << std::endl;
	}
	print_testing("Testing operator[]:");
	for (int i = 12; i < 22; i++) {
		std::cout << v_int[i] << ' ';
	}
	std::cout << std::endl;
	print_testing("Testing reserve():");
	std::cout << "v_int.capacity() = " << v_int.capacity() << std::endl;
	v_int.reserve(42);
	std::cout << "reserve(42): v_int.capacity() = " << v_int.capacity() << std::endl;
	v_int.reserve(121);
	std::cout << "reserve(121): v_int.capacity() = " << v_int.capacity() << std::endl;
	std::cout << CYAN << "Testing front() and back(): " << RESET << v_int.front() << " and " << v_int.back() << std::endl;
	print_testing("Testing copy constructor:");
	ft::vector<int>	v_copy(v_int);
	iter	orig_iter = v_int.begin();
	iter	copy_iter = v_copy.begin();
	std::cout << "If everything's allright the next line should be empty" << std::endl << std::endl;
	for (; orig_iter < v_int.end() && copy_iter < v_copy.end(); orig_iter++, copy_iter++) {
		if (*orig_iter != *copy_iter) {
			std::cout << "Something's wrong" << std::endl;
		}
	}
	print_testing("Testing insert():");
	for (int i = 10; i > 0; i--) {
		v_int.insert(v_int.begin(), i);
	}
	print_testing("Testing resize(5), should be \"1 2 3 4 5\":");
	v_int.resize(5);
	for (iter it = v_int.begin(); it < v_int.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	print_testing("Testing resize(10), should be \"1 2 3 4 5 42 42 42 42 42\":");
	v_int.resize(10, 42);
	for (iter it = v_int.begin(); it < v_int.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	print_testing("Testing swap():");
	v_int.swap(v_copy);
	for (iter it = v_int.begin(); it < v_int.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	std::cout << "v_int.size() = " << v_int.size() << std::endl;
	print_testing("Testing insert() and erase():");
	v_int.insert(v_int.begin() + 12, v_copy.begin(), v_copy.end() - 3);
	v_int.erase(v_int.begin() + 25, v_int.end() - 12);
	for (iter it = v_int.begin(); it < v_int.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	std::cout << "v_int.size() = " << v_int.size() << std::endl;
	print_testing("Testing assign():");
	v_int.assign(v_copy.begin(), v_copy.begin() + 5);
	for (iter it = v_int.begin(); it < v_int.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	print_testing("Testing clear():");
	std::cout << "v_int.empty(): " << (v_int.empty() ? "yes" : "no") << std::endl;
	v_int.clear();
	std::cout << "v_int.empty(): " << (v_int.empty() ? "yes" : "no") << std::endl << std::endl;

	print_testing("Testing with a large number of elements:");
	std::ifstream	tree("RBtree.hpp");
	std::string		str;
	ft::vector<std::string>	v_test;
	while (tree.good()) {
		getline(tree, str);
		for (int i = 0; i < 1000; i++) {
			v_test.push_back(str);
		}
	}
	ft::vector<std::string>	v_salam;
	v_salam.assign(210000, "salam aleykum");
	v_test.insert(v_test.begin() + 212121, v_salam.begin(), v_salam.end());
	v_test.erase(v_test.begin(), v_test.begin() + 844221);
	for (ft::vector<std::string>::iterator it = v_test.begin(); it < v_test.end(); it++) {
		if (rand() % 1000 == 42) {
			std::cout << *it << std::endl;
		}
	}
	std::cout << "v_test.size() = " << v_test.size() << std::endl;
	std::cout << "v_test.capacity() = " << v_test.capacity() << std::endl;
	std::cout << std::endl;
	ft::vector<std::string>	v_tmp;
	v_tmp = v_test;
	print_testing("Testing operator overloads:");
	std::cout << "operator == " << (v_test == v_salam ? "true" : "false") << std::endl;
	std::cout << "operator == " << (v_test == v_tmp ? "true" : "false") << std::endl;
	std::cout << "operator != " << (v_test != v_salam ? "true" : "false") << std::endl;
	std::cout << "operator < " << (v_test < v_salam ? "true" : "false") << std::endl;
	std::cout << "operator <= " << (v_test <= v_salam ? "true" : "false") << std::endl;
	std::cout << "operator > " << (v_test > v_salam ? "true" : "false") << std::endl;
	std::cout << "operator >= " << (v_test >= v_salam ? "true" : "false") << std::endl;
	std::cout << "operator > " << (v_test > v_tmp ? "true" : "false") << std::endl;
	std::cout << "operator >= " << (v_test >= v_tmp ? "true" : "false") << std::endl;

	std::cout	<< std::endl
				<< ITALIC << GREEN
				<< "Running stack tests."
				<< RESET << std::endl;

	ft::stack<int, std::deque<int> >	st_test;
	print_testing("Stack was created with std::deque container");
	print_testing("Testing capacity methods:");
	std::cout << "st_test.empty(): " << (st_test.empty() ? "yes" : "no") << std::endl;
	std::cout << "st_test.size() = " << st_test.size() << std::endl;
	print_testing("Testing push() and size() again:");
	for (int i = 1; i < 4243; i++) {
		st_test.push(i);
	}
	std::cout << "st_test.size() = " << st_test.size() << std::endl;
	print_testing("Testing top():");
	std::cout << "st_test.top() = " << st_test.top() << std::endl;
	print_testing("Testing pop():");
	for (int i = 0; i < 4200; i++) {
		st_test.pop();
	}
	std::cout << "st_test.top() = " << st_test.top() << std::endl;
	std::cout << "st_test.size() = " << st_test.size() << std::endl;
	std::cout << "st_test.empty(): " << (st_test.empty() ? "yes" : "no") << std::endl;

	std::cout	<< std::endl
				<< ITALIC << GREEN
				<< "Running map tests."
				<< RESET << std::endl;

	ft::map<int, int>	m_test;
	print_testing("Testing capacity methods:");
	std::cout << "m_test.empty(): " << (m_test.empty() ? "yes" : "no") << std::endl;
	std::cout << "m_test.size() = " << m_test.size() << std::endl;

	print_testing("Testing operator[]:");
	for (int i = 0; i < 21420; i++) {
		m_test[i] = rand();
	}

	print_testing("Testing iterator, insert() and erase():");
	ft::map<int,int>::iterator	map_it = m_test.begin();
	for (int i = 0; i < 12000; i++) {
		map_it++;
	}
	for (int i = 21420; i < 21420 * 2; i++) {
		m_test.insert(map_it, ft::make_pair(i, rand()));
	}
	for (int i = 420; i < 42000; i++) {
		m_test.erase(i);
	}
	print_testing("And testing reverse_iterator:");
	for (ft::map<int,int>::reverse_iterator m_iter = m_test.rbegin(); m_iter != m_test.rend(); m_iter++) {
		std::cout << m_iter->first << ' ' << m_iter->second << ' ';
	}
	std::cout << std::endl;
	std::cout << "m_test.empty(): " << (m_test.empty() ? "yes" : "no") << std::endl;
	std::cout << "m_test.size() = " << m_test.size() << std::endl;
	print_testing("Testing find():");
	for (int i = 0; i < 21; i++) {
		std::cout << m_test.find(i)->first << ' ' << m_test.find(i)->second << std::endl;
	}
	ft::map<int, int>	m_copy;
	m_copy = m_test;

	ft::map<int,int>::iterator m_it = m_copy.begin();
	for (int i = 0; i < 21; i++) {
		m_it++;
	}
	m_copy.erase(m_it, m_copy.end());
	print_testing("Testing swap():");
	ft::swap(m_copy, m_test);
	for (ft::map<int,int>::iterator m_iter = m_test.begin(); m_iter != m_test.end(); m_iter++) {
		std::cout << m_iter->first << ' ' << m_iter->second << ' ';
	}
	std::cout << std::endl;
	std::cout << "m_test.size() = " << m_test.size() << std::endl;
	print_testing("Testing lower and upper bounds:");
	std::cout << "m_test.upper_bound(12)->second " << m_test.upper_bound(12)->second << std::endl;
	std::cout << "m_test.upper_bound(0)->second " << m_test.upper_bound(0)->second << std::endl;
	std::cout << "m_test.lower_bound(12)->second " << m_test.lower_bound(12)->second << std::endl;
	std::cout << "m_test.lower_bound(0)->second " << m_test.lower_bound(0)->second << std::endl;
	print_testing("Testing equal_range():");
	std::cout << m_test.equal_range(1).first->first << ' ' << m_test.equal_range(1).second->first << ' ' << std::endl;
	std::cout << m_test.equal_range(1).first->second << ' ' << m_test.equal_range(1).second->second << ' ' << std::endl;
	print_testing("Testing count():");
	std::cout << "m_test.count(12) = " << m_test.count(12) << std::endl;
	std::cout << "m_test.count(424242424242) = " << m_test.count(42424242) << std::endl;
	print_testing("Testing clear():");
	m_copy.clear();
	std::cout << "m_copy.empty() after clear(): " << (m_copy.empty() ? "yes" : "no") << std::endl;
	print_testing("Testing operator overloads:");
	std::cout << "operator == " << (m_test == m_copy ? "true" : "false") << std::endl;
	std::cout << "operator == " << (m_test == m_copy ? "true" : "false") << std::endl;
	std::cout << "operator != " << (m_test != m_copy ? "true" : "false") << std::endl;
	std::cout << "operator < " << (m_test < m_copy ? "true" : "false") << std::endl;
	std::cout << "operator <= " << (m_test <= m_copy ? "true" : "false") << std::endl;
	std::cout << "operator > " << (m_test > m_copy ? "true" : "false") << std::endl;
	std::cout << "operator >= " << (m_test >= m_copy ? "true" : "false") << std::endl;

	std::cout	<< std::endl
				<< ITALIC << GREEN
				<< "Running set tests."
				<< RESET << std::endl;

	ft::set<int>	s_test;
	print_testing("Testing capacity methods:");
	std::cout << "s_test.empty(): " << (s_test.empty() ? "yes" : "no") << std::endl;
	std::cout << "s_test.size() = " << s_test.size() << std::endl;

	print_testing("Testing iterator, insert() and erase():");
	for (int i = 0; i < 43; i++) {
		s_test.insert(i);
	}
	for (int i = 22; i < 42; i++) {
		s_test.erase(i);
	}
	print_testing("And testing reverse_iterator:");
	for (ft::set<int>::reverse_iterator s_iter = s_test.rbegin(); s_iter != s_test.rend(); s_iter++) {
		std::cout << *s_iter << ' ' ;
	}
	std::cout << std::endl;
	std::cout << "s_test.empty(): " << (s_test.empty() ? "yes" : "no") << std::endl;
	std::cout << "s_test.size() = " << s_test.size() << std::endl;
	print_testing("Testing find():");
	for (int i = 0; i < 21; i++) {
		std::cout << *s_test.find(i) << ' ' << std::endl;
	}
	ft::set<int>	s_copy;
	s_copy = s_test;

	ft::set<int>::iterator s_it = s_copy.begin();
	for (int i = 0; i < 21; i++) {
		s_it++;
	}
	s_copy.erase(s_it, s_copy.end());
	print_testing("Testing swap():");
	ft::swap(s_copy, s_test);
	for (ft::set<int>::iterator s_iter = s_test.begin(); s_iter != s_test.end(); s_iter++) {
		std::cout << *s_iter << ' ';
	}
	std::cout << std::endl;
	std::cout << "s_test.size() = " << s_test.size() << std::endl;
	print_testing("Testing lower and upper bounds:");
	std::cout << "s_test.upper_bound(12)->second " << *s_test.upper_bound(12) << std::endl;
	std::cout << "s_test.upper_bound(0)->second " << *s_test.upper_bound(0) << std::endl;
	std::cout << "s_test.lower_bound(12)->second " << *s_test.lower_bound(12) << std::endl;
	std::cout << "s_test.lower_bound(0)->second " << *s_test.lower_bound(0) << std::endl;
	print_testing("Testing count():");
	std::cout << "s_test.count(12) = " << s_test.count(12) << std::endl;
	std::cout << "s_test.count(424242424242) = " << s_test.count(42424242) << std::endl;
	print_testing("Testing clear():");
	s_copy.clear();
	std::cout << "s_copy.empty() after clear(): " << (s_copy.empty() ? "yes" : "no") << std::endl;
	print_testing("Testing operator overloads:");
	std::cout << "operator == " << (s_test == s_copy ? "true" : "false") << std::endl;
	std::cout << "operator == " << (s_test == s_copy ? "true" : "false") << std::endl;
	std::cout << "operator != " << (s_test != s_copy ? "true" : "false") << std::endl;
	std::cout << "operator < " << (s_test < s_copy ? "true" : "false") << std::endl;
	std::cout << "operator <= " << (s_test <= s_copy ? "true" : "false") << std::endl;
	std::cout << "operator > " << (s_test > s_copy ? "true" : "false") << std::endl;
	std::cout << "operator >= " << (s_test >= s_copy ? "true" : "false") << std::endl;

	return (0);
}
