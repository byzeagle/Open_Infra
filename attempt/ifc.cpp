#include <string>
#include <iostream>
#include "IfcBSplineCurve.hpp"
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

int main()
{
	IfcBSplineCurve<IFC_1> ifc1;

	ifc1.ClosedCurve = false;
	ifc1.Degree = 500;
	ifc1.SelfIntersect = false;

	IfcBSplineCurve<IFC_2> ifc2;

	//ifc2 = ifc1;  // Error

	IfcBSplineCurve<IFC_3> ifc3;

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

	cout << "Superset Version : " << display(superset.version) << endl;
	cout << "Value of x is : " << x << endl;
	cout << "Value of k is : " << k << endl;
	cout << "Value of b is : " << b << endl;

	system("PAUSE");

	return 0;
}