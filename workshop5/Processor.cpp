//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/02/27
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include"Processor.h"

namespace sdds
{
	Processor::Processor(CentralUnit<Processor>* cU, std::string brand, std::string code, int power)
	{
		hostingUnit = cU;
		m_brand = brand;
		m_code = code;
		m_power = power;
	}
	void Processor::run()
	{
		if (hostingUnit && m_current)
		{
			try
			{
				if (m_current->is_complete())
				{
					delete m_current;
					m_current = nullptr;
					
				}
				else
				{
					m_current->operator()(m_power);
				}
			}
			catch (std::underflow_error&)
			{
				CentralUnit<Processor>::log << "Processed over quota for ";
				CentralUnit<Processor>::log << *m_current;
				delete m_current;
				m_current = nullptr;
			}
		}
		
	}
	void Processor::operator()()
	{

			if (hostingUnit && m_current && !m_current->is_complete())
			{
				try
				{
					m_current->operator()(m_power);
					if (m_current->is_complete())
					{
						if (afterJobFinishes)
						{
							afterJobFinishes(*hostingUnit, this);
						}
						delete m_current;
						m_current = nullptr;
					}
				}
				catch (std::underflow_error&)
				{
					if (runWhenError)
					{
						runWhenError(this);
						delete m_current;
						m_current = nullptr;
					}
				}
			}
		
	}
	Processor::operator bool() const
	{  
		return m_current == nullptr;
	}
	Processor& Processor::operator+=(Job*& currentJob)
	{
		if (*this)
		{
			m_current = currentJob;
		}
		else
		{
			throw "Job already assigned";
		}
		return *this;
	}

	Job* Processor::get_current_job()const
	{
		return m_current;
	}
	void Processor::on_complete(void(*jobIsDone)(CentralUnit<Processor>& cU, Processor* processor))
	{
		if(jobIsDone)
		   afterJobFinishes = jobIsDone;
	}
	void Processor::on_error(std::function<void(Processor*)> errorCatched)
	{
		if (errorCatched)
		{
			runWhenError = errorCatched;
		}
	}

	Job* Processor::free()
	{
		Job* oldJob = m_current;
		m_current = nullptr;
		return oldJob;
	}

	
	std::ostream& operator<<(std::ostream& ostr, const Processor& processor)
	{
		ostr << "(" << processor.m_power << ") " << processor.m_brand << " " << processor.m_code;
		if (!processor)
		{
			ostr << " processing " << *(processor.m_current);
		}
		return ostr;
	}

}