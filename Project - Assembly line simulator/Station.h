// Name: Ashwin Anand
// Seneca Student ID: 152042206
// Seneca email: aanand24@myseneca.ca
// Date of completion: 19-03-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include<iostream>
#include<string>
#include"Utilities.h"

namespace sdds
{
	class Station
	{
		int m_id{};
		std::string m_itemName{};
		std::string m_desc{};
		size_t m_serialNumber{}, m_nItems{};
		static size_t m_widthField, id_generator;
	public:
		Station(){ }
		Station(const std::string& row);
		const std::string& getItemName()const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full)const;
	};
}
#endif // !SDDS_STATION_H

