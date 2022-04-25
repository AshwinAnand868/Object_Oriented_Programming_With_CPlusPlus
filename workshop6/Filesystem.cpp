//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/03/12
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include "Filesystem.h"
namespace sdds
{
	void removeSpecificChars(std::string& target, char toBeRemoved)
	{
		target.erase(0, target.find_first_not_of(toBeRemoved));
		target.erase(target.find_last_not_of(toBeRemoved) + 1);
	}
	Filesystem::Filesystem(std::string fileName, std::string rootName)
	{
		std::string line="", directoryName = "", file_name="", contents="";
		std::ifstream file(fileName);
		size_t pos{0}, nextpos{0};
		Directory* directory{};
		File* file_ptr{};
		if (file)
		{
			m_root = new Directory(rootName);

			do
			{
				std::getline(file, line);

				if (file)
				{
					nextpos = line.find('/');
					if (nextpos != std::string::npos)
					{
						directoryName = line.substr(pos, nextpos + 1);
						removeSpecificChars(directoryName, ' ');
						if (!(m_root->find(directoryName)))
						{
							directory = new Directory(directoryName);
							*m_root += directory;
						}
						pos = nextpos + 1;
						nextpos = line.find('/', pos);
						m_current = std::move(directory);
					}
					
					while (nextpos != std::string::npos)
					{
						directoryName = line.substr(pos, (nextpos - pos) + 1);
						removeSpecificChars(directoryName, ' ');
						if (!(m_current->find(directoryName)))
						{
							directory = new Directory(directoryName);
							*m_current += directory;
						}
						pos = nextpos + 1;
						nextpos = line.find('/', pos);
						m_current = std::move(directory);
					}
					nextpos = line.find('|', pos);
					if (nextpos != std::string::npos)
					{
						file_name = line.substr(pos, (nextpos - pos));
						removeSpecificChars(file_name, ' ');
						pos = nextpos + 1;
						nextpos = line.find('\n', pos);
						contents = line.substr(pos, (nextpos - pos));
						removeSpecificChars(contents, ' ');
						file_ptr = new File(file_name, contents);
						*m_current += std::move(file_ptr);
					}
					nextpos = 0;
					pos = 0;
				}
				m_current = m_root;
				
			} while (file);
		}
		else
		{
			throw "File does not exist";
		}
	}
	Filesystem::Filesystem(Filesystem&& filesystem)noexcept
	{
		*this = std::move(filesystem);
	}
	Filesystem& Filesystem::operator=(Filesystem&& filesystem)noexcept
	{
		if (this != &filesystem)
		{
			delete m_root;
			m_root = nullptr;
			if (filesystem.m_root)
				m_root = filesystem.m_root;
			filesystem.m_root = nullptr;
			delete m_current;
			m_current = nullptr;
			if (filesystem.m_current)
				m_current = filesystem.m_current;
			filesystem.m_current = nullptr;
		}
		return *this;
	}

	Filesystem& Filesystem::operator+=(Resource* resource)
	{
		*m_current += resource;
		return *this;
	}

	Directory* Filesystem::change_directory(const std::string& dir_name)
	{
		
		Resource* resource = m_current->find(dir_name);

		if (dir_name == "")
			m_current = m_root;
		else if(resource)
		{
			m_current = dynamic_cast<Directory*>(resource);
		}
		else
		{
			std::string string1 = dir_name + " not found!";
			throw std::invalid_argument("Cannot change directory! " +string1);
		}
		return m_current;
	}

	Directory* Filesystem::get_current_directory()
	{
		return m_current;
	}

	Filesystem::~Filesystem()
	{
		delete m_root;
	}
}

