//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/02/13
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_TOY_H
#define SDDS_TOY_H

#include<iostream>
#include <string>
namespace sdds
{
	class Toy
	{
		unsigned orderId{};
		std::string toyName{};
		unsigned nItems{};
		double price{};
		double HST{ 0.13 };
	public:
		Toy()
		{
		}
		Toy(const Toy& toy);
		void update(int numItems);
		Toy(const std::string& toy);
		friend std::ostream& operator<<(std::ostream& ostr, const Toy& toy);
	};
	
}



#endif // !SDDS_TOY_H
