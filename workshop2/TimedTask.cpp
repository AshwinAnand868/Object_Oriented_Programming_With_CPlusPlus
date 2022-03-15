//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/01/28
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#define _CRT_SECURE_NO_WARNINGS
#include<cstring>
#include"TimedTask.h"


using namespace std;

namespace sdds
{

	void TimedTask::startClock()
	{
		start = chrono::steady_clock::now();
	}
	void TimedTask::stopClock()
	{
		end = chrono::steady_clock::now();
	}
	void TimedTask::addTask(const char* tName)
	{
		tasks[nRecords].taskName = tName;
		tasks[nRecords].timeUnits = "nanoseconds";
		tasks[nRecords].taskDuration = chrono::duration_cast<chrono::nanoseconds>(end - start);
		nRecords++;
	}
	ostream& operator<<(ostream& ostr,const TimedTask& timedTask)
	{
		ostr << "--------------------------\n";
		ostr << "Execution Times:\n";
		ostr << "--------------------------\n";
		for (int i = 0; i < timedTask.nRecords; i++)
		{
			ostr.width(21);
			ostr.setf(ios::left);
			ostr << timedTask.tasks[i].taskName.c_str();
			ostr.unsetf(ios::left);
			ostr << " ";
			ostr.width(13);
			ostr << timedTask.tasks[i].taskDuration.count();
			ostr << " ";
			ostr << timedTask.tasks[i].timeUnits.c_str();
			if (i + 1 != timedTask.nRecords)
			{
				ostr << endl;
			}

		}
		ostr << "\n--------------------------\n";
		return ostr;		
	}
}