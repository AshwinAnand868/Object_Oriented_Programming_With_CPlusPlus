//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/01/28
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_SET_H
#define SDDS_SET_H
#include<cmath>
#include"Collection.h"

namespace sdds
{
	template<typename T>
	class Set : public Collection<T,100>
	{
		public:
			Set(){ }
			bool add(const T& item);
	};
	
	template<typename T>
	bool Set<T>::add(const T& item)
	{
		bool status = false, exists = false;
		int currentElements = Collection<T, 100>::size();

		if (currentElements < 100 )
		{		
			if (currentElements > 0)
			{
				for (int i = 0; !exists && i < currentElements; i++)
				{
					if (item == Collection<T, 100>::operator[](i))
					{
						exists = true;
					}
				}
			}
			
			if (!exists)
			{
				Collection<T, 100>::add(item);
				status = true;
			}			
		}
		return status;
	}


	template<>
	bool Set<double>::add(const double& item)
	{
		bool status = false, exists = false;
		int currentElements = Collection<double, 100>::size();

		if (currentElements < 100)
		{
			if (currentElements > 0)
			{
				for (int i = 0; !exists && i < currentElements; i++)
				{
					if (fabs(item - Collection<double, 100>::operator[](i)) <= 0.01)
					{
						exists = true;
					}
				}
			}

			if (!exists)
			{
				Collection<double, 100>::add(item);
				status = true;
			}
		}
		return status;
	}

}
#endif