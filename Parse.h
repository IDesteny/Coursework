#pragma once
#include <string>
#include <vector>
#include "Person.h"

namespace prs
{
	class Parse
	{
	public:
		static std::vector<Person> __fastcall parsing(const std::string &);
	};
}