#pragma once
#include <string>

namespace https
{
	class Https
	{
	public:
		static std::string get(const char *const, const char *const);
	};
}