// Name: Ashwin Anand
// Seneca Student ID: 152042206
// Seneca email: aanand24@myseneca.ca
// Date of completion: 06-04-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include<iostream>
#include<deque>
#include"CustomerOrder.h"
#include"Station.h"


namespace sdds
{
	extern std::deque<sdds::CustomerOrder> g_pending;
	extern std::deque<sdds::CustomerOrder> g_completed;

	extern std::deque<sdds::CustomerOrder> g_incomplete;


	class Workstation : public Station
	{
		std::deque<CustomerOrder> m_orders{}; // orders that are currently present in the station to get processed; order gets entered through the back(push) and exit through the front(pop) 
		Workstation* m_pNextStation{}; // pointer to next workstation
	public:
		Workstation(){ }
		Workstation(const Workstation& ws) = delete;
		Workstation& operator=(const Workstation& ws) = delete;
		Workstation(Workstation&& ws) = delete;
		Workstation& operator=(Workstation&& ws) = delete;
		Workstation(const std::string& row) : Station(row){ }
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}
#endif // !SDDS_WORKSTATION_H
