//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/02/13
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include<utility>
#include"Child.h"

namespace sdds
{
	Child::Child(std::string c_name, int c_age, const Toy* c_toys[], size_t count)
	{
		name = c_name;
		age = c_age;
		toysCounter = count;
		toys = new const Toy * [toysCounter];
		for (size_t i = 0; i < toysCounter; i++)
		{
			toys[i] = new Toy(*c_toys[i]);
		}
	}
	Child::Child(const Child& child)
	{
		*this = child;
	}
	Child& Child::operator=(const Child& child)
	{
		if (this != &child)
		{
			name = child.name;
			age = child.age;

			if(toysCounter){
				for (size_t i = 0; i < toysCounter; i++)
					delete toys[i];
			}
			toysCounter = child.toysCounter;
			delete[] toys;
			
			toys = nullptr;
			if (child.toys && toysCounter > 0)
			{
				toys = new const Toy * [toysCounter];
				for (size_t i = 0; i < toysCounter; i++)
				{
					toys[i] = new Toy(*(child.toys[i]));
				}
			}

		}
		return *this;
	}

	Child::Child(Child&& child) noexcept
	{
		*this = std::move(child);
	}

	Child& Child::operator=(Child&& child) noexcept
	{
		if (this != &child)
		{
			name = child.name;
			child.name = "";
			age = child.age;
			child.age = 0;
			
			if (toysCounter)
			{
				for (size_t i = 0; i < toysCounter; i++)
					delete toys[i];
			}

			delete[] toys;

			toysCounter = child.toysCounter;
			child.toysCounter = 0;
			toys = child.toys;

			for (size_t i = 0; i < toysCounter; i++)
			{
				toys[i] = child.toys[i];
			}
			child.toys = nullptr;
		}
		return *this;
	}

	Child::~Child()
	{
		for (size_t i = 0; i < toysCounter; i++)
			delete toys[i];
		delete[] toys;
	}

	size_t Child::size() const
	{
		return toysCounter;
	}

	std::ostream& operator<<(std::ostream& ostr, const Child& child)
	{
		static int counter = 0;
		counter++;
		ostr << "--------------------------" << "\n";
		ostr << "Child " << counter << ": " << child.name << " " << child.age << " years old:" << "\n";
		ostr << "--------------------------" << "\n";
		if (child.toys && child.toys[0])
		{
			for (size_t i = 0; i < child.toysCounter; i++)
					ostr << *child.toys[i];
		}
		else
		{
			ostr << "This child has no toys!" << "\n";
		}
		ostr << "--------------------------" << "\n";		
		return ostr;
	}

}