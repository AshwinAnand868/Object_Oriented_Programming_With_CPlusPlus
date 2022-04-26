// Name: Ashwin Anand
// Seneca Student ID: 152042206
// Seneca email: aanand24@myseneca.ca
// Date of completion: 19-03-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include"Utilities.h"

namespace sdds
{
	char Utilities::m_delimiter = '\n';

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	void Utilities::removeSpecificChars(std::string& target, char toBeRemoved)
	{
		target.erase(0, target.find_first_not_of(toBeRemoved));
		target.erase(target.find_last_not_of(toBeRemoved) + 1);
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}


	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		size_t delim_pos{};
		std::string token = "";
		
		
		if (str[next_pos] == m_delimiter)
		{
			more = false;
			throw "ERROR: No token.";
		}
		else
		{
			if (delim_pos != std::string::npos)
			{
				delim_pos = str.find(m_delimiter, next_pos);

				token = str.substr(next_pos, delim_pos - next_pos);
				removeSpecificChars(token, ' ');

				if (token.length() > m_widthField)
					m_widthField = token.length();


				delim_pos = str.find(m_delimiter, next_pos);

				if (delim_pos == std::string::npos)
					more = false;
				else
				{
					next_pos = delim_pos + 1; // may be plus 1 req
					more = true;
				}
			}
		}
		return token;
	}
}