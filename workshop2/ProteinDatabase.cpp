//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/01/28
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#include<fstream>
#include<algorithm>
#include"ProteinDatabase.h"

using namespace std;

namespace sdds
{
	ProteinDatabase::ProteinDatabase()
	{
	}
	ProteinDatabase::ProteinDatabase(const char* fileName)
	{
		ifstream inFile(fileName);
		string helperString{};
		
		if (inFile.is_open())
		{
			while (inFile)
			{
				if (inFile.get() == '>')
				{
					nProteinSequences++;
				}
			}
		}
		inFile.clear();
		proteinSequences = new string[nProteinSequences];

     	inFile.seekg(0);
		size_t i = 0;

		if (inFile.is_open())
		{
			while (inFile)
			{
				inFile.ignore(200, '\n');
				getline(inFile, helperString, '>');
				if (i < nProteinSequences)
				{
					auto newLinesRemoved = remove(helperString.begin(), helperString.end(), '\n');
					helperString.erase(newLinesRemoved, helperString.end());
					proteinSequences[i] = helperString;
				}
				i++;
			}
		}
	
		inFile.close();
	}

	ProteinDatabase::ProteinDatabase(const ProteinDatabase& proteinDatabase)
	{
		*this = proteinDatabase;
	}

	ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& proteinDatabase)
	{
		if (this != &proteinDatabase)
		{
			nProteinSequences = proteinDatabase.nProteinSequences;

			delete[] proteinSequences;
			proteinSequences = nullptr;
			if (proteinDatabase.proteinSequences)
			{
				proteinSequences = new string[nProteinSequences];
				for (size_t i = 0; i < nProteinSequences; i++)
				{
					proteinSequences[i] = proteinDatabase.proteinSequences[i];
				}
			}
		}
		return *this;
	}

	ProteinDatabase::ProteinDatabase(ProteinDatabase&& proteinDatabase) noexcept
	{
		*this = std::move(proteinDatabase);
	}


	ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& proteinDatabase) noexcept
	{
		if (this != &proteinDatabase)
		{
			delete[] proteinSequences;
			proteinSequences = proteinDatabase.proteinSequences;
			proteinDatabase.proteinSequences = nullptr;
			nProteinSequences = proteinDatabase.nProteinSequences;
			proteinDatabase.nProteinSequences = 0;
			
		}
		return *this;
	}

	size_t ProteinDatabase::size()
	{
		return nProteinSequences;
	}

	std::string ProteinDatabase::operator[](size_t index)
	{
		if (index < nProteinSequences)
		{
			return proteinSequences[index];
		}
		return "";
	}

	ProteinDatabase::~ProteinDatabase()
	{
		delete[] proteinSequences;
	}
}
