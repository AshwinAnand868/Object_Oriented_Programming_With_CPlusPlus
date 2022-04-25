//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/03/27
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#ifndef SDDS_WRITINGRECORD_H
#define SDDS_WRITINGRECORD_H

#include "GeneratingList.h"
#include "EmpProfile.h"

namespace sdds
{
	GeneratingList<EmployeeWage> writeRaw(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal);
	GeneratingList<EmployeeWage> writeSmart(const GeneratingList<Employee>& emp, const GeneratingList<Salary>& sal);
}


#endif // SDDS_WRITINGRECORD_H
