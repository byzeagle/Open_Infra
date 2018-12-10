#ifndef IFCPARAMETERVALUE_HPP
#define IFCPARAMETERVALUE_HPP

#include "type.hpp"

template <Version T> struct IfcParameterValue {

};

template <>
struct IfcParameterValue<IFC_1>
{
	IfcParameterValue() = default;
	double m_value;

	IfcParameterValue<IFC_1> & operator = (const IfcParameterValue<Common> & obj);

};

template <>
struct IfcParameterValue<IFC_2>
{
	IfcParameterValue() = default;
	double m_value;

	IfcParameterValue<IFC_2> & operator = (const IfcParameterValue<Common> & obj);

};

template <>
struct IfcParameterValue<IFC_3>
{
	IfcParameterValue() = default;
	double m_value;

	IfcParameterValue<IFC_3> & operator = (const IfcParameterValue<Common> & obj);

};

template <>
struct IfcParameterValue<Common>
{
	IfcParameterValue() = default;
	double m_value;

	IfcParameterValue<Common> & operator = (const IfcParameterValue<IFC_1> & obj);
	IfcParameterValue<Common> & operator = (const IfcParameterValue<IFC_2> & obj);
	IfcParameterValue<Common> & operator = (const IfcParameterValue<IFC_3> & obj);
};

IfcParameterValue<Common> & IfcParameterValue<Common>::operator = (const IfcParameterValue<IFC_1> & obj)
{
	m_value = obj.m_value;
	return *this;
}

IfcParameterValue<Common> & IfcParameterValue<Common>::operator = (const IfcParameterValue<IFC_2> & obj)
{
	m_value = obj.m_value;
	return *this;
}

IfcParameterValue<Common> & IfcParameterValue<Common>::operator = (const IfcParameterValue<IFC_3> & obj)
{
	m_value = obj.m_value;
	return *this;
}

IfcParameterValue<IFC_1> & IfcParameterValue<IFC_1>::operator = (const IfcParameterValue<Common> & obj)
{
	m_value = obj.m_value;
	return *this;
}

IfcParameterValue<IFC_2> & IfcParameterValue<IFC_2>::operator = (const IfcParameterValue<Common> & obj)
{
	m_value = obj.m_value;
	return *this;
}

IfcParameterValue<IFC_3> & IfcParameterValue<IFC_3>::operator = (const IfcParameterValue<Common> & obj)
{
	m_value = obj.m_value;
	return *this;
}

#endif