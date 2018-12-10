#ifndef IFCBSPLINECURVEWITHKNOTS_HPP
#define IFCBSPLINECURVEWITHKNOTS_HPP

#include "variant.hpp"
#include "info.h"
#include "type.hpp"
#include <string>

#include "IfcBSplineCurve.hpp"
#include "IfcParameterValue.hpp"

using boost::get;

// Dummy Declaration
template <Version T>
struct IfcBSplineCurveWithKnots { };

//template<>
//struct IfcBSplineCurveWithKnots<IFC_1> : public IfcBSplineCurve<IFC_1>
//{
//	static constexpr Version version = IFC_1;
//
//	
//
//	IfcBSplineCurveWithKnots<IFC_1> & operator = (const IfcBSplineCurveWithKnots<Common> & obj);
//};

template<>
struct IfcBSplineCurveWithKnots<IFC_2> : public IfcBSplineCurve<IFC_2>
{
	static constexpr Version version = IFC_2;

	std::vector<int> KnotMultiplicities;
	std::vector<std::shared_ptr<IfcParameterValue<IFC_2>>> Knots;

	IfcBSplineCurveWithKnots<IFC_2> & operator = (const IfcBSplineCurveWithKnots<Common> & obj);
};

template<>
struct IfcBSplineCurveWithKnots<IFC_3> : public IfcBSplineCurve <IFC_3>
{
	static constexpr Version version = IFC_3;

	std::vector<ifcinteger> KnotMultiplicities;
	std::vector<std::shared_ptr<IfcParameterValue<IFC_3>>> Knots;

	IfcBSplineCurveWithKnots<IFC_3> & operator = (const IfcBSplineCurveWithKnots<Common> & obj);
};

template<>
struct IfcBSplineCurveWithKnots<Common> : public IfcBSplineCurve <Common>
{
	Version version = Common;
	
	std::vector<variant<int,ifcinteger>> KnotMultiplicities;
	std::vector<std::shared_ptr<IfcParameterValue<Common>>> Knots;

	IfcBSplineCurveWithKnots() : IfcBSplineCurve<Common>() {};

	//IfcBSplineCurveWithKnots<Common> & operator = (const IfcBSplineCurveWithKnots<IFC_1> & obj);
	IfcBSplineCurveWithKnots<Common> & operator = (const IfcBSplineCurveWithKnots<IFC_2> & obj);
	IfcBSplineCurveWithKnots<Common> & operator = (const IfcBSplineCurveWithKnots<IFC_3> & obj);
};

//IfcBSplineCurveWithKnots<Common> & IfcBSplineCurveWithKnots<Common>::operator = (const IfcBSplineCurveWithKnots<IFC_1> & obj)
//{
//	version = IFC_1;
//	Degree = obj.Degree;
//	Degree.v = version;
//	//ControlPointsList = obj.ControlPointsList;
//	//CurveForm = obj.CurveForm;
//	ClosedCurve = obj.ClosedCurve;
//	ClosedCurve.v = version;
//	SelfIntersect = obj.SelfIntersect;
//	SelfIntersect.v = version;
//
//	return *this;
//}

IfcBSplineCurveWithKnots<Common> & IfcBSplineCurveWithKnots<Common>::operator = (const IfcBSplineCurveWithKnots<IFC_2> & obj)
{
	version = IFC_2;
	Degree = obj.Degree;
	Degree.v = version;
	//ControlPointsList = obj.ControlPointsList;
	//CurveForm = obj.CurveForm;
	ClosedCurve = obj.ClosedCurve;
	ClosedCurve.v = version;
	SelfIntersect = obj.SelfIntersect;
	SelfIntersect.v = version;

	return *this;
}

IfcBSplineCurveWithKnots<Common> & IfcBSplineCurveWithKnots<Common>::operator = (const IfcBSplineCurveWithKnots<IFC_3> & obj)
{
	version = IFC_3;
	Degree = obj.Degree;
	Degree.v = version;
	//ControlPointsList = obj.ControlPointsList;
	//CurveForm = obj.CurveForm;
	ClosedCurve = obj.ClosedCurve;
	ClosedCurve.v = version;
	SelfIntersect = obj.SelfIntersect;
	SelfIntersect.v = version;

	return *this;
}

//IfcBSplineCurveWithKnots<IFC_1> & IfcBSplineCurveWithKnots<IFC_1>::operator = (const IfcBSplineCurveWithKnots<Common> & obj)
//{
//	Degree = get<int>(obj.Degree);
//	//ControlPointsList = obj.ControlPointsList;
//	//CurveForm = obj.CurveForm;
//	ClosedCurve = get<bool>(obj.ClosedCurve);
//	SelfIntersect = get<bool>(obj.SelfIntersect);
//
//	return *this;
//}

IfcBSplineCurveWithKnots<IFC_2> & IfcBSplineCurveWithKnots<IFC_2>::operator = (const IfcBSplineCurveWithKnots<Common> & obj)
{
	Degree = get<int>(obj.Degree);
	//ControlPointsList = obj.ControlPointsList;
	//CurveForm = obj.CurveForm;
	ClosedCurve = get<bool>(obj.ClosedCurve);
	SelfIntersect = get<bool>(obj.SelfIntersect);

	return *this;
}

IfcBSplineCurveWithKnots<IFC_3> & IfcBSplineCurveWithKnots <IFC_3>::operator = (const IfcBSplineCurveWithKnots<Common> & obj)
{
	Degree = get<ifcinteger>(obj.Degree);
	//ControlPointsList = obj.ControlPointsList;
	//CurveForm = obj.CurveForm;
	ClosedCurve = get<ifclogical>(obj.ClosedCurve);
	SelfIntersect = get<ifclogical>(obj.SelfIntersect);

	return *this;
}

#endif