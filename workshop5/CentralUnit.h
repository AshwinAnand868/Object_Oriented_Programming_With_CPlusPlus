//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/02/27
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#ifndef SDDS_CENTRALUNIT_H
#define SDDS_CENTRALUNIT_H


#include<iostream>
#include<fstream>
#include<utility>
#include<cstring>
#include"Job.h"
namespace sdds
{
	const int MAXJOBS = 4;
	template<typename T>
	class CentralUnit
	{
		std::string m_type{}; 
		T** m_items{}; 		
		Job* m_jobs[MAXJOBS]{};
		size_t m_size{}; 
		size_t m_count{}; 
	public:
		static std::ostream& log;
		static void complete_job(CentralUnit<T>& cU, T* unitAddress);

		CentralUnit()
		{
		}

		void removeSpecificChars(std::string& target, char toBeRemoved)
		{
			target.erase(0, target.find_first_not_of(toBeRemoved));
			target.erase(target.find_last_not_of(toBeRemoved) + 1);
		}
		CentralUnit(std::string type, const char* filename)
		{
			m_type = type;
			std::ifstream file(filename);
			size_t pos = 0, nextPos = 0;
			int i = 0, njobsCanHandle = 0;
			std::string readingString{}, tokens[3];
			if (!file)
			{
				throw std::invalid_argument("File cannot be opened.");
			}
			else
			{
				do
				{
					std::getline(file, readingString);

					if (file)
					{
						m_size++;
					}

				} while (file);

				m_items = new T * [m_size];
				m_size = 0;

				file.clear();
				file.seekg(std::ios::beg);
				do
				{
					std::getline(file, readingString);
					if (file)
					{
						while (nextPos != std::string::npos)
						{
							nextPos = readingString.find('|', pos);
							tokens[i] = readingString.substr(pos, nextPos - pos);
							removeSpecificChars(tokens[i], ' ');
							pos = nextPos + 1;
							i++;
						}

						nextPos = 0;
						pos = 0;

						try
						{
							njobsCanHandle = stoi(tokens[2]);
						}
						catch (std::invalid_argument&)
						{
							njobsCanHandle = 1;
						}

						m_items[m_size] = new T(this, tokens[0], tokens[1], njobsCanHandle); 

						m_items[m_size]->on_complete(complete_job);
						m_items[m_size]->on_error([this](T* processor)->void
							{
								Job* jobUnprocessed = processor->free();
								log << "Failed to complete job " << jobUnprocessed->name() << "\n";
								log << this->get_available_units() << " units available.\n";
								delete jobUnprocessed;
							});
						m_size++;
						i = 0;
					}
				} while (file);
			}
		}
		CentralUnit(const CentralUnit& cU)
		{
			throw "Error: Cannot copy for a new instance";
		}

		CentralUnit& operator=(const CentralUnit& cU) = delete;

		CentralUnit(CentralUnit&& cU)
		{
			*this = std::move(cU);
		}
		CentralUnit& operator=(CentralUnit&& cU)
		{
			if (this != &cU)
			{
				size_t i;
				m_type = cU.m_type;
				cU.m_type = "";
				m_size = cU.m_size;
				cU.m_size = 0;
				m_count = cU.m_count;
				cU.m_count = 0;

				for (i = 0; i < m_size; i++)
				{
					delete m_items[i];
				}
				delete[] m_items;


				m_items = cU.m_items;

				if (m_items && m_count > 0)
				{
					for (i = 0; i < m_size; i++)
					{
						m_items[i] = cU.m_items[i];
					}
				}

				for (i = 0; i < m_size; i++)
					cU.m_items[i] = nullptr;

				cU.m_items = nullptr;

				for (i = 0; i < m_count; i++)
				{
					delete m_jobs[i];
				}

				m_jobs = cU.m_jobs;
				for (i = 0; i < m_count; i++)
				{
					m_jobs[i] = cU.m_jobs[i];
				}
				for (i = 0; i < m_count; i++)
				{
					cU.m_jobs[i] = nullptr;
				}
				cU.m_jobs = nullptr;
			}
		}

		~CentralUnit()
		{
			size_t i;
			for (i = 0; i < m_size; i++)
			{
				delete m_items[i];
			}
			delete[] m_items;
			for (i = 0; i < m_count; i++)
			{
				delete m_jobs[i];
			}
		}
		CentralUnit& operator+=(std::string jobName)
		{
			if (m_count == MAXJOBS)
			{
				throw "Error: Job cannot be handled; queue is full";
			}
			else
			{
				m_jobs[m_count] = new Job(jobName);
				++m_count;
				return *this;
			}
		}

		bool has_jobs()const
		{
			return (unsigned)get_available_units() < m_size || m_count > 0;
		}

		int get_available_units()const
		{
			int count = 0;
			for (size_t i = 0; i < m_size; i++)
			{
				if (*this->m_items[i])
					count++;
			}
			return count;
		}
		void run()
		{
			for (size_t i = 0; i < m_size; i++)
			{
				if (*m_items[i] && m_count > 0)
				{
					m_items[i]->operator+=(m_jobs[m_count - 1]);
					m_count--;
				}
				m_items[i]->operator()();
			}
		}

		void operator+=(T* unit)
		{
			if (*unit)
			{
				size_t i = 0;
				T** temp = new T * [m_size + 1];
				for ( i = 0; i < m_size; i++)
				{
					temp[i] = m_items[i];
				}

				temp[i] = unit;

				delete[] m_items;
				m_size++;

				m_items = new T * [m_size];
				for ( i = 0; i < m_size; i++)
				{
					//m_items[i] = new T();
					m_items[i] = temp[i];
				}

				m_items[m_size - 1]->on_complete(complete_job);
				m_items[m_size - 1]->on_error([this](T* processor)->void
					{
						Job* jobUnprocessed = processor->free();
						log << "Failed to complete job " << (processor->get_current_job())->name() << "\n";
						log << this->get_available_units() << " units available.\n";
						delete jobUnprocessed;
					});

				//for ( i = 0; i < m_size; i++)
				//	delete temp[i];
				delete[] temp;
			}
			else
			{
				throw "Unit Not Available";
			}
		}
		T* operator[](const char* job_title)const
		{
			std::string name = "";
			int match{-1};
			for (size_t i = 0; i < m_size; i++)
			{
				name = (m_items[i]->get_current_job()) ? (m_items[i]->get_current_job())->name() : "";
				if (!strcmp(name.c_str(), job_title))
					match = i;
			}
			if (match == -1)
			{
				throw std::out_of_range("Job is not being handled by a unit.");
			}
			return m_items[match];
		}
		void display()const
		{
			log << "Central " << m_type << " Unit list\n";
			for (size_t i = 0; i < m_size; i++)
			{	
				log << "[";
				log.width(4);
				log.fill('0');
				log << i + 1;
				log << "] " << *m_items[i] <<"\n";
				log.fill(' ');
			}
		}
	};

	template<typename T>
	std::ostream& CentralUnit<T>::log = std::cout;
	
	template<typename T>
     void CentralUnit<T>::complete_job(CentralUnit<T>& cU, T* unitAddress)
	 {
		 Job* finishedJob = unitAddress->free();
		 log << "[COMPLETE] " << *finishedJob << " using " << *unitAddress << "\n";
		 log << cU.get_available_units() << " units available.\n";

		 delete finishedJob;
	 }
}

#endif // !SDDS_CENTRALUNIT_H



