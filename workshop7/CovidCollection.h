//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/03/17
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<numeric>
#include<list>
namespace sdds
{
	struct Covid
	{
		std::string country{}, city{}, variant{};
		size_t year{}, nCases{}, m_deaths{};
	};

	class CovidCollection
	{
		std::vector<Covid> covidCollection{};
	public:
		CovidCollection()
		{
		}

		CovidCollection(std::string fileName);
		void display(std::ostream& out);
		void sort(std::string orderBy);
		void cleanList();
		bool inCollection(std::string variant) const;
		std::list<Covid> getListForVariant(std::string variant) const;
	};
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
}

#endif // !SDDS_COVIDCOLLECTION_H

