#include "FileWriter.hpp"
#include <fstream>
#include <direct.h>

void fw::FileWriter::write(const char *const name, const std::vector<Person> &prsns)
{
	if (prsns.empty())
		throw std::exception("fileWriter: There is no data");

	if (_mkdir(name) == -1 && errno == EINVAL)
		throw std::exception("fileWriter: Failed to create folder");

	std::ofstream f;
	const auto &&dirname = std::string(name) + '/';

	for (int i = 0; i < prsns.size(); ++i)
	{
		f.open(dirname + std::to_string(i) + ".txt");

		f << "name:\t\t" << prsns[i].name << '\n';
		f << "position:\t" << prsns[i].position << '\n';
		f << "subdivision:\t" << prsns[i].subdivision << '\n';
		f << "audience:\t" << prsns[i].audience << '\n';
		f << "phone:\t\t" << prsns[i].phone << '\n';
		f << "link:\t\t" << prsns[i].link << '\n';
	
		f.close();
	}
}