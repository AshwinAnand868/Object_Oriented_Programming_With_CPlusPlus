//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/03/12
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

#include<iostream>
#include<fstream>
#include<string>
#include<utility>
#include"Directory.h"
#include"File.h"

namespace sdds
{
	class Filesystem
	{
		Directory* m_root{};
		Directory* m_current{};
	public:
		Filesystem(std::string fileName, std::string rootName = "");
		Filesystem(const Filesystem& filesystem) = delete;
		Filesystem& operator=(const Filesystem& filesystem) = delete;
		Filesystem(Filesystem&& filesystem)noexcept;
		Filesystem& operator=(Filesystem&& filesystem)noexcept;
		Filesystem& operator+=(Resource* resource);
		Directory* change_directory(const std::string& dir_name = "");
		Directory* get_current_directory();
		~Filesystem();
	};
}





#endif // !SDDS_FILESYSTEM_H

