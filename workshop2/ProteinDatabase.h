//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/01/28
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#ifndef SDDS_PROTEINDATABASE_H
#define SDDS_PROTEINDATABASE_H
#include<iostream>
#include<string>
namespace sdds
{
		class ProteinDatabase
		{
			std::string* proteinSequences{};
			size_t nProteinSequences{};
		public:
			ProteinDatabase();
			ProteinDatabase(const char* fileName);
			ProteinDatabase(const ProteinDatabase& proteinDatabase);
			ProteinDatabase& operator=(const ProteinDatabase& proteinDatabase);
			ProteinDatabase(ProteinDatabase&& proteinDatabase) noexcept;
			ProteinDatabase& operator=(ProteinDatabase&& proteinDatabase) noexcept;
			size_t size();
			std::string operator[](size_t);
			~ProteinDatabase();
		};
}

#endif