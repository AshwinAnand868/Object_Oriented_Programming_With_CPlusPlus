//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/01/28
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#include"Pair.h"

namespace sdds
{
	Pair::Pair(){ }
	std::ostream& operator<<(std::ostream& ostr, const Pair& pair)
	{
		ostr.width(20);
		ostr.fill(' ');
		ostr << pair.getKey();
		ostr << ": ";
		ostr << pair.getValue();
		return ostr;
	}
	bool operator==(const Pair& pair1, const Pair& pair2)
	{
		return pair1.getKey() == pair2.getKey();
	}
}