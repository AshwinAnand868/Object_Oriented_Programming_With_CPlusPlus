//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/02/13
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_CONFIRMORDER_H
#define SDDS_CONFIRMORDER_H

#include<iostream>
#include"Toy.h"

namespace sdds
{
	class ConfirmOrder
	{
			const Toy** toys{};
			int toyCounter{};
		public:
			ConfirmOrder(){ }
			ConfirmOrder(const ConfirmOrder& confirmOrder);
			ConfirmOrder& operator=(const ConfirmOrder& confirmOrder);
			ConfirmOrder(ConfirmOrder&& confirmOrder) noexcept;
			ConfirmOrder& operator=(ConfirmOrder&& confirmOrder) noexcept;
			~ConfirmOrder();
			ConfirmOrder& operator+=(const Toy& toy);
			ConfirmOrder& operator-=(const Toy& toy);
			friend std::ostream& operator<<(std::ostream& ostr, const ConfirmOrder& confirmOrder);

	};
}
#endif // !SDDS_CONFIRMORDER_H
