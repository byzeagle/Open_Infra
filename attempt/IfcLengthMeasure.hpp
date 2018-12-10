#ifndef IFCLENGTHMEASURE_HPP
#define IFCLENGTHMEASURE_HPP

#include "type.hpp"

template <Version T> struct IfcLengthMeasure {

};

template <>
struct IfcLengthMeasure<IFC_1>
{
	IfcLengthMeasure() = default;
	double m_value;

	IfcLengthMeasure<IFC_1> & operator = (const IfcLengthMeasure<Common> & obj);

};

template <>
struct IfcLengthMeasure<IFC_2>
{
	IfcLengthMeasure() = default;
	double m_value;

	IfcLengthMeasure<IFC_2> & operator = (const IfcLengthMeasure<Common> & obj);

};

template <>
struct IfcLengthMeasure<IFC_3>
{
	IfcLengthMeasure() = default;
	double m_value;

	IfcLengthMeasure<IFC_3> & operator = (const IfcLengthMeasure<Common> & obj);

};

template <>
struct IfcLengthMeasure<Common>
{
	IfcLengthMeasure() = default;
	double m_value;

	IfcLengthMeasure<Common> & operator = (const IfcLengthMeasure<IFC_1> & obj);
	IfcLengthMeasure<Common> & operator = (const IfcLengthMeasure<IFC_2> & obj);
	IfcLengthMeasure<Common> & operator = (const IfcLengthMeasure<IFC_3> & obj);
};

IfcLengthMeasure<Common> & IfcLengthMeasure<Common>::operator = (const IfcLengthMeasure<IFC_1> & obj)
{
	m_value = obj.m_value;
	return *this;
}

IfcLengthMeasure<Common> & IfcLengthMeasure<Common>::operator = (const IfcLengthMeasure<IFC_2> & obj)
{
	m_value = obj.m_value;
	return *this;
}

IfcLengthMeasure<Common> & IfcLengthMeasure<Common>::operator = (const IfcLengthMeasure<IFC_3> & obj)
{
	m_value = obj.m_value;
	return *this;
}

IfcLengthMeasure<IFC_1> & IfcLengthMeasure<IFC_1>::operator = (const IfcLengthMeasure<Common> & obj)
{
	m_value = obj.m_value;
	return *this;
}

IfcLengthMeasure<IFC_2> & IfcLengthMeasure<IFC_2>::operator = (const IfcLengthMeasure<Common> & obj)
{
	m_value = obj.m_value;
	return *this;
}

IfcLengthMeasure<IFC_3> & IfcLengthMeasure<IFC_3>::operator = (const IfcLengthMeasure<Common> & obj)
{
	m_value = obj.m_value;
	return *this;
}
#endif