#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include "type.hpp"
#include "info.h"
#include "variant.hpp"

template <typename T>
struct Property 
{
	virtual ~Property() {}
	virtual T & operator = (const T &f) { return value = f; }
	virtual operator T const & () const { return value; }
	operator int()
	{
		return get<int>(value);
	}
	Version version = Common;
	T value;
};

#endif