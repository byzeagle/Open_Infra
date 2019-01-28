#include "CustomGenerator.h"

CustomGenerator::CustomGenerator(const string & str)
{

}

void CustomGenerator::generate(std::ostream & out, Schema & schema)
{
	this->schema = schema;
	createEntityClasses();
}


/*
	1-) Create .hpp file if not exist and add dummy node
	2-) Add schema specific info
	3-) Last one is union
*/
void CustomGenerator::createEntityClasses()
{
	string dummy_template("template<Version T>\n"
		"struct {{ENTITY_NAME}} { };\n"
	);

	string Template("template <>\n"
		"struct {{ENTITY_NAME}}<{{VERSION}}>\n"
		"{\n"
		"\tstatic constexpr Version version = {{VERSION}};\n"
		"{{FIELD}}\n"
		"\t{{ENTITY_NAME}}<{{VERSION}}> & operator= (const & {{ENTITY_NAME}}<Union>);\n"
		"};\n"
	);

	string TemplateInheritance("template <>\n"
		"struct {{ENTITY_NAME}}<{{VERSION}}> : public {{SUPERTYPE}}<{{VERSION}}>\n"
		"{\n"
		"\tstatic constexpr Version version = {{VERSION}};\n"
		"{{FIELD}}"
		"\t{{ENTITY_NAME}}<{{VERSION}}> & operator= (const {{ENTITY_NAME}}<Union> &);\n"
		"};\n"
	);

	string AssignOpTemplate("{{ENTITY_NAME}}<{{VERSION}}> & {{ENTITY_NAME}}<{{VERSION}}>::operator= (const {{ENTITY_NAME}}<Union> & obj)\n"
							"{\n"
							"{{FIELDOP}}"
							"}\n");

	map<string, int> lookup;

	// Fill up
	for (int i = 0; i < schema.getEntityCount(); ++i)
	{
		const Entity & entity = schema.getEntityByIndex(i);
		lookup[entity.getName()] = 1;
	}
	

	// For each entitiy
	for (int i = 0; i < schema.getEntityCount(); ++i)
	{
		const Entity & entity = schema.getEntityByIndex(i);
		string tempTemplate = "";
		string tempAssignOp = "";
		string field = "";
		string fieldop = "";

		if (!entity.hasSupertype())
			tempTemplate = Template;
		else
			tempTemplate = TemplateInheritance;

		string tempDummyTemplate = dummy_template;
		tempAssignOp = AssignOpTemplate;

		// For each attribute of entities
		for (int k = 0; k < entity.getAttributeCount(); ++k)
		{
			const EntityAttribute & attribute = entity.getAttribute(k);
			string name = attribute.getName();
			string type = (attribute.type)->toString();

			fieldop += "\t" + string("this->") + name + " = " + "obj." + name + ";\n";

			if (lookup.count(type) >= 1)
			{
				type += string("<") + "{{VERSION}}" + ">";
			}
			
			if(attribute.isOptional())
				field += "\t" + string("boost::optional<") + type + ">" + " " + name + ";\n";
			else
				field += "\t" + type + " " + name + ";\n";
		}

		// Replacement of 
		boost::replace_all(tempDummyTemplate, "{{ENTITY_NAME}}", entity.getName());

		boost::replace_all(tempAssignOp, "{{ENTITY_NAME}}", entity.getName());
		boost::replace_all(tempAssignOp, "{{FIELDOP}}", fieldop);
		boost::replace_all(tempAssignOp, "{{VERSION}}", schema.name_);


		boost::replace_all(tempTemplate, "{{ENTITY_NAME}}", entity.getName());
		boost::replace_all(tempTemplate, "{{SUPERTYPE}}", entity.getSupertype());
		boost::replace_all(tempTemplate, "{{FIELD}}", field);
		boost::replace_all(tempTemplate, "{{VERSION}}", schema.name_);

		cout << "-------------------------" << endl;
		cout << tempDummyTemplate << endl << endl;
		cout << endl;
		cout << tempTemplate << endl;
		cout << endl;
		cout << tempAssignOp << endl;
	}
}

