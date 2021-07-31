#pragma once
#include <functional>

struct TypeReflection
{
	size_t SizeInBytes;

	TypeReflection(const char* name, size_t size)
	{
		TypeName = name;
		SizeInBytes = size;
		HashedName = std::hash<std::string>{}(name);
	}

	void SetTypeName(const char* name)
	{
		TypeName = name;
		HashedName = std::hash<std::string>{}(name);
	}
	const char* GetTypeName() const { return TypeName; }
	bool IsOfType(const char* typeName) const { return *typeName == *TypeName; }
	size_t GetTypeHash() const { return HashedName; }
	size_t& GetTypeHashRef() { return HashedName; }

protected:
	const char* TypeName;
	size_t HashedName;
};