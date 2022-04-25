//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/03/27
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_GENERATINGLIST_H
#define SDDS_GENERATINGLIST_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds {
	template<typename T>
	class GeneratingList {

		std::vector<T> list;
	public:

		GeneratingList(){}
		GeneratingList(const char* f) {
			std::ifstream file(f);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(f) + std::string(" ***");

			while (file) {
				T t;
				if (t.load(file))
					list.push_back(T(t));
			}
		}

		size_t size() const { return list.size(); }
		const T& operator[](size_t i) const { return list[i]; }

		//TODO: Implement the Luhn Algorithm to check the 
		//      valadity of SIN No's

		bool SINValidator(const std::string& SIN)
		{
			size_t len = SIN.length(); // 9
			std::string payload = SIN.substr(0, len - 1);  // dropping check digit
			size_t payloadLen = payload.length();
			int assumedCheckDigit = stoi(SIN.substr(8)), calculatedCheckDigit{}; // for comparison
			int payloadData = 0, sum = 0;
			for (int i = payloadLen - 1; i >= 0; i--)
			{
				payloadData = payload[i] - '0'; // converting a char to int
				if(i % 2 != 0)
					payloadData *= 2;

				if (payloadData > 9)
					payloadData = (payloadData / 10) + (payloadData % 10);
				sum += payloadData;

			}
			calculatedCheckDigit = ((10 - (sum % 10)) % 10);
			return calculatedCheckDigit == assumedCheckDigit;
		}

		//TODO: Overload the += operator with a raw pointer
		// as a second operand.
		void operator+=(T* type)
		{
			list.push_back(*type);
		}

		//TODO: Overload the += operator with a raw pointer
		// as a second operand.

		void operator+=(std::unique_ptr<T> smartType)
		{
			list.push_back(*smartType);
		}

		void print(std::ostream& os) const {
			os << std::fixed << std::setprecision(2);
			for (auto& e : list)
				e.print(os);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const GeneratingList<T>& rd) {
		rd.print(os);
		return os;
	}
}
#endif // !SDDS_GENERATINGLIST_H
