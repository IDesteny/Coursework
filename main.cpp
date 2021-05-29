﻿#include "Https.h"
#include "FileWriter.h"
#include "Parse.h"
#include <iostream>

int main()
{
	try
	{
		const char *const host = "lk.pnzgu.ru";
		const char *const target = "/phone";

		std::cout << "data retrieval...\n";
		const auto &&data = https::Https::get(host, target);

		std::cout << "parsing data...\n";
		const auto &&prsns = prs::Parse::parsing(data);

		std::cout << "writing to file...\n";
		fw::FileWriter::write("data", prsns);

		std::cout << "Count persons: " << prsns.size() << "\n\n";
	} catch (const std::exception &ex)
	{
		std::cout << ex.what();
	}
	return 0;
}