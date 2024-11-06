#include <iostream>
template<typename>
struct dummy
{
};
template<typename T>
struct dynamic_cast_interface
{	virtual ~dynamic_cast_interface(void) = default;
	virtual const T*getPtr(const dummy<T>&) const
	{	return nullptr;
	}
	virtual T*getPtr(const dummy<T>&)
	{	return nullptr;
	}
	virtual const T&getReference(const dummy<T>&) const
	{	throw std::bad_cast();
	}
	virtual T&getReference(const dummy<T>&)
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
	using dynamic_cast_interface<T>::getReference;
	virtual const T*getPtr(const dummy<T>&) const override
	{	return this;
	}
	virtual T*getPtr(const dummy<T>&) override
	{	return this;
	}
	virtual const T&getReference(const dummy<T>&) const override
	{	return *this;
	}
	virtual T&getReference(const dummy<T>&) override
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
		const base *const p0 = &s0;

		if (auto p0D = p0->getPtr(dummy<derive0>()))
			std::cout << "p0 is a derive0!" << std::endl;
		else
			std::cout << "p0 is not a derive0!" << std::endl;
	}
	{
		dynamic_cast_implementation<derive1> s1;
		base *const p1 = &s1;
		if (auto p1D = p1->getPtr(dummy<derive0>()))
			std::cout << "p1 is a derive0!" << std::endl;
		else
			std::cout << "p1 is not a derive0!" << std::endl;
	}	
}
