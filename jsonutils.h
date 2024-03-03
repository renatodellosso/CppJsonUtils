#pragma once
#include <functional>
#include <string>
#include <rapidjson/document.h>
#include <iostream>

namespace jsonutils
{

	std::string	valueToTree(const rapidjson::Value& value, int indent = 0);

	template <typename T, int Size> std::array<T, Size> toArray(const rapidjson::GenericArray<false, rapidjson::Value> value, std::function<T(rapidjson::Value&)> converter)
	{
		std::array<T, Size> result;
		for (rapidjson::SizeType i = 0; i < value.Size(); i++)
		{
			rapidjson::Value* child = &value[i];
			result[i] = converter(*child);
		}
		return result;
	}

	template <typename T, int Size> rapidjson::Value toValue(const std::array<T, Size>& array, rapidjson::MemoryPoolAllocator<>* allocator, std::function<rapidjson::Value(T)> converter)
	{
		rapidjson::Value node(rapidjson::kArrayType);

		for (T value : array)
		{
			node.PushBack(&converter(value), allocator);
		}

		return node;
	}

	/*template <typename T> std::vector<T> toVector(const rapidjson::GenericArray<false, rapidjson::Value> value, std::function<T(rapidjson::Value&)> converter)
	{
		std::vector<T> result;
		for (rapidjson::SizeType i = 0; i < value.Size(); i++)
		{
			rapidjson::Value* child = &value[i];
			result.push_back(converter(*child));
		}
		return result;
	}*/

	/* Expects T to have a constructor that takes in a Value */
	template <typename T> T parse(const std::string json)
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
		rapidjson::Value toValue(rapidjson::MemoryPoolAllocator<>* allocator) const;

	protected:
		virtual void writeToObject(rapidjson::Value& node, rapidjson::MemoryPoolAllocator<>* allocator) const = 0;
		// = 0 means this is a pure virtual function (abstract function), and the class is abstract.
	};

}