#ifndef IFCCARTESIANPOINT_HPP
#define IFCCARTESIANPOINT_HPP

#include "type.hpp"

template <Version T>
struct IfcCartesianPoint
{

};

template <>
struct IfcCartesianPoint<IFC_1>
{

};

template <>
struct IfcCartesianPoint<IFC_2>
{

};

template <>
struct IfcCartesianPoint<IFC_3>
{

};

template <>
struct IfcCartesianPoint<Common>
{

};

#endif