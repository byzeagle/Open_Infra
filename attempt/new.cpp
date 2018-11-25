
namespace IFC1
{

	struct IfcCurve
	{

	};

	struct IfcCartesianPoint
	{

	};

	struct IfcBSplineCurveForm
	{

	};

	struct IfcBSplineCurve : public IfcCurve
	{
		int Degree;
		IfcCartesianPoint ControlPointsList[2];
		IfcBSplineCurveForm CurveForm;
		bool ClosedCurve;
		bool SelfIntersect;

		IfcBSplineCurve & operator = (const SuperSet::IfcBSplineCurve & obj)
		{
			Degree = get<int>(obj.Degree);
			//ControlPointsList = obj.ControlPointsList;
			//CurveForm = obj.CurveForm;
			ClosedCurve = get<bool>(obj.ClosedCurve);
			SelfIntersect = get<bool>(obj.SelfIntersect);
		}
	};
}

namespace IFC2
{
	struct IfcCurve
	{

	};

	struct IfcCartesianPoint
	{

	};

	struct IfcBSplineCurveForm
	{

	};

	struct IfcBSplineCurve : public IfcCurve
	{
		int Degree;
		IfcCartesianPoint ControlPointsList[2];
		IfcBSplineCurveForm CurveForm;
		bool ClosedCurve;
		bool SelfIntersect;

		IfcBSplineCurve & operator = (const SuperSet::IfcBSplineCurve & obj)
		{
			Degree = get<int>(obj.Degree);
			//ControlPointsList = obj.ControlPointsList;
			//CurveForm = obj.CurveForm;
			ClosedCurve = get<bool>(obj.ClosedCurve);
			SelfIntersect = get<bool>(obj.SelfIntersect);
		}
	};
}

namespace IFC3
{

	struct ifclogical {};
	struct ifcinteger {};

	struct IfcCurve
	{

	};

	struct IfcCartesianPoint
	{

	};

	struct IfcBSplineCurveForm
	{

	};

	struct IfcBSplineCurve : public IfcCurve
	{
		ifcinteger Degree;
		IfcCartesianPoint ControlPointsList[2];
		IfcBSplineCurveForm CurveForm;
		ifclogical ClosedCurve;
		ifclogical SelfIntersect;

		IfcBSplineCurve & operator = (const SuperSet::IfcBSplineCurve & obj)
		{
			Degree = get<ifcinteger>(obj.Degree);
			//ControlPointsList = obj.ControlPointsList;
			//CurveForm = obj.CurveForm;
			ClosedCurve = get<ifclogical>(obj.ClosedCurve);
			SelfIntersect = get<ifclogical>(obj.SelfIntersect);
		}
	};
}

namespace SuperSet
{
	struct ifclogical {};
	struct ifcinteger {};

	struct IfcCurve
	{

	};

	struct IfcCartesianPoint
	{

	};

	struct IfcBSplineCurveForm
	{

	};

	struct IfcBSplineCurve : public IfcCurve
	{
		Version version;

		variant<int, ifcinteger> Degree;
		IfcCartesianPoint ControlPointsList[2];
		IfcBSplineCurveForm CurveForm;
		variant<bool, ifclogical> ClosedCurve;
		variant<bool, ifclogical> SelfIntersect;

		IfcBSplineCurve & operator = (const IFC1::IfcBSplineCurve & obj)
		{
			version = IFC_1;
			Degree = obj.Degree;
			//ControlPointsList = obj.ControlPointsList;
			//CurveForm = obj.CurveForm;
			ClosedCurve = obj.ClosedCurve;
			SelfIntersect = obj.SelfIntersect;
		}
	};
}

template <Version T>
void function(IfcBSplineCurve<T> obj)
{

}


// Each function to be handled differently
template<>
void function(IfcBSplineCurve<Common> obj)
{

}


// Each function to be handled differently
template<>
void function(IfcBSplineCurve<IFC_1> obj)
{

}


struct type_size_visitor : public boost::static_visitor<unsigned> {
	template <typename T>
	unsigned operator()(const T&) const { return sizeof(T); }
};

// Derived Variant to overload implicit conversion operators
template <typename ... Types>
struct variant : public boost::variant<Types...>
{
	using base_type = boost::variant<Types...>;
public:
	// inherit constructors
	using base_type::base_type;

	// add a new method
	unsigned type_size() { return boost::apply_visitor(type_size_visitor(), *this); }

	/* Inheriting operators from boost::variant does not
	   work as it normally would. We have to add explicit
	   overloads for the operators we want to use.
	*/

	bool operator == (const variant & rhs) const {
		// cast rhs to base and delegate to operator in base
		return base_type::operator==(static_cast<const base_type&>(rhs));
	}

	template <typename T>
	void operator() (const T & operand) const {
		// cast rhs to base and delegate to operator in base
		out_ << operand;
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