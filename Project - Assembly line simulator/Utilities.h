// Name: Ashwin Anand
// Seneca Student ID: 152042206
// Seneca email: aanand24@myseneca.ca
// Date of completion: 19-03-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include<iostream>
#include<string>
namespace sdds
{
	class Utilities
	{
		size_t m_widthField{ 1 };
		static char m_delimiter;
	public:
		Utilities(){ }
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		void removeSpecificChars(std::string& target, char toBeRemoved);
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
}
#endif // !SDDS_UTILITIES_H

