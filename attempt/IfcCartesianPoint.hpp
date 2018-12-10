#ifndef IFCCARTESIANPOINT_HPP
#define IFCCARTESIANPOINT_HPP

#include "type.hpp"
#include "IfcLengthMeasure.hpp"

#include <vector>

template <Version T>
struct IfcCartesianPoint
{
};

template <>
struct IfcCartesianPoint<IFC_1>
{
	IfcCartesianPoint() = default;
	std::vector<std::shared_ptr<IfcLengthMeasure<IFC_1>>> m_Coordinates;
};

template <>
struct IfcCartesianPoint<IFC_2>
{
	IfcCartesianPoint() = default;
	std::vector<std::shared_ptr<IfcLengthMeasure<IFC_2>>> m_Coordinates;
};

template <>
struct IfcCartesianPoint<IFC_3>
{
	IfcCartesianPoint() = default;
	std::vector<std::shared_ptr<IfcLengthMeasure<IFC_3>>> m_Coordinates;
};

template <>
struct IfcCartesianPoint<Common>
{
	IfcCartesianPoint() = default;
	std::vector<std::shared_ptr<IfcLengthMeasure<Common>>> m_Coordinates;
};

#endif