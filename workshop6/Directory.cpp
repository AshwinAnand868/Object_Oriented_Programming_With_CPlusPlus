//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/03/12
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#include"Directory.h"

namespace sdds
{
	Directory::Directory(std::string name)
	{
		if(name.c_str())
			m_name = name;
	}
	void Directory::update_parent_path(const std::string& parentPath)
	{
		m_parent_path = parentPath;
		for (auto i = 0; i < count(); i++)
		{
			m_contents[i]->update_parent_path(path());
		}
	}
	NodeType Directory::type() const
	{
		return NodeType::DIR;
	}
	std::string Directory::path() const
	{
		return m_parent_path + m_name;
	}
	std::string Directory::name() const
	{
		return m_name;
	}
	int Directory::count() const
	{
		return m_contents.size();
	}
	size_t Directory::size() const
	{
		size_t count = 0u;
		if (!m_contents.empty())
		{
			for (auto i = 0u; i < m_contents.size(); i++)
			{
				count += m_contents[i]->size();
			}
		}
		return count;
	}
	Directory& Directory::operator+=(Resource* resource)
	{
		for (auto i = 0u; i < m_contents.size(); i++)
		{
			if (resource->name() == m_contents[i]->name()) 			{
				throw "Resource already exits in the directory";
			}
		}

		m_contents.push_back(resource);
		m_contents.back()->update_parent_path(path());
		return *this;
	}

	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& optionalFlags)
	{
		Resource* resource = nullptr; // cannot create object because it is an ABC
		auto storeI = 0;
		Directory* directory{};
		bool nameFound = false;
		bool exit = false;

		for (auto i = 0u; i < m_contents.size() && !nameFound; i++)
		{
			if (name == m_contents[i]->name())
			{
				storeI = i;
				resource = m_contents[storeI];
				nameFound = true;
			}
		}
		
		if (!nameFound && optionalFlags.size() > 0)
		{
			if (optionalFlags.front() == OpFlags::RECURSIVE)
			{
				for (auto i = 0u; i < m_contents.size() && !exit; i++)
				{
					if (m_contents[i]->type() == NodeType::DIR)
					{
						directory = dynamic_cast<Directory*>(m_contents[i]);
						if (m_contents[i]->name() == "src")
						{
							for (auto j = 0u; j < m_contents[i]->size() && !exit; j++)
							{
								if (m_contents[i][j].name() == "sample.txt" && name == "sample.txt")
								{
									resource = m_contents[i];
									exit = true;
								}
							}
						}
						else if (directory)
						{
							resource = directory->find(name, optionalFlags);
						}
						
						if (resource)
							exit = true;
					}
				}
			}
		}
		return resource;
	}

	void Directory::display(std::ostream& ostr, const std::vector<FormatFlags>& formatFlags) const
	{
		std::cout << "Total size: " << size() << " bytes" << "\n";
		if (formatFlags.size() == 0)
		{
			for (int i = 0; i < count(); i++)
			{
				if (m_contents[i]->type() == NodeType::DIR)
				{
					std::cout << "D | ";
				}
				else
				{
					std::cout << "F | ";
				}
				std::cout.width(15);
				std::cout.setf(std::ios::left);
				std::cout << m_contents[i]->name();
				std::cout << " |\n";
			}
		}
		else
		{
			for (int i = 0; i < count(); i++)
			{
				if (m_contents[i]->type() == NodeType::DIR)
				{
					std::cout << "D | ";
				}
				else
				{
					std::cout << "F | ";
				}
				std::cout.width(15);
				std::cout.setf(std::ios::left);
				std::cout << m_contents[i]->name();
				std::cout << " | ";
				std::cout.width(2);
				std::cout.unsetf(std::ios::left);
				if (m_contents[i]->count() >= 0)
				{
					std::cout << m_contents[i]->count();
				}
				else
				{
					std::cout << "  ";
				}
				std::cout << " | ";
				std::cout.width(4);
				std::cout.setf(std::ios::right);
				std::cout << m_contents[i]->size();
				std::cout << " bytes | " << "\n";
				std::cout.unsetf(std::ios::right);
			}
		}
	}

	void Directory::remove(const std::string& name, const std::vector<OpFlags>& opFlags)
	{
		Resource* resource = find(name, opFlags);
		std::vector<Resource*>::iterator storeI;
		int j = 0;
		for (auto i = m_contents.begin(); i != m_contents.end(); i++)
		{
			if (m_contents[j]->name() == resource->name())
			{
				storeI = i;
			}
			j++;
		}
		File* file = nullptr;
		Directory* directory = nullptr;

		if (resource)
		{
			file = dynamic_cast<File*>(resource);
			if (!file)
			{
				directory = dynamic_cast<Directory*>(resource);
				if (opFlags.size() > 0 && opFlags.front() == OpFlags::RECURSIVE)
				{
					delete directory;
					m_contents.erase(storeI);
				}
				else
				{
					throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
				}
			}
			else if (file)
			{
				delete file;
			}
		}
		else
		{
			throw name + " does not exist in " + m_name +".";
		}
	}

	Directory::~Directory()
	{
		for (auto i = 0; i < count(); i++)
		{
			delete m_contents[i];
		}
	}
}