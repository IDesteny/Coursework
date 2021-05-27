#include "Https.h"
#include "Person.h"
#include "FileWriter.h"
#include "Parse.h"
#include <vector>
#include <iostream>

int main()
{
	std::cout << "Start\n";
	std::cout << "==================\n\n";

	//get data
	std::cout << "data retrieval...\n";
	auto &&data = https::HttpsHelper::get("lk.pnzgu.ru", "/phone");

	//parsing
	std::cout << "parsing data...\n";
	auto &&prsns = prs::Parse::parsing(data);

	//output data
	std::cout << "writing to file...\n";
	fw::FileWriter::write("data", prsns);
	
	std::cout << "\n==================\n";
	std::cout << "End\n\n";
	
	//output info
	std::cout << "Count persons: " << prsns.size() << "\n\n";

	return 0;
}