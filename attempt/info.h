#ifndef INFO_H
#define INFO_H

#include <unordered_map>

using std::unordered_map;

enum Version : int 
{
	IFC_1, 
	IFC_2, 
	IFC_3, 
	Common
};


//Collison of namespaces
enum Types : int
{
	ifcintegerx,
	ifclogicalx
};

using info_t = unordered_map<Version, unordered_map<Types, bool>>;
using abcd = unordered_map<Types, bool>;

#endif