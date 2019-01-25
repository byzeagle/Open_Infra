#ifndef CUSTOMGENERATOR_H
#define CUSTOMGENERATOR_H

#include <iostream>
#include <string>
#include "boost/algorithm/string/replace.hpp"
#include "OpenInfraPlatform/ExpressBinding/Meta/Schema.h"

using namespace std;
using namespace OpenInfraPlatform::ExpressBinding;

class CustomGenerator
{
	public:
		CustomGenerator(const string &);
		void generate(std::ostream & out, Schema & schema);

	private:
		void createEntityClasses();
		Schema schema;
};

#endif
