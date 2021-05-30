#pragma once
#include <string>

namespace https
{
	class Https
	{
	public:
		static std::string __fastcall get(const char *const, const char *const);
	};
}