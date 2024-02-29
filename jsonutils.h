#pragma once
#include <string>
#include <rapidjson/document.h>
#include <iostream>

namespace jsonutils
{

	std::string	valueToTree(const rapidjson::Value& value, int indent = 0);

	/* Expects T to have a constructor that takes in a Value */
	template <typename T> inline T parse(const std::string json)
	{
		// Template functions must be defined in the header file.
		// Use inline to avoid multiple definition errors when including this header in multiple files.

		rapidjson::Document doc;
		doc.Parse(json.c_str());
		return T(doc);
	}

	/* Objects implementing this class are able to be converted to JSON. */
	class Stringifiable
	{
	public:
		std::string stringify() const; // Const at the end of a function declaration means that the function will not modify the object it is called on.
		rapidjson::Value toValue(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>* allocator) const;

	protected:
		virtual void writeToObject(rapidjson::Value& node, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>* allocator) const = 0;
		// = 0 means this is a pure virtual function (abstract function), and the class is abstract.
	};

}