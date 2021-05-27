#include "Parse.h"
#include <boost/regex.hpp>

std::vector<Person> prs::Parse::parsing(const std::string &data)
{
	std::vector<Person> persons;

	const char * const rgxs[] {
		"<span style=\"display: none;\">(.*)</span>",
		"<a href=\"(.*?)\"",
		"<b>(.*)</b>",
		"<br/>(.*)<i",
		"(.*)",
		"(.*)"
	};

	//full information
	boost::regex rgx("<tbody>(.*?)</tbody>");
	boost::smatch res;
	boost::regex_search(data, res, rgx);

	auto &&data2 = res[1].str();

	//specific person
	boost::regex rgx2("<tr >(.*?)</tr>");
	boost::smatch res2;

	std::string::const_iterator &&cbegin = data2.cbegin();
	std::string::const_iterator &&cend = data2.cend();

	//fields person
	boost::regex rgx3("<td>(.*?)</td>");
	boost::smatch res3;

	std::string::const_iterator cbegin2;
	std::string::const_iterator cend2;

	//new person
	Person prsn;

	std::string dataField;

	//specific field data
	boost::smatch ress;

	while (boost::regex_search(cbegin, cend, res2, rgx2))
	{
		//data about him
		const auto &&data3 = res2[1].str();
		
		cbegin2 = data3.cbegin();
		cend2 = data3.cend();

		//Phone
		boost::regex_search(cbegin2, cend2, res3, rgx3);
		dataField = res3[1];
		boost::regex_search(dataField, ress, (boost::regex)rgxs[0]);
		if (!ress[1].str().empty()) prsn.phone = ress[1];
		cbegin2 = res3[1].second;


		//Link
		boost::regex_search(cbegin2, cend2, res3, rgx3);
		dataField = res3[1];
		boost::regex_search(dataField, ress, (boost::regex)rgxs[1]);
		if (!ress[1].str().empty()) prsn.link = ress[1];
		cbegin2 = res3[1].second;


		//Position
		boost::regex_search(cbegin2, cend2, res3, rgx3);
		dataField = res3[1];
		boost::regex_search(dataField, ress, (boost::regex)rgxs[2]);
		if (!ress[1].str().empty()) prsn.name = ress[1];
		boost::regex_search(dataField, ress, (boost::regex)rgxs[3]);
		if (!ress[1].str().empty()) prsn.position = ress[1];
		cbegin2 = res3[1].second;


		//Subdivision
		boost::regex_search(cbegin2, cend2, res3, rgx3);
		dataField = res3[1];
		boost::regex_search(dataField, ress, (boost::regex)rgxs[4]);
		if (!ress[1].str().empty()) prsn.subdivision = ress[1];
		cbegin2 = res3[1].second;


		//Audience
		boost::regex_search(cbegin2, cend2, res3, rgx3);
		dataField = res3[1];
		boost::regex_search(dataField, ress, (boost::regex)rgxs[5]);
		if (!ress[1].str().empty()) prsn.audience = ress[1];
		cbegin2 = res3[1].second;


		persons.push_back(std::move(prsn));
		cbegin = res2[1].second;
	}

	return persons;
}