// Name: Ashwin Anand
// Seneca Student ID: 152042206
// Seneca email: aanand24@myseneca.ca
// Date of completion: 06-04-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

namespace sdds
{
	std::deque<sdds::CustomerOrder> g_pending{}; 
	std::deque<sdds::CustomerOrder> g_completed{}; 

	std::deque<sdds::CustomerOrder> g_incomplete{};

	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os); 
		}
	}

	bool Workstation::attemptToMoveOrder()
	{	
		bool orderMoved = false;

		if (!m_orders.empty())
		{
			bool orderFilled = (m_orders.front()).isItemFilled(getItemName());
			bool inStock = getQuantity() > 0;

			if (orderFilled || !inStock)
			{
				if (getNextStation())
				{
					*m_pNextStation += std::move(m_orders.front());
				}
				else if (m_orders.front().isOrderFilled())
				{
					g_completed.push_back(std::move(m_orders.front()));
				}
				else
				{
					g_incomplete.push_back(std::move(m_orders.front()));
				}
				
				m_orders.pop_front();
				orderMoved = true;
			}
		}
		
		return orderMoved;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		if (getNextStation())
			os << getItemName() << " --> " << m_pNextStation->getItemName() << "\n";
		else
			os << getItemName() << " --> " << "End of Line\n";
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}