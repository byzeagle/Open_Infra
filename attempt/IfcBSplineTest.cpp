#include <string>
#include <iostream>
#include <vector>
#include <array>
#include "IfcBSplineCurveWithKnots.hpp"
#include "type.hpp"
#include "variant.hpp"

//using boost::variant;
using boost::get;
using std::cout;
using std::endl;
using std::ostream;

//enum Version : int {IFC_1, IFC_2, IFC_3, Common};

std::string display(Version v)
{
	switch (v)
	{
	case IFC_1:
		return "IFC_1";
	case IFC_2:
		return "IFC_2";
	case IFC_3:
		return "IFC_3";
	case Common:
		return "SuperSet";
	}
}


// Compute B-Spline basis functions for given curve value t
static void computeBSplineBasisFunctions(
	const uint8_t order, // k: order of basis and polynomial of degree k - 1
	const double t, // t: arbitrary value on B-Spline curve
	const uint32_t numControlPoints, // n + 1 control points
	const std::vector<double>& knotVector, // t_i: knot points
	std::vector<double>& basisFuncs)
{
	const uint8_t degree = order - 1;
	const uint16_t numBasisFuncs = degree + numControlPoints;
	const uint16_t numKnots = order + numControlPoints;
	// create temporary basis functions of size k + n (or d + (n + 1), with d = k - 1)
	std::vector<double> tempBasisFuncs(numBasisFuncs, 0.0);

	// intialize first order basis functions
	for (auto i = 0; i < numBasisFuncs; ++i)
	{
		const double knot = knotVector[i];
		const double knotNext = knotVector[i + 1];
		if (t >= knot && t < knotNext && knot < knotNext)
		{
			tempBasisFuncs[i] = 1.0;
		}
	}

	double basisFuncFirst = 0.0;
	double basisFuncSecond = 0.0;

	// build basis functions of higher order up-to order = degree
	for (int k = 1; k <= degree; ++k)
	{
		for (int i = 0; i < numBasisFuncs - k; ++i)
		{
			const double t_i = knotVector[i];
			const double t_ik = knotVector[i + k];
			const double t_ik1 = knotVector[i + k + 1];
			const double t_i1 = knotVector[i + 1];
			// function is zero if basis is zero or denominator is zero
			if (tempBasisFuncs[i] == 0 || t_ik == t_i) { basisFuncFirst = 0.0; }
			else
			{
				// apply formula of first part
				basisFuncFirst = (t - t_i) / (t_ik - t_i) * tempBasisFuncs[i];
			}

			// function is zero if basis is zero or denominator is zero
			if (tempBasisFuncs[i + 1] == 0 || t_ik1 == t_i1) { basisFuncSecond = 0.0; }
			else
			{
				// apply formula of first part
				basisFuncSecond = (t_ik1 - t) / (t_ik1 - t_i1) * tempBasisFuncs[i + 1];
			}

			// compute sum and set as basis function for next order
			tempBasisFuncs[i] = basisFuncFirst + basisFuncSecond;
		}
	}

	const uint32_t numBasis = numControlPoints;
	for (int j = 0; j < numBasis; ++j)
	{
		basisFuncs[j] = tempBasisFuncs[j];
	}
}

static void computeBSplineCurve(
	const uint8_t order,
	const uint32_t numCurvePoints,
	const uint32_t numControlPoints,
	const std::vector<std::array<double, 3>>& controlPoints,
	const std::vector<double>& weights,
	const std::vector<double>& knotVector,
	std::vector<std::array<double, 3>>& curvePoints)
{

	// curve is defined for [t_p;t_m-p], m := number of knots - 1
	const uint32_t firstIndex = order - 1;
	const uint32_t lastIndex = knotVector.size() - order;

	const double knotStart = knotVector[firstIndex];
	const double knotEnd = knotVector[lastIndex];
	const double knotRange = knotEnd - knotStart;

	// compute step size
	const double step = knotRange / static_cast<double>(numCurvePoints - 1);

	std::vector<double> basisFuncs(numControlPoints, 0.0);
	// start with first valid knot
	double t = knotStart;
	// at the end, subtract current knot value with this to avoid zero-vectors (since last knot value is excluded by definition)
	const double accuracy = 0.0000001;

	for (auto i = 0; i < numCurvePoints; ++i)
	{
		if (i == numCurvePoints - 1) { t = knotEnd - accuracy; }

		// 1) Evaluate basis functions at curve point t
		computeBSplineBasisFunctions(order, t, numControlPoints, knotVector, basisFuncs);
		// 2) Compute exact point
		std::array<double, 3> point = { 0,0,0 };
		// 2i) If B-spline surface is rational, weights and their sum have to considered, as well
		double weightSum = 0.0;

		for (int j = 0; j < numControlPoints; ++j)
		{
			const double basisFunc = basisFuncs[j];
			const std::array<double, 3>& controlPoint = controlPoints[j];

			if (!weights.empty())
			{
				// 3a) apply formula for rational B-spline surfaces
				const double weightProduct = weights[j] * basisFunc;
				//point += weightProduct * controlPoint;
				for (int i = 0; i < 3; i++)
					point[i] += weightProduct * controlPoint[i];

				weightSum += weightProduct;
			}
			else
			{
				// 3b) apply formula for normal B-spline curves
				//point += basisFunc * controlPoint;
				for (int i = 0; i < 3; i++)
					point[i] += basisFunc * controlPoint[i];
			}

		}

		if (!weights.empty())
		{
			//point /= weightSum;
			for (int i = 0; i < 3; i++)
				point[i] /= weightSum;
		}

		curvePoints.push_back(point);

		t += step;
	}
}

void convertIfcBSplineCurve(
	const std::shared_ptr<IfcBSplineCurve<Common>>& splineCurve,
	const std::vector<std::array<double, 3>>& controlPoints,
	std::vector<std::array<double, 3>>& loops)
{
	const int degree = splineCurve->Degree;
	const int order = degree + 1;
	const int numControlPoints = 2;
	const int numKnots = order + numControlPoints;

	std::vector<double> knots;
	knots.reserve(numKnots);

	std::vector<double> weights;

	std::shared_ptr<IfcBSplineCurveWithKnots<Common>> bspline =
		std::dynamic_pointer_cast<IfcBSplineCurveWithKnots<Common>>(splineCurve);

	if (bspline)
	{
		auto& knotMults = bspline->KnotMultiplicities;
		const std::vector<std::shared_ptr<IfcParameterValue<Common>>>& splineKnots = bspline->Knots;
		//const std::vector<std::shared_ptr<emt::Ifc4EntityTypes::IfcCartesianPoint>>& splinePoints = bspline->m_ControlPointsList;

		if (knotMults.size() != splineKnots.size())
		{
			std::cout << "ERROR: knot multiplicity does not correspond number of knots" << std::endl;
			return;
		}

		// obtain knots
		for (int i = 0; i < splineKnots.size(); ++i)
		{
			double knot = splineKnots[i]->m_value;
			int knotMult = knotMults[i];
			// look at the multiplicity of the current knot
			for (int j = 0; j < knotMult; ++j)
			{
				knots.push_back(knot);
			}
		}

		//! TEMPORARY default number of curve points
		const uint8_t numCurvePoints = numKnots * 10;
		std::vector<std::array<double, 3>> curvePoints;
		curvePoints.reserve(numCurvePoints);

		computeBSplineCurve(order, numCurvePoints, numControlPoints, controlPoints, weights, knots, curvePoints);

		loops.insert(loops.end(), curvePoints.begin(), curvePoints.end());
	}
}

void convertIfcCartesianPointVector(
	const std::vector<std::shared_ptr<IfcCartesianPoint<Common>>>& points,
	std::vector<std::array<double, 3>>& loop)
{
	const double length_factor = 1.0;
	const unsigned int num_points = points.size();

	for (unsigned int i_point = 0; i_point < num_points; ++i_point) {
		const std::vector<std::shared_ptr<IfcLengthMeasure<Common>>>& coords =
			points[i_point]->m_Coordinates;

		if (coords.size() > 2) {
			double x = coords[0]->m_value * length_factor;
			double y = coords[1]->m_value * length_factor;
			double z = coords[2]->m_value * length_factor;

			loop.push_back({ x, y, z });
		}
		else if (coords.size() > 1) {

			double x = coords[0]->m_value * length_factor;
			double y = coords[1]->m_value * length_factor;

			loop.push_back({ x, y, 0.0 });
		}
		else {
			std::cout << "convertIfcCartesianPointVector: ifc_pt->m_Coordinates.size() != 2"
				<< std::endl;
		}
	}
}

void convertIfcCurve(std::shared_ptr<IfcBSplineCurve<Common>> bspline_curve,
	std::vector<std::array<double, 3>>& targetVec) {
	std::vector<std::shared_ptr<IfcCartesianPoint<Common>>> &points = std::vector<std::shared_ptr<IfcCartesianPoint<Common>>>();

	points.push_back(std::make_shared<IfcCartesianPoint<Common>>(bspline_curve->ControlPointsList[0]));
	points.push_back(std::make_shared<IfcCartesianPoint<Common>>(bspline_curve->ControlPointsList[1]));

	std::vector<std::array<double, 3>> splinePoints;
	splinePoints.reserve(points.size());
	convertIfcCartesianPointVector(points, splinePoints);

	convertIfcBSplineCurve(bspline_curve, splinePoints, targetVec);
	return;
}




int main() {

	// Construct ifc1 curve.
	IfcBSplineCurve<IFC_1> ifc1Curve;
	ifc1Curve.Degree = 2;
	ifc1Curve.ClosedCurve = false;

	// Construct Common curve and initialize it with the ifc1curve.
	//IfcBSplineCurve<Common> curve;
	//curve = ifc1Curve;

	std::shared_ptr<IfcBSplineCurve<Common>> curve_ptr = std::make_shared<IfcBSplineCurve<Common>>();
	*curve_ptr = ifc1Curve;

	// Initialize targetVec.
	std::vector<std::array<double, 3>> targetVec;

	convertIfcCurve(curve_ptr, targetVec);

	IfcBSplineCurve<IFC_1> ifc1;

	ifc1.ClosedCurve = false;
	ifc1.Degree = 500;
	ifc1.SelfIntersect = false;

	IfcBSplineCurve<IFC_2> ifc2;
	ifc2.Degree = 1337;

	//ifc2 = ifc1;  // Error

	IfcBSplineCurve<IFC_3> ifc3;
	ifc3.Degree = 42;

	IfcBSplineCurve<Common> superset;

	superset = ifc1;
	superset = ifc3;
	superset = ifc2;
	superset = ifc1;
	superset = ifc3;
	superset = ifc2;

	// IFC1 IfcBSpline is type of int
	int y = ifc1.Degree;

	//ifcinteger num = ifc1.Degree;		// Does not work.
	//int num = ifc3.Degree;			// Does not work

	// SuperSet works for both types - because union of Degree is int and ifcinteger
	// No need to explicit check, compiler does it for you.
	ifcinteger k = superset.Degree;
	ifclogical b = superset.SelfIntersect;
	int x = superset.Degree;

	variant<double, int> var;
	var = 52.1;
	ifcinteger intvar = var;

	return 0;
}