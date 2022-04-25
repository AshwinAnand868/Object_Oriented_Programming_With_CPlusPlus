//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/02/27
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_PROCESSOR_H
#define SDDS_PROCESSOR_H

#include<iostream>
#include<string>
#include<functional>
#include"CentralUnit.h"
#include"Job.h"
namespace sdds
{
	class Processor
	{
		CentralUnit<Processor>* hostingUnit{};
		std::string m_brand{};
		std::string m_code{};
		int m_power{};
		Job* m_current{}; 
		void (*afterJobFinishes) (CentralUnit<Processor>& cU, Processor* processor){};
		std::function<void(Processor*)> runWhenError{};

	public:
		Processor(){ }
		Processor(CentralUnit<Processor>* cU, std::string brand, std::string code, int power);
		void run();
		void operator()();
		explicit operator bool() const;
		Processor& operator+=(Job*&);
		Job* get_current_job()const;
		void on_complete(void (*jobIsDone) (CentralUnit<Processor>& cU, Processor* processor));
		void on_error(std::function<void(Processor*)> errorCatched);
		Job* free();
		friend std::ostream& operator<<(std::ostream&, const Processor&);
	};
}

#endif