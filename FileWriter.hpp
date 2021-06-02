#pragma once
#include <vector>
#include "Person.hpp"

namespace fw
{
	class FileWriter
	{
	public:
		static void write(const char *const, const std::vector<Person> &);
	};
}