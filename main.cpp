#include <iostream>
#include <string>
#include <sstream>
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

class Test
{
	private:
		std::string	*		_str;
		int	_i;

	public:
		Test(int i) : _i(i) {
			std::stringstream	ss;
			_str = new std::string;
			ss << _i;
			ss >> *_str;
		}
		~Test() { delete _str; }
};

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
	std::cout << std::endl;

	std::cout	<< ITALIC << GREEN
				<< "Running vector tests."
				<< RESET << std::endl;

	ft::vector<int>						v_int;
	typedef ft::vector<int>::iterator	iter;

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
	std::cout << "Testing reverse_iterator:" << std::endl;
	for (ft::vector<int>::reverse_iterator rit = v_int.rbegin(); rit < v_int.rend(); rit++) {
		std::cout << *rit << ' ';
	}
	std::cout << std::endl;
	try {
		std::cout << "Testing .at() method:" << std::endl;
		std::cout << v_int.at(12) << std::endl;
		std::cout << v_int.at(0) << std::endl;
		std::cout << v_int.at(21) << std::endl;
		std::cout << v_int.at(-12) << std::endl;
	}
	catch (std::exception const & e) {
		std::cout << "Exception was caught because of a range error from at()" << std::endl;
	}
	std::cout << "Testing operator[]:" << std::endl;
	for (int i = 12; i < 22; i++) {
		std::cout << v_int[i] << ' ';
	}
	std::cout << std::endl;
	std::cout << "Testing reserve():\nv_int.capacity() = " << v_int.capacity() << std::endl;
	v_int.reserve(42);
	std::cout << "reserve(42): v_int.capacity() = " << v_int.capacity() << std::endl;
	v_int.reserve(121);
	std::cout << "reserve(121): v_int.capacity() = " << v_int.capacity() << std::endl;
	std::cout << "Testing front() and back(): " << v_int.front() << " and " << v_int.back() << std::endl;
	std::cout << "Testing copy constructor:" << std::endl;
	ft::vector<int>	v_copy(v_int);
	iter	orig_iter = v_int.begin();
	iter	copy_iter = v_copy.begin();
	std::cout << "If everything's allright the next line should be empty" << std::endl << std::endl;
	for (; orig_iter < v_int.end() && copy_iter < v_copy.end(); orig_iter++, copy_iter++) {
		if (*orig_iter != *copy_iter) {
			std::cout << "Something's wrong" << std::endl;
		}
	}
	std::cout << "Testing insert():" << std::endl;
	for (int i = 10; i > 0; i--) {
		v_int.insert(v_int.begin(), i);
	}
	std::cout << "Testing resize(5), should be \"1 2 3 4 5\":" << std::endl;
	v_int.resize(5);
	for (iter it = v_int.begin(); it < v_int.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	std::cout << "Testing resize(10), should be \"1 2 3 4 5 42 42 42 42 42\":" << std::endl;
	v_int.resize(10, 42);
	for (iter it = v_int.begin(); it < v_int.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	std::cout << "Testing swap():" << std::endl;
	v_int.swap(v_copy);
	for (iter it = v_int.begin(); it < v_int.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	std::cout << "v_int.size() = " << v_int.size() << std::endl;
	std::cout << "Testing insert() and erase():" << std::endl;
	v_int.insert(v_int.begin() + 12, v_copy.begin(), v_copy.end() - 3);
	v_int.erase(v_int.begin() + 25, v_int.end() - 12);
	for (iter it = v_int.begin(); it < v_int.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	std::cout << "v_int.size() = " << v_int.size() << std::endl;
	std::cout << "Testing assign():" << std::endl;
	v_int.assign(v_copy.begin(), v_copy.begin() + 5);
	for (iter it = v_int.begin(); it < v_int.end(); it++) {
		std::cout << *it << ' ';
	}
	std::cout << "Testing clear():" << std::endl;
	std::cout << "v_int.empty(): " << (v_int.empty() ? "yes" : "no") << std::endl;
	v_int.clear();
	std::cout << "v_int.empty(): " << (v_int.empty() ? "yes" : "no") << std::endl << std::endl;

	std::cout << "Testing with a large number of elements:" << std::endl;
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
	// for (ft::vector<std::string>::iterator it = v_test.begin(); it < v_test.end(); it++) {
	// 	std::cout << *it << std::endl;
	// }
	std::cout << "v_test.size() = " << v_test.size() << std::endl;
	std::cout << "v_test.capacity() = " << v_test.capacity() << std::endl;


	return (0);
}
