#include "JSON.h"

namespace neu::json
{
	bool Load(const std::string& filename, rapidjson::Document& document)
	{
		// !! create a std::ifstream object called stream 
		// !! check if it is open, if not use LOG to print error and return false 
		// !! https://riptutorial.com/cplusplus/example/1625/opening-a-file 

		rapidjson::IStreamWrapper istream(stream);
		document.ParseStream(istream);
		if (document.IsObject() == false)
		{
			LOG("json file cannot be read %s.", filename.c_str());
			return false;
		}

		return true;
	}

	bool Get(const rapidjson::Value& value, const std::string& name, int& data)
	{
		// check if 'name' member exists and is of type 

		if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsInt() ==
			false)
		{
			LOG("error reading json data %s", name.c_str());
			return false;
		}

		// set data 
		data = value[name.c_str()].GetInt();

		return true;
	}
}