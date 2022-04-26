// Name: Ashwin Anand
// Seneca Student ID: 152042206
// Seneca email: aanand24@myseneca.ca
// Date of completion: 06-04-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include"LineManager.h"

namespace sdds
{
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		
		std::ifstream ipFile(file);
		std::string row = "";
		Utilities utils{};
		bool more = true;
		size_t next_pos = 0u;
		std::string tokens[2]{ "","" };
		std::vector<Workstation*>::iterator itr;
		
		bool isNextStation = false, foundFirst = false;
		Workstation* firstOneMightBe{};

		do
		{
			std::getline(ipFile, row);
			if (ipFile)
			{
				tokens[0] = utils.extractToken(row, next_pos, more);

				if (more)
					tokens[1] = utils.extractToken(row, next_pos, more);

				auto i = std::find_if(stations.begin(), stations.end(), [=](const Workstation* ws)
					{
						return tokens[0] == ws->getItemName();
					});
				m_activeLine.push_back(stations[i - stations.begin()]);
			}
			next_pos = 0u;
			more = true;
			row = "", tokens[0] = "", tokens[1] = "";
		} while (ipFile);

		ipFile.clear();
		ipFile.seekg(std::ios::beg);
		do
		{
			std::getline(ipFile, row);

			if (ipFile)
			{
				tokens[0] = utils.extractToken(row, next_pos, more); 

				if(more)
					tokens[1] = utils.extractToken(row, next_pos, more);
				
				
				if (tokens[1] != "")
				{
					itr = std::find_if(m_activeLine.begin(), m_activeLine.end(), [=](const Workstation* ws)
						{
							return tokens[1] == ws->getItemName();
						});
				}
				std::for_each(m_activeLine.begin(), m_activeLine.end(), [=](Workstation* ws)
					{
						if (tokens[0] == ws->getItemName() && tokens[1] != "")
						{
							ws->setNextStation(m_activeLine[itr - m_activeLine.begin()]);
						}
						
					});

				
				
				next_pos = 0u;
				more = true;
				tokens[0] = "";
				tokens[1] = "";
			}
		} while (ipFile);

		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws1)
			{
				if (!foundFirst)
				{
					std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* ws2)
						{
							if (ws2->getNextStation() && !isNextStation)
							{
								if ((ws1->getItemName() == ws2->getNextStation()->getItemName()))
								{
									isNextStation = true;
								}
							}
						});

					if (isNextStation == false)
					{
						firstOneMightBe = ws1;
						foundFirst = true;
					}
				}
				isNextStation = false;
			});

		m_firstStation = firstOneMightBe;
		m_cntCustomerOrder = g_pending.size();
	}

	void LineManager::reorderStations()
	{
		size_t size = m_activeLine.size();
		std::vector<Workstation*> ordered_workstations{};
		ordered_workstations.push_back(m_firstStation);
		Workstation* currWorkstation{}, *nextStation{};
		for (size_t i = 0; i < size; i++)
		{
			currWorkstation = ordered_workstations.back();
			if (currWorkstation->getNextStation())
			{
				nextStation = currWorkstation->getNextStation();
				ordered_workstations.push_back(nextStation);
			}
		}

		m_activeLine = ordered_workstations;
	}

	bool LineManager::run(std::ostream& os)
	{
		static int tracker = 1;
		
		os << "Line Manager Iteration: " << tracker << "\n";
		if (!g_pending.empty())
		{
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}
			

		for (auto& station : m_activeLine)
		{
			station->fill(os);
		}
		for(auto& station : m_activeLine)
		{
			station->attemptToMoveOrder();
		}
		size_t c_size = g_completed.size();
		size_t ic_size = g_incomplete.size();
		size_t t_size = c_size + ic_size;
		tracker++;
		return t_size == m_cntCustomerOrder;
	}

	void LineManager::display(std::ostream& os)const
	{
		for (auto& station : m_activeLine)
			station->display(os);
	}
}