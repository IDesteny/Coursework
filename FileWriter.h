#pragma once
#include <vector>
#include "Person.h"

namespace fw
{
	class FileWriter
	{
	public:
		static void __fastcall write(const char *const, const std::vector<Person> &);
	};
}