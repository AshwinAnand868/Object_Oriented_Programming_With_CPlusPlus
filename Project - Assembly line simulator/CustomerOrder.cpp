// Name: Ashwin Anand
// Seneca Student ID: 152042206
// Seneca email: aanand24@myseneca.ca
// Date of completion: 25-03-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include"CustomerOrder.h"
#include"Utilities.h"
namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(const std::string& record)
	{
		size_t next_pos{};
		Utilities utils{};
		bool more = true;
		std::string tokens[2];
		std::string item_name = "";
		int i = 0;

		do
		{
			if(utils.getDelimiter() == '\n')
				utils.setDelimiter('|');
			utils.extractToken(record, next_pos, more);
			m_cntItem++;
		} while (more);
		m_cntItem = m_cntItem-2;

		m_lstItems = new Item * [m_cntItem];
		next_pos = 0;
		m_cntItem = 0;
		do
		{
			if (i < 2)
			{
				tokens[i] = utils.extractToken(record, next_pos, more);
				i++;
			}
			else
			{
				item_name = utils.extractToken(record, next_pos, more);

				m_lstItems[m_cntItem] = new Item(item_name);
				m_cntItem++;
			}
		} while (more);

		m_name = tokens[0];
		m_product = tokens[1];
		if (m_widthField < utils.getFieldWidth())
			m_widthField = utils.getFieldWidth();
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& customerOrder) noexcept
	{
		*this = std::move(customerOrder);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& customerOrder) noexcept
	{
		m_name = customerOrder.m_name;
		customerOrder.m_name = "";
		
		m_product = customerOrder.m_product;

		for (size_t i = 0; i < m_cntItem; i++)
			delete m_lstItems[i];
		delete[] m_lstItems;

		m_cntItem = customerOrder.m_cntItem;
		customerOrder.m_cntItem = 0;

		m_lstItems = customerOrder.m_lstItems;
		customerOrder.m_lstItems = nullptr;
		return *this;
	}

	bool CustomerOrder::isOrderFilled() const
	{
		bool orderFilled{};
		bool loopBreaker = false;
		for (size_t i = 0; i < m_cntItem && !loopBreaker; i++)
		{
			if (m_lstItems[i]->m_isFilled)
				orderFilled = true;
			else
			{
				orderFilled = false;
				loopBreaker = true;
			}
			
		}
		return orderFilled;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName)const
	{
		bool isItemPresent = false;
		bool isItemFilled = false;
		bool result{};
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItems[i]->m_itemName == itemName)
			{
				isItemPresent = true;
				if (m_lstItems[i]->m_isFilled)
					isItemFilled = true;
				else
					isItemFilled = false;
			}
		}
		if (!isItemPresent)
			result = true;
		else 
			result = isItemPresent && isItemFilled;

		return result;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		std::string i_name = station.getItemName();
		size_t quantity = 0;
		bool oneFillDone = false;
		for (size_t i = 0; i < m_cntItem && !oneFillDone; i++)
		{
			if (m_lstItems[i]->m_itemName == i_name && !m_lstItems[i]->m_isFilled)
			{
				quantity = station.getQuantity();
				if (quantity > 0)
				{
					m_lstItems[i]->m_isFilled = true;
					station.updateQuantity();

					m_lstItems[i]->m_serialNumber = station.getNextSerialNumber();

					os << "    Filled " << m_name << ", " << m_product << " [" << i_name << "]\n";
					oneFillDone = true;
				}
				else
				{
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << i_name << "]\n";
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << "\n";
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << std::setw(6) << std::left << std::setfill('0') << std::right <<m_lstItems[i]->m_serialNumber;
			
			os << "] " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItems[i]->m_itemName <<  "   - " << std::right;
			if (isItemFilled(m_lstItems[i]->m_itemName))
				os << "FILLED\n";
			else
				os << "TO BE FILLED\n";
		}
	}



	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++)
			delete m_lstItems[i];
		delete[] m_lstItems;
	}

}