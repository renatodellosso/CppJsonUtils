#pragma once
#include <string>

namespace JsonUtils
{
	/* Objects implementing this class are able to be converted to JSON. */
	class Stringifiable
	{
	public:
		// Const at the end of a function declaration means that the function will not modify the object it is called on.
		std::string stringify() const;
	protected:
		virtual void writeToDocument(rapidjson::Document& doc) const = 0; // = 0 means this is a pure virtual function (abstract function), and the class is abstract.
	};
}