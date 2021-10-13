// Mega

#pragma once

#ifndef JSON_UTIL_H
#define JSON_UTIL_H

#include <rapidjson\document.h>
#include <string>
#include <vector>

using rapidjson::Document;
using rapidjson::Value;
using std::string;
using std::vector;

namespace json
{
	bool Open( const string &file, Document &doc );
	
	bool						GetBool			( const Value &v, const string &name );
	float						GetFloat		( const Value &v, const string &name );
	int							GetInt			( const Value &v, const string &name );
	string						GetString		( const Value &v, const string &name );
	const Value &				GetValue		( const Value &v, const string &name );
	
	vector<float>				GetFloatVector	( const Value &v, const string &name );
	vector<int>					GetIntVector	( const Value &v, const string &name );
	vector<string>				GetStringVector	( const Value &v, const string &name );
	vector<const Value * const>	GetValueVector	( const Value &v, const string &name );
}

#endif	/* JSON_UTIL_H */