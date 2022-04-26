// Name: Ashwin Anand
// Seneca Student ID: 152042206
// Seneca email: aanand24@myseneca.ca
// Date of completion: 25-03-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include<iostream>
#include<iomanip>
#include<string>
#include<utility>
#include"Station.h"
namespace sdds
{
	class CustomerOrder
	{
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src)
			{
			};
		};

		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItems{};
		static size_t m_widthField;
	public:
		CustomerOrder(){ }
		CustomerOrder(const std::string& record);
		CustomerOrder(const CustomerOrder& customerOrder)
		{
			throw "Copy operations not allowed on CustomerOrder instance";
		}
		CustomerOrder& operator=(const CustomerOrder& customerOrder) = delete;
		CustomerOrder(CustomerOrder&& customerOrder) noexcept;
		CustomerOrder& operator=(CustomerOrder&& customerOrder) noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName)const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os)const;
	};
}



#endif // !SDDS_CUSTOMERORDER_H

