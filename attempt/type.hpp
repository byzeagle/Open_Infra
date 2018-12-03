#ifndef TYPE_HPP
#define TYPE_HPP

#include "variant.hpp"
#include "property.hpp"
#include <iostream>

using std::ostream;

struct ifclogical
{
	bool val;

	ifclogical() : val(false) {}

	template <typename ... Args>
	ifclogical(const variant<Args...> & obj);

	template <typename ... Args>
	ifclogical & operator = (const variant<Args...> & obj);

	ifclogical & operator = (const ifclogical & obj)
	{
		val = obj.val;
		return (*this);
	}

	operator bool()
	{
		return val;
	}

	friend ostream & operator << (ostream& os, const ifclogical & obj);
};

struct ifcinteger
{
	int val;

	ifcinteger() : val(0) {}

	// Constructors

	//template <typename ... Args>
	//ifcinteger(const variant<Args...> & obj);

	//template <typename T>
	//ifcinteger(const Property<T> & obj);

	//template <typename ... Args>
	//ifcinteger & operator = (const variant<Args...> & obj);

	//template <typename T>
	//ifcinteger & operator = (const Property<T> & obj);

	ifcinteger(const ifcinteger & i) : val(i.val) {}

	ifcinteger & operator = (const int n)
	{
		val = n;
		return (*this);
	}

	ifcinteger & operator = (const ifcinteger & obj)
	{
		val = obj.val;
		return (*this);
	}

	operator int()
	{
		return val;
	}

	friend ostream & operator << (ostream& os, const ifcinteger & obj);
};

template<typename ... Args>
ifclogical::ifclogical(const variant<Args...> & obj)
{
	ifclogical x = get<ifclogical>(obj);
	val = x.val;
}

template<typename ... Args>
ifclogical & ifclogical::operator =(const variant<Args...> & obj)
{
	//val = get<bool>(obj);
}

//template<typename ... Args>
//ifcinteger::ifcinteger(const variant<Args...> & obj)
//{
//	val = boost::get<int>(obj);
//}

//template <typename T>
//ifcinteger::ifcinteger(const Property<T> & obj)
//{
//	val = get<int>(obj.value);
//}

//template <typename ... Args>
//ifcinteger & ifcinteger::operator = (const variant<Args...> & obj)
//{
//	val = boost::get<int>(obj);
//}

//template <typename T>
//ifcinteger & ifcinteger::operator = (const Property<T> & obj)
//{
	//val = obj.val;
//}

std::ostream & operator << (std::ostream & os, const ifcinteger & obj)
{
	return os << obj.val;
}

ostream & operator << (ostream& os, const ifclogical & obj)
{
	return os << obj.val;
}

#endif
