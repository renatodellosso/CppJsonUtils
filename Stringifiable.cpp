#include "Stringifiable.h"
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace JsonUtils
{
	std::string Stringifiable::stringify() const
	{
		rapidjson::Document doc;
		writeToDocument(doc);

		// Set up a string buffer to write the JSON to.
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		return buffer.GetString();
	}
}