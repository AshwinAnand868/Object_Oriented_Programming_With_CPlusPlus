//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/02/13
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "ConfirmOrder.h"

namespace sdds
{
	ConfirmOrder::ConfirmOrder(const ConfirmOrder& confirmOrder)
	{
		*this = confirmOrder;
	}

	ConfirmOrder& ConfirmOrder::operator=(const ConfirmOrder& confirmOrder)
	{
		if (this != &confirmOrder)
		{
			toyCounter = confirmOrder.toyCounter;
			delete[] toys;
			toys = nullptr;
			if (confirmOrder.toys && toyCounter > 0)
			{
				toys = new const Toy * [toyCounter];
				for (int i = 0; i < toyCounter; i++)
				{
					toys[i] = confirmOrder.toys[i];
				}
			}
		}
		return *this;
	}

	ConfirmOrder::ConfirmOrder(ConfirmOrder&& confirmOrder) noexcept
	{
		*this = std::move(confirmOrder);
	}


	ConfirmOrder& ConfirmOrder::operator=(ConfirmOrder&& confirmOrder) noexcept
	{
		if (this != &confirmOrder)
		{
			toyCounter = confirmOrder.toyCounter;
			confirmOrder.toyCounter = 0;
			delete[] toys;
			toys = confirmOrder.toys;
			confirmOrder.toys = nullptr;
		}
		return *this;
	}


	ConfirmOrder::~ConfirmOrder()
	{
		delete[] toys;
	}

	ConfirmOrder& ConfirmOrder::operator+=(const Toy& toy)
	{
		bool addressMatch = false;
		for (int i = 0; i < toyCounter && !addressMatch; i++)
		{
			if (toys[i] == &toy)
			{
				addressMatch = true;
			}
		}

		if (!addressMatch)
		{
			const Toy** tempToys = new const Toy * [toyCounter + 1]; 
			for (int i = 0; i < toyCounter; i++)
					tempToys[i] = toys[i];
			tempToys[toyCounter] = &toy;
			delete[] toys;
			toys = nullptr;
			toys = new const Toy * [++toyCounter]; 
			for (int i = 0; i < toyCounter; i++)
					toys[i] = tempToys[i];
			delete[] tempToys;
		}
		return *this;
	}

	ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy)
	{
		bool addressMatch = false;
		int i = 0;
		for (; i < toyCounter && !addressMatch; i++)
		{
			if (toys[i] == &toy)
			{
				addressMatch = true;
			}
		}

		if (addressMatch)
		{
			for (; i < toyCounter; i++)
				toys[i - 1] = toys[i];

			const Toy** tempToys = new const Toy * [toyCounter-1];

			for (int i = 0; i < toyCounter - 1; i++)
					tempToys[i] = toys[i];
			delete[] toys;
			toys = nullptr;
			toys = new const Toy * [--toyCounter];
			for (int i = 0; i < toyCounter; i++)
				toys[i] = tempToys[i];
			delete[] tempToys;
		}
		return *this;
	}

	std::ostream& operator<<(std::ostream& ostr, const ConfirmOrder& confirmOrder)
	{
		ostr << "--------------------------" << "\n";
		ostr << "Confirmations to Send" << "\n";
		ostr << "--------------------------" << "\n";
		if (confirmOrder.toys && confirmOrder.toys[0])
		{
			for (int i = 0; i < confirmOrder.toyCounter; i++)
				ostr << *confirmOrder.toys[i];
		}
		else
		{
			ostr << "There are no confirmations to send!" << "\n";
		}
		ostr << "--------------------------" << "\n";
		return ostr;
	}

}
