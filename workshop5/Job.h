//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/02/27
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_JOB_H
#define SDDS_JOB_H

#include<iostream>
#include<string>
#include<exception>

namespace sdds
{
	class Job
	{
		std::string jobTitle{}; 
		unsigned int unitsOfWork{};
		unsigned int remUnitOfWork{}; 
		bool isActive{false};

	public:
		Job(){}
		Job(std::string title);
		bool is_active();
		bool is_complete();
		std::string name();
		void display(std::ostream& ostr);
		void operator()(unsigned int uWork);
	};
	std::ostream& operator<<(std::ostream& ostr, Job& job);
}
#endif // !SDDS_JOB_H
