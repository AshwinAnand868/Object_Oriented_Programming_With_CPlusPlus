//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/01/28
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_PAIR_H
#define SDDS_PAIR_H
#include<iostream>

namespace sdds
{
	class Pair
	{
		std::string m_key{};
		std::string m_value{};
	public:
		const std::string& getKey()const //const added by me
		{
			return m_key;
		}
		const std::string& getValue()const
		{
			return m_value;
		}

		Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value }{};
		Pair();
	};
	std::ostream& operator<<(std::ostream& ostr, const Pair& pair);
	bool operator==(const Pair& pair1, const Pair& pair2);
}

#endif	