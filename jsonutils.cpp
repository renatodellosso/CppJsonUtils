#include "jsonutils.h"
#include "pch.h"
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace jsonutils
{

	std::string Stringifiable::stringify() const
	{
		rapidjson::Document doc;
		doc.SetObject();
		writeToObject(doc, &doc.GetAllocator());

		// Set up a string buffer to write the JSON to.
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		return buffer.GetString();
	}

	rapidjson::Value Stringifiable::toValue(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>* allocator) const
	{
		rapidjson::Value node;
		node.SetObject();
		writeToObject(node, allocator);
		return node;
	}

	std::string valueToTree(const rapidjson::Value& value, int indent)
	{
		std::string tree;
		std::string indentStr(indent, ' ');

		// If the value is an object, print its members.
		if (value.IsObject())
		{
			tree += "{\n";
			for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it)
			{
				tree += indentStr + "  " + it->name.GetString() + ": " + valueToTree(it->value, indent + 1) + "\n";
			}
			tree += indentStr + "}";
		}

		// If the value is an array, print its elements.
		else if (value.IsArray())
		{
			tree += "[\n";
			for (rapidjson::SizeType i = 0; i < value.Size(); i++)
			{
				tree += indentStr + "  " + valueToTree(value[i], indent + 1) + "\n";
			}
			tree += indentStr + "]";
		}

		// If the value is a string, print it.
		else if (value.IsString())
		{
			tree += "\"" + std::string(value.GetString(), value.GetStringLength()) + "\"";
		}

		// If the value is a number, print it.
		else if (value.IsNumber())
		{
			if (value.IsInt())
			{
				tree += std::to_string(value.GetInt());
			}
			else if (value.IsUint())
			{
				tree += std::to_string(value.GetUint());
			}
			else if (value.IsInt64())
			{
				tree += std::to_string(value.GetInt64());
			}
			else if (value.IsUint64())
			{
				tree += std::to_string(value.GetUint64());
			}
			else if (value.IsDouble())
			{
				tree += std::to_string(value.GetDouble());
			}
		}

		// If the value is a boolean, print it.
		else if (value.IsBool())
		{
			tree += value.GetBool() ? "true" : "false";
		}

		// If the value is null, print it.
		else if (value.IsNull())
		{
			tree += "null";
		}

		// If the value is something else, print it.
		else
		{
			tree += "???";
		}

		return tree;
	}

}