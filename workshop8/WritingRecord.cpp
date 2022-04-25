//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/03/27
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#include "GeneratingList.h"
#include "EmpProfile.h"
#include "WritingRecord.h"
#include <utility>

using namespace std;

namespace sdds {
	GeneratingList<EmployeeWage> writeRaw(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal) {
		GeneratingList<EmployeeWage> activeEmp;
		
		bool notFound{};
		// TODO: Add your code here to build a list of employees
		//         using raw pointers
		for (size_t i = 0; i < emp.size(); i++)
		{
			notFound = true;
			
				for (size_t j = 0; j < sal.size() && notFound; j++)
				{
				
					if (emp[i].id == sal[j].id)
					{
						notFound = false;
						EmployeeWage* empWage = new EmployeeWage(emp[i].name, sal[j].salary);

						try
						{
							empWage->rangeValidator();
						}
						catch (const std::string&)
						{
							delete empWage;
							throw std::string("*** Employees salaray range is not valid");
						};
						if (activeEmp.SINValidator(emp[i].id))
							activeEmp += empWage;
						else
							throw std::string("SIN not valid");
						delete empWage; 
					}
				}
		}
		return activeEmp;
	}

	GeneratingList<EmployeeWage> writeSmart(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal)
	{
		GeneratingList<EmployeeWage> activeEmp;
		bool notFound{};
		// TODO: Add your code here to build a list of employees
		//         using smart pointers
		for (size_t i = 0; i < emp.size(); i++)
		{
			notFound = true;

			for (size_t j = 0; j < sal.size() && notFound; j++)
			{

				if (emp[i].id == sal[j].id)
				{
					notFound = false;
					std::unique_ptr<EmployeeWage> empWage(new EmployeeWage(emp[i].name, sal[j].salary));

					try
					{
						empWage->rangeValidator();
					}
					catch (const std::string&)
					{
						throw std::string("*** Employees salaray range is not valid");
					};
					if (activeEmp.SINValidator(emp[i].id))
						activeEmp += std::move(empWage);
					else
						throw std::string("SIN not valid");
				}
			}
		}
		return activeEmp;
	}
}