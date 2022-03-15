//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/02/13
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include<algorithm>
#include"Toy.h"

namespace sdds
{
	void Toy::update(int numItems)
	{
		 nItems = numItems;
	}
	void removeSpecificChars(std::string& target, char toBeRemoved)
	{
		target.erase(0, target.find_first_not_of(toBeRemoved));
		target.erase(target.find_last_not_of(toBeRemoved) + 1);
	}
	Toy::Toy(const std::string& toy)
	{
		size_t pointerB = 0;
		size_t nextPos = 0;
		std::string delimeter = ":";
		std::string tokens[4];
		int i = 0;

		nextPos = toy.find(delimeter, pointerB);
		while (nextPos != std::string::npos)
		{
			tokens[i] = toy.substr(pointerB, nextPos - pointerB); 
			removeSpecificChars(tokens[i], ' ');
			pointerB = nextPos + 1;
			nextPos = toy.find(delimeter, pointerB);
			i++;
		}

		tokens[i] = toy.substr(pointerB);
		removeSpecificChars(tokens[i], ' ');

		orderId = std::stoi(tokens[0]);
		toyName = tokens[1];
		nItems = std::stoi(tokens[2]);
		price = std::stod(tokens[3]);
	}

	Toy::Toy(const Toy& toy)
	{
		orderId = toy.orderId;
		toyName = toy.toyName;
		nItems = toy.nItems;
		price = toy.price;
	}

	std::ostream& operator<<(std::ostream& ostr, const Toy& toy)
	{
		double subtotal{}, total{}, tax{};
		ostr << "Toy";
		ostr.width(8);
		ostr << toy.orderId;
		ostr << ":";
		ostr.width(18);
		ostr << toy.toyName;
		ostr.width(3);
		ostr << toy.nItems;
		ostr << " items";
		ostr.width(8);
		ostr << toy.price;
		ostr << "/item  subtotal:";
		subtotal = toy.price * toy.nItems;
		ostr.width(7);
		ostr << subtotal;
		ostr << " tax:";
		tax = subtotal * toy.HST;
		ostr.width(6);
		ostr.setf(std::ios::fixed);
		ostr.precision(2);
		ostr << tax;
		ostr << " total:";
		total = subtotal + tax;
		ostr.width(7);
		ostr << total << "\n";
		return ostr;
	}
}