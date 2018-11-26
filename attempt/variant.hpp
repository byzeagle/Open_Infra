#ifndef VARIANT_HPP
#define VARIANT_HPP

#include "boost/variant.hpp"
#include "info.h"

// Derived Variant to overload implicit conversion operators
template <typename ... Types>
struct variant : public boost::variant<Types...>
{
	using base_type = boost::variant<Types...>;

	// inherit constructors
	using base_type::base_type;

	// add a new method
	unsigned type_size() 
	{ 
		return boost::apply_visitor(type_size_visitor(), *this); 
	}

	Version v;
	variant() {}
	variant(const Version & v) : v(version) {}

	/* Inheriting operators from boost::variant does not
	   work as it normally would. We have to add explicit
	   overloads for the operators we want to use.
	*/

	bool operator == (const variant & rhs) const 
	{
		// cast rhs to base and delegate to operator in base
		return base_type::operator==(static_cast<const base_type&>(rhs));
	}

	operator int()
	{	
		return get<int>(*this);
	}

	operator double()
	{
		return get<double>(*this);
	}

	operator float()
	{
		return get<float>(*this);
	}

	operator unsigned int()
	{
		return get<unsigned int>(*this);
	}

	operator long int()
	{
		return get<long int>(*this);
	}

	operator short int()
	{
		return get<short int>(*this);
	}

	operator size_t()
	{
		return get<size_t>(*this);
	}
};

#endif