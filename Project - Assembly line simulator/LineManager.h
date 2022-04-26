// Name: Ashwin Anand
// Seneca Student ID: 152042206
// Seneca email: aanand24@myseneca.ca
// Date of completion: 06-04-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include<fstream>
#include<vector>
#include<algorithm>
#include"Workstation.h"

namespace sdds
{
	class LineManager
	{
			std::vector<Workstation*> m_activeLine{}; // the workstations that are present on the assembly line
			size_t m_cntCustomerOrder{}; // counter of how many orders
			Workstation* m_firstStation{}; // pointer to the first active station
		public:
			LineManager(){ }
			LineManager(const std::string& file, const std::vector<Workstation*>& stations);
			void reorderStations();
			bool run(std::ostream& os);
			void display(std::ostream& os)const;
	};
}
#endif // !SDDS_LINEMANAGER_H
