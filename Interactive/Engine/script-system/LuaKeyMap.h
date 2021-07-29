#pragma once
#include <map>
#include <string>

class LuaKeyMap
{
public:
	inline static std::map<std::string, Keys> Keys = {
		{"W", Keys::W},
		{"F", Keys::F}
	};
};
