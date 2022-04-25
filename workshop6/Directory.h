//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/03/12
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

#include<iostream>
#include<vector>
#include"Resource.h"
#include"File.h"

namespace sdds
{
	class Directory : public Resource
	{
		std::vector<Resource*> m_contents{};
	public:
		Directory(){ }
		Directory(std::string name);
		void update_parent_path(const std::string& parentPath);
		NodeType type()const;
		std::string path()const;
		std::string name() const;
		int count()const;
		size_t size() const;
		Directory& operator+=(Resource* resource);
		Resource* find(const std::string& name, const std::vector<OpFlags>& optionFlags = std::vector<OpFlags>());
		Directory(const Directory& directory) = delete;
		Directory(Directory&& directory) = delete;
		Directory& operator=(const Directory& directory) = delete;
		Directory& operator=(Directory&& directory) = delete;
		void display(std::ostream& ostr, const std::vector<FormatFlags>& formatFlags = std::vector<FormatFlags>()) const;
		~Directory();
		void remove(const std::string& name, const std::vector<OpFlags>& optionFlags= std::vector<OpFlags>());
	};
}

#endif