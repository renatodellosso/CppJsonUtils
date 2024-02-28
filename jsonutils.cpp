#include "jsonutils.h"
#include "pch.h"
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace jsonutils
{

	ObjDocument::ObjDocument()
	{
		SetObject();
	}

	ObjDocument::ObjDocument(const std::string& json) : ObjDocument() // Call the default constructor.
	{
		Parse(json.c_str());
	}

	int ObjDocument::getInt(const std::string& key, int ifMissing) const
	{
		return HasMember(key.c_str()) ? (*this)[key.c_str()].GetInt() : ifMissing;
	}

	float ObjDocument::getFloat(const std::string& key, float ifMissing) const
	{
		return HasMember(key.c_str()) ? (*this)[key.c_str()].GetFloat() : ifMissing;
	}

	double ObjDocument::getDouble(const std::string& key, double ifMissing) const
	{
		return HasMember(key.c_str()) ? (*this)[key.c_str()].GetDouble() : ifMissing;
	}

	bool ObjDocument::getBool(const std::string& key, bool ifMissing) const
	{
		return HasMember(key.c_str()) ? (*this)[key.c_str()].GetBool() : ifMissing;
	}

	std::string ObjDocument::getString(const std::string& key, const std::string& ifMissing) const
	{
		return HasMember(key.c_str()) ? (*this)[key.c_str()].GetString() : ifMissing;
	}

	std::string Stringifiable::stringify() const
	{
		ObjDocument doc;
		writeToDocument(doc);

		// Set up a string buffer to write the JSON to.
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		return buffer.GetString();
	}

}