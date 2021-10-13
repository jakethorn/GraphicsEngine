#include "JsonUtil.h"

#include <limits>

#include "DebugConsole.h"
#include "File.h"

////////////////////
// open file

bool json::Open( const string &file, Document &doc )
{
	string text{ file::Read( file ) };

	bool success{ !text.empty() };

	if ( success )
	{
		doc.Parse( text.c_str() );
		success = doc.IsObject();
	}

	console::Print( success, "Parse Json file: " + file );
	return success;
}

////////////////////
// get bool

bool json::GetBool(const Value & v, const string & name)
{
	return v.HasMember(name.c_str()) ? v[name.c_str()].GetBool() : false;
}

////////////////////
// get int

int	json::GetInt(const Value & v, const string & name)
{
	return v.HasMember(name.c_str()) ? v[name.c_str()].GetInt() : 0xD15EA5E;
}

////////////////////
// get float

float json::GetFloat(const Value & v, const string & name)
{
	return v.HasMember(name.c_str()) ? v[name.c_str()].GetDouble() : std::numeric_limits<float>::quiet_NaN();
}

////////////////////
// get string

string json::GetString(const Value & v, const string & name)
{
	return v.HasMember(name.c_str()) ? v[name.c_str()].GetString() : "";
}

////////////////////
// get value

const Value & json::GetValue(const Value & v, const string & name)
{
	return v.HasMember(name.c_str()) ? v[name.c_str()] : v;
}

////////////////////
// get int vector

vector<int> json::GetIntVector(const Value & v, const string & name)
{
	vector<int> retval;

	if (v.HasMember(name.c_str()))
		for (unsigned int i = 0; i < v[name.c_str()].Size(); ++i)
			retval.push_back(v[name.c_str()][i].GetInt());

	return retval;
}

////////////////////
// get float vector

vector<float> json::GetFloatVector(const Value & v, const string & name)
{
	vector<float> retval;

	if (v.HasMember(name.c_str()))
		for (unsigned int i = 0; i < v[name.c_str()].Size(); ++i)
			retval.push_back(v[name.c_str()][i].GetDouble());

	return retval;
}

////////////////////
// get string vector

vector<string> json::GetStringVector(const Value & v, const string & name)
{
	vector<string> retval;

	if (v.HasMember(name.c_str()))
		for (unsigned int i = 0; i < v[name.c_str()].Size(); ++i)
			retval.push_back(v[name.c_str()][i].GetString());

	return retval;
}

////////////////////
// get value vector

vector<const Value * const> json::GetValueVector(const Value & v, const string & name)
{
	vector<const Value * const> retval;

	if (v.HasMember(name.c_str()))
		for (unsigned int i = 0; i < v[name.c_str()].Size(); ++i)
			retval.push_back(&(v[name.c_str()][i]));

	return retval;
}