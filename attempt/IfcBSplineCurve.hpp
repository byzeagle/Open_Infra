#ifndef IFCBSPLINECURVE_HPP
#define IFCBSPLINECURVE_HPP

#include "variant.hpp"
#include "info.h"
#include "type.hpp"
#include <string>
#include "property.hpp"

#include "IfcBSplineCurveForm.hpp"
#include "IfcCartesianPoint.hpp"
#include "IfcCurve.hpp"

using boost::get;

// Dummy Declaration
template <Version T>
struct IfcBSplineCurve { };

template<>
struct IfcBSplineCurve<IFC_1> : public IfcCurve<IFC_1>
{
	static constexpr Version version = IFC_1;

	int Degree;
	IfcCartesianPoint<IFC_1> ControlPointsList[2];
	IfcBSplineCurveForm<IFC_1> CurveForm;
	bool ClosedCurve;
	bool SelfIntersect;

	IfcBSplineCurve<IFC_1> & operator = (const IfcBSplineCurve<Common> & obj);
};

template<>
struct IfcBSplineCurve<IFC_2> : public IfcCurve<IFC_2>
{
	static constexpr Version version = IFC_2;

	int Degree;
	IfcCartesianPoint<IFC_2> ControlPointsList[2];
	IfcBSplineCurveForm<IFC_2> CurveForm;
	bool ClosedCurve;
	bool SelfIntersect;

	IfcBSplineCurve<IFC_2> & operator = (const IfcBSplineCurve<Common> & obj);
};

template<>
struct IfcBSplineCurve<IFC_3> : public IfcCurve <IFC_3>
{
	static constexpr Version version = IFC_3;

	ifcinteger Degree;
	IfcCartesianPoint<IFC_3> ControlPointsList[2];
	IfcBSplineCurveForm<IFC_3> CurveForm;
	ifclogical ClosedCurve;
	ifclogical SelfIntersect;

	IfcBSplineCurve<IFC_3> & operator = (const IfcBSplineCurve<Common> & obj);
};

template<>
struct IfcBSplineCurve<Common> : public IfcCurve <IFC_3>
{
	Version version = Common;

	//Property<variant<int, ifcinteger>> Degree;

	struct : public Property<variant<int, ifcinteger>>
	{
		virtual variant<int, ifcinteger> & operator = (const variant<int, ifcinteger> & f) 
		{ 
			return value = f; 
		}

		virtual operator int ()
		{ 
			if (version != IFC_3)
				return get<int>(value);
			else
				throw "FUCK";
		}

		virtual operator ifcinteger const & () const
		{
			if (version == IFC_3)
				return get<ifcinteger>(value);
			else
				throw "FUCK";
		}

	} Degree2;

	IfcCartesianPoint<Common> ControlPointsList[2];
	IfcBSplineCurveForm<Common> CurveForm;

	variant<bool, ifclogical> ClosedCurve;
	variant<bool, ifclogical> SelfIntersect;

	IfcBSplineCurve<Common> & operator = (const IfcBSplineCurve<IFC_1> & obj);
	IfcBSplineCurve<Common> & operator = (const IfcBSplineCurve<IFC_2> & obj);
	IfcBSplineCurve<Common> & operator = (const IfcBSplineCurve<IFC_3> & obj);
};

IfcBSplineCurve<Common> & IfcBSplineCurve<Common>::operator = (const IfcBSplineCurve<IFC_1> & obj)
{
	version = IFC_1;
	//Degree = obj.Degree;
	//Degree.version = version;

	Degree2.version = version;
	Degree2.value = obj.Degree;

	//ControlPointsList = obj.ControlPointsList;
	//CurveForm = obj.CurveForm;
	ClosedCurve = obj.ClosedCurve;
	
	SelfIntersect = obj.SelfIntersect;


	return *this;
}

IfcBSplineCurve<Common> & IfcBSplineCurve<Common>::operator = (const IfcBSplineCurve<IFC_2> & obj)
{
	version = IFC_2;
	//Degree = obj.Degree;
	//Degree.version = version;
	//ControlPointsList = obj.ControlPointsList;
	//CurveForm = obj.CurveForm;
	ClosedCurve = obj.ClosedCurve;
	SelfIntersect = obj.SelfIntersect;
	
	return *this;
}

IfcBSplineCurve<Common> & IfcBSplineCurve<Common>::operator = (const IfcBSplineCurve<IFC_3> & obj)
{
	version = IFC_3;
	//Degree = obj.Degree;
	//Degree.version = version;

	Degree2.version = version;
	Degree2.value = obj.Degree;

	//ControlPointsList = obj.ControlPointsList;
	//CurveForm = obj.CurveForm;
	ClosedCurve = obj.ClosedCurve;
	SelfIntersect = obj.SelfIntersect;

	return *this;
}

IfcBSplineCurve<IFC_1> & IfcBSplineCurve<IFC_1>::operator = (const IfcBSplineCurve<Common> & obj)
{
	//Degree = get<int>(obj.Degree.value);
	//ControlPointsList = obj.ControlPointsList;
	//CurveForm = obj.CurveForm;
	ClosedCurve = get<bool>(obj.ClosedCurve);
	SelfIntersect = get<bool>(obj.SelfIntersect);

	return *this;
}

IfcBSplineCurve<IFC_2> & IfcBSplineCurve<IFC_2>::operator = (const IfcBSplineCurve<Common> & obj)
{
	//Degree = get<int>(obj.Degree.value);
	//ControlPointsList = obj.ControlPointsList;
	//CurveForm = obj.CurveForm;
	ClosedCurve = get<bool>(obj.ClosedCurve);
	SelfIntersect = get<bool>(obj.SelfIntersect);

	return *this;
}

IfcBSplineCurve<IFC_3> & IfcBSplineCurve <IFC_3>::operator = (const IfcBSplineCurve<Common> & obj)
{
	//Degree = get<ifcinteger>(obj.Degree.value);
	//ControlPointsList = obj.ControlPointsList;
	//CurveForm = obj.CurveForm;
	ClosedCurve = get<ifclogical>(obj.ClosedCurve);
	SelfIntersect = get<ifclogical>(obj.SelfIntersect);

	return *this;
}

#endif
