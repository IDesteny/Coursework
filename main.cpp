#include "Https.hpp"
#include "FileWriter.hpp"
#include "Parse.hpp"
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

		std::cout << "Count persons: ";
		std::cout << prsns.size() << "\n\n";

	} catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return 0;
}