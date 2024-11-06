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

struct realConstant;
struct integerConstant;

struct expression:dynamic_cast_interface<realConstant>, dynamic_cast_interface<integerConstant>
{	using dynamic_cast_interface<realConstant>::getPtr;
	using dynamic_cast_interface<integerConstant>::getPtr;
	using dynamic_cast_interface<realConstant>::getReference;
	using dynamic_cast_interface<integerConstant>::getReference;
};


struct realConstant:expression
{
};
struct integerConstant:expression
{
};
int main()
{
	{	dynamic_cast_implementation<realConstant> s0;
		const expression *const p0 = &s0;

		if (auto p0D = p0->getPtr(dummy<realConstant>()))
			std::cout << "p0 is a realConstant!" << std::endl;
		else
			std::cout << "p0 is not a realConstant!" << std::endl;
	}
	{
		dynamic_cast_implementation<integerConstant> s1;
		expression *const p1 = &s1;
		if (auto p1D = p1->getPtr(dummy<realConstant>()))
			std::cout << "p1 is a realConstant!" << std::endl;
		else
			std::cout << "p1 is not a realConstant!" << std::endl;
	}	
}
