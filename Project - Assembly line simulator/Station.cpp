// Name: Ashwin Anand
// Seneca Student ID: 152042206
// Seneca email: aanand24@myseneca.ca
// Date of completion: 19-03-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include"Station.h"

namespace sdds
{
	size_t Station::m_widthField = 0, Station::id_generator = 0;

	Station::Station(const std::string& row)
	{
		Utilities utils{};
		size_t next_pos = 0u;
		bool more = true;
		m_id = id_generator;
		id_generator++;
		std::string tokens[4];
		int i = 0;
		do
		{
			tokens[i] = utils.extractToken(row, next_pos, more);
			i++;
		} while (more && i < 3);

		if (m_widthField < utils.getFieldWidth())
			m_widthField = utils.getFieldWidth();


		tokens[i] = utils.extractToken(row, next_pos, more);

		m_itemName = tokens[0];
		m_serialNumber = stoi(tokens[1]);
		m_nItems = stoi(tokens[2]);
		m_desc = tokens[3];
	}

	const std::string& Station::getItemName() const
	{
		return m_itemName;
	}
	size_t Station::getNextSerialNumber()
	{
		size_t nextSerNo = m_serialNumber;
		m_serialNumber++;
		return nextSerNo;
	}
	size_t Station::getQuantity() const
	{
		return m_nItems;
	}
	void Station::updateQuantity()
	{
		if (m_nItems > 0) m_nItems--;
	}
	void Station::display(std::ostream& os, bool full)const
	{
		os.width(3);
		os.fill('0');
		os << m_id + 1;
		os.fill(' ');
		os << " | ";
		os.width(m_widthField + 1);
		os.setf(std::ios::left, std::ios::adjustfield);
		os << m_itemName;
		os.unsetf(std::ios::left);
		os << " | ";	
		os.width(6);
		os.fill('0');
		os << m_serialNumber;
		os.fill(' ');
		os << " | ";

		if (full)
		{
			os.width(4);
			os << m_nItems;
			os << " | ";
			os << m_desc << std::endl;
		}
		else
			os << std::endl;
	}
}
