#include "CustomGenerator.h"

// String templates for generation of types are here.
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
	"}\n"
);

CustomGenerator::CustomGenerator(const string & str)
{

}

void CustomGenerator::generate(std::ostream & out, Schema & schema)
{
	this->schema = schema;
	createEntityClasses();
	//printEntityClasses();
	//createUnionTypes();
}

void CustomGenerator::printEntityClasses()
{
	for (const auto & pair : entityLookUp)
		for (const auto pair2 : pair.second)
			cout << pair2.second << endl;
}

void CustomGenerator::debug()
{
	for (const auto & pair : unionType)
	{
		cout << "____ENTITYNAME___ : " << pair.first << endl;
		for (const auto & pair2 : pair.second)
		{
			const string & fieldName = pair2.first;
			cout << "----field name ----" << endl;
			cout << fieldName << endl;
			cout << "-----types------" << endl;

			for (const auto & setElement : pair2.second)
				cout << setElement << endl;
		}
	}
}

void CustomGenerator::createUnionTypes()
{
	for (const auto & outerPair : unionType)
	{
		string tempTemplate = Template;
		string element = "";
		const string version = "Union";
		const string & Entity = outerPair.first;

		for (const auto & innerPair : outerPair.second)
		{
			const auto field = innerPair.first;
			if (innerPair.second.size() > 1)
			{
				element += "\tboost::variant<";
			}
			int i = 1;
			for (const auto & setElement : innerPair.second)
			{
				// Here use variant
				if (innerPair.second.size() > 1)
				{
					element += setElement + ", ";
					if (i++ == innerPair.second.size())
					{
						element += "> " + field + "\n";
					}
				}
				else // Here use nothing
				{
					element += '\t' + setElement + " " + field + ";\n";
				}
			}
		}

		boost::replace_all(tempTemplate, "{{ENTITY_NAME}}", Entity);
		boost::replace_all(tempTemplate, "{{FIELD}}", element);
		boost::replace_all(tempTemplate, "{{VERSION}}", version);
		cout << tempTemplate << endl;
	}
}

/*
	1-) Create .hpp file if not exist and add dummy node
	2-) Add schema specific info
	3-) Last one is union
*/
void CustomGenerator::createEntityClasses()
{
	set<string> lookup;

	// This is needed to know whether a field is an entity
	// If so, template parameter for specialization is to be provided
	for (int i = 0; i < schema.getEntityCount(); ++i)
		lookup.insert(schema.getEntityByIndex(i).getName());
	
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

			// Add for the union struct
			unionType[entity.getName()][name].insert(type);

			fieldop += "\t" + string("this->") + name + " = " + "obj." + name + ";\n";

			if (lookup.count(type) == 1)
				type += string("<") + "{{VERSION}}" + ">";
			
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

		// Store generated structs and assignment operators
		entityLookUp[schema.name_][entity.getName()] = tempTemplate;
		opLookUp[schema.name_][entity.getName()] = tempAssignOp;
	}
}

