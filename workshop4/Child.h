//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/02/13
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_CHILD_H
#define SDDS_CHILD_H

#include<iostream>
#include<string>
#include"Toy.h"
namespace sdds
{
	class Child
	{
			std::string name{};
			int age{};
			const sdds::Toy** toys{};
			size_t toysCounter{};// just a reminder
		public:
			Child(){}
			Child(std::string   c_name, int c_age, const Toy* toy[], size_t count);
			Child(const Child& child);
			Child& operator=(const Child& child);
			Child(Child&& child) noexcept;
			Child& operator=(Child&& child) noexcept;
			~Child();
			size_t size() const;
			friend std::ostream& operator<<(std::ostream& ostr, const Child& child);
	};
}

#endif // !SDDS_CHILD_H
