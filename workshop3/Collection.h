//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/01/28
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include<iostream>
#include"Pair.h"

namespace sdds
{
	template<typename T, unsigned CAPACITY>
	class Collection
	{
		T collection[CAPACITY]{};
		int nElements{};
		static T dummy;
		public:
			Collection(){ }

			int size()const
			{
				return nElements;
			}
			std::ostream& display(std::ostream& ostr = std::cout)const
			{
				ostr.width(23);
				ostr.fill('-');
				ostr << "\n" << "| Collection Content |" << "\n";
				ostr.width(23);
				ostr.fill('-');
				ostr << "\n";
				for (int i = 0; i < nElements; i++)
				{
					ostr << collection[i] << "\n";
				}
				ostr.width(23);
				ostr.fill('-');
				ostr << "\n";
				return ostr;
			}
			virtual bool add(const T& item)
			{
				bool status = false;
				if ((unsigned) nElements < CAPACITY)
				{
					collection[nElements++] = item;
					status = true;
				}
				return status;
			}
			T operator[](int index)const
			{
				if (index >= 0 && index < nElements)
				{
					return collection[index];
				}
				return dummy;
			}
			virtual ~Collection(){  }
	};

	template<typename T, unsigned CAPACITY>
	T Collection<T, CAPACITY>::dummy{};

	template<> // denotes specialization
	Pair Collection<Pair, 100>::dummy{ "No Key", "No Value" };

}


#endif