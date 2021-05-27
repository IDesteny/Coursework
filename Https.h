#pragma once
#include <string>

namespace https
{
	class HttpsHelper
	{
	public:
		static std::string __fastcall get(const char *, const char *);
	};
}