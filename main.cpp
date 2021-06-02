#include "Https.hpp"
#include "FileWriter.hpp"
#include "Parse.hpp"
#include <iostream>

#define stdout(msg) std::cout << msg;

int main()
{
	try
	{
		auto host = "lk.pnzgu.ru";
		auto target = "/phone";

		stdout("data retrieval...\n");
		auto data = https::Https::get(host, target);

		stdout("parsing data...\n");
		auto prsns = prs::Parse::parsing(data);

		stdout("writing to file...\n");
		fw::FileWriter::write("data", prsns);

		stdout("Count persons: ");
		std::cout << prsns.size() << "\n\n";

	} catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return 0;
}