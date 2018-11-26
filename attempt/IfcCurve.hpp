#ifndef IFCCURVE_HPP
#define IFCCURVE_HPP

#include "type.hpp"

template <Version T>
struct IfcCurve {};

template<>
struct IfcCurve<IFC_1>
{

};

template<>
struct IfcCurve<IFC_2>
{

};

template<>
struct IfcCurve<IFC_3>
{

};

template<>
struct IfcCurve<Common>
{

};

#endif