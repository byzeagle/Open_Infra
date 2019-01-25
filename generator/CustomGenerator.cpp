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
		"{{FIELD}}"
		"};\n"
	);

	string TemplateInheritance("template <>\n"
		"struct {{ENTITY_NAME}}<{{VERSION}}> : public {{SUPERTYPE}}<{{VERSION}}>\n"
		"{\n"
		"{{FIELD}}"
		"};\n"
	);

	// For each entitiy
	for (int i = 0; i < schema.getEntityCount(); ++i)
	{
		const Entity & entity = schema.getEntityByIndex(i);
		string tempTemplate = "";

		if (!entity.hasSupertype())
			tempTemplate = Template;
		else
			tempTemplate = TemplateInheritance;

		string tempDummyTemplate = dummy_template;
		string field = "";

		// For each attribute of entities
		for (int k = 0; k < entity.getAttributeCount(); ++k)
		{
			const EntityAttribute & attribute = entity.getAttribute(k);
			field += "\t" + (attribute.type)->toString() + " " + attribute.getName() + ";\n";
		}

		// Replacement of 
		boost::replace_all(tempDummyTemplate, "{{ENTITY_NAME}}", entity.getName());
		boost::replace_all(tempTemplate, "{{ENTITY_NAME}}", entity.getName());
		boost::replace_all(tempTemplate, "{{SUPERTYPE}}", entity.getSupertype());
		boost::replace_all(tempTemplate, "{{VERSION}}", schema.name_);
		boost::replace_all(tempTemplate, "{{FIELD}}", field);

		cout << "-------------------------" << endl;
		cout << tempDummyTemplate << endl << endl;
		cout << endl;
		cout << tempTemplate << endl;
	}
}

