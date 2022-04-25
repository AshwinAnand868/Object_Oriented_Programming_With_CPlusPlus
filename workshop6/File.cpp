//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/03/12
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include"File.h"

namespace sdds
{
	File::File(std::string name, std::string contents ="")
	{
			m_name = name;
			m_contents = contents;
	}

	void File::update_parent_path(const std::string& parentPath)
	{
		m_parent_path = parentPath;
	}

	NodeType File::type() const
	{
		return NodeType::FILE;
	}

	std::string File::path() const
	{
		return m_parent_path + m_name;
	}

	std::string File::name() const
	{
		return m_name;
	}

	int File::count() const
	{
		return -1;
	}

	size_t File::size() const
	{
		size_t count = 0u;
		for (auto i = 0u; i < m_contents.length(); i++)
		{
			if (m_contents[i])
			{
				count++;
			}
		}
		return count;
	}
}
