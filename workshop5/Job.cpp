//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/02/27
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include"Job.h"

namespace sdds
{
	Job::Job(std::string title)
	{
		if (!title.empty())
		{
			jobTitle = title;
			unitsOfWork = (jobTitle.length() % 10) + 1;
			remUnitOfWork = unitsOfWork;
			isActive = true;
		}
	}

	bool Job::is_active()
	{
		return isActive;
	}

	bool Job::is_complete()
	{
		return remUnitOfWork == 0; 
	}

	std::string Job::name()
	{
		return jobTitle;
	}

	void Job::display(std::ostream& ostr)
	{
		ostr << "`" << jobTitle << "` [";
		ostr.fill('0');
		ostr.width(2);
		ostr << remUnitOfWork;
		ostr << "/";
		ostr.width(2);
		ostr << unitsOfWork;
		ostr << " remaining]";
		ostr.fill(' ');
	}

	void Job::operator()(unsigned int uWork) 
	{
		if(uWork <= remUnitOfWork)
		{
			remUnitOfWork = remUnitOfWork - uWork;
			if (remUnitOfWork == 0)
				isActive = false;
		}
		else
		{
			remUnitOfWork = 0;
			isActive = false;
			throw std::underflow_error("Error: Too many Units of work");
		}
	}
	std::ostream& operator<<(std::ostream& ostr, Job& job)
	{
		job.display(ostr);
		return ostr;
	}
}