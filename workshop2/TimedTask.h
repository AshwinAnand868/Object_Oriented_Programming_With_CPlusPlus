//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/01/28
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
#ifndef SDDS_TIMEDTASK_H
#define SDDS_TIMEDTASK_H

#include<iostream>
#include<chrono>
#include<string>

namespace sdds
{
	const size_t MAXEVENTS = 10;

	class TimedTask
	{

		struct Task
		{
			std::string taskName{};
			std::string timeUnits{};
			std::chrono::steady_clock::duration taskDuration{};
		};
		int nRecords{};
		std::chrono::steady_clock::time_point start{};
		std::chrono::steady_clock::time_point end{};
		Task tasks[MAXEVENTS];

	public:
		TimedTask(){}
		void startClock();
		void stopClock();
		void addTask(const char* tName);
		friend std::ostream& operator<<(std::ostream& ostr,const TimedTask& timedTask);
	};
}
#endif // !SDDS_TIMEDTASK_H
