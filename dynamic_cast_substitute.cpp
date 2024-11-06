// dynamic_cast_substitute.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
template<typename>
struct constant
{
};
template<typename>
struct writeable
{
};
template<typename T>
struct dynamic_cast_interface
{	virtual ~dynamic_cast_interface(void) = default;
	virtual const T*getPtr(constant<T>&&) const
	{	return nullptr;
	}
	virtual T*getPtr(writeable<T>&&)
	{	return nullptr;
	}
	virtual const T&getReference(constant<T>&&) const
	{	throw std::bad_cast();
	}
	virtual T&getReference(writeable<T>&&)
	{	throw std::bad_cast();
	}
};


template<typename T>
struct dynamic_cast_implementation:T
{	virtual ~dynamic_cast_implementation(void) = default;
	template<typename ...ARGS>
	dynamic_cast_implementation(ARGS&&..._r)
		:T(std::forward<ARGS>(_r)...)
	{
	}
	using dynamic_cast_interface<T>::getPtr;
	virtual const T*getPtr(constant<T>&&) const override
	{	return this;
	}
	virtual T*getPtr(writeable<T>&&) override
	{	return this;
	}
	virtual const T&getReference(constant<T>&&) const override
	{	return *this;
	}
	virtual T&getReference(writeable<T>&&) override
	{	return *this;
	}
};

struct derive0;
struct derive1;

struct base:dynamic_cast_interface<derive0>, dynamic_cast_interface<derive1>
{	using dynamic_cast_interface<derive0>::getPtr;
	using dynamic_cast_interface<derive1>::getPtr;
	using dynamic_cast_interface<derive0>::getReference;
	using dynamic_cast_interface<derive1>::getReference;
};


struct derive0:base
{
};
struct derive1:base
{
};
int main()
{
	{	dynamic_cast_implementation<derive0> s0;
		base *const p0 = &s0;

		if (auto p0D = p0->getPtr(writeable<derive0>()))
			std::cout << "p0 is a derive0!" << std::endl;
		else
			std::cout << "p0 is not a derive0!" << std::endl;
	}
	{
		dynamic_cast_implementation<derive1> s1;
		base *const p1 = &s1;
		if (auto p1D = p1->getPtr(writeable<derive0>()))
			std::cout << "p1 is a derive0!" << std::endl;
		else
			std::cout << "p1 is not a derive0!" << std::endl;
	}	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
