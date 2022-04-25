//Name - Ashwin Anand
//email - aanand24@myseneca.ca
//student id - 152042206
//date - 2022/03/17
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#include"CovidCollection.h"
namespace sdds
{
	void removeSpecificChars(std::string& target, char toBeRemoved)
	{
		target.erase(0, target.find_first_not_of(toBeRemoved));
		target.erase(target.find_last_not_of(toBeRemoved) + 1);
	}


	CovidCollection::CovidCollection(std::string fileName)
	{
		std::string row = "", year_ ="", n_cases="", n_deaths="", country="", city="", variant="";
		size_t rowCounter{}, pos = 25, nextpos{};
		int year{};
		std::ifstream file(fileName);
		if (!file)
			throw "File does not exist!";
		else
		{
			do
			{
				std::getline(file, row);
				if (file)
				{
					rowCounter++;
				}
			} while (file);


			file.clear();
			file.seekg(std::ios::beg);
			std::vector<Covid> covid_collection(rowCounter);
			covidCollection = covid_collection;
			for (auto i = 0u; i < rowCounter; i++)
			{
				if (file)
				{
					std::getline(file, row);

					country = row.substr(0, pos);
					removeSpecificChars(country, ' ');
					city = row.substr(pos, pos);
					removeSpecificChars(city, ' ');

					nextpos = pos + 25;
					variant = row.substr(nextpos, pos);
					removeSpecificChars(variant, ' ');

					nextpos += pos;
					year_ = row.substr(nextpos, 5);
					removeSpecificChars(year_, ' ');

					nextpos = nextpos + 5;
					n_cases = row.substr(nextpos, 5);
					removeSpecificChars(n_cases, ' ');

					nextpos = nextpos + 5;
					n_deaths = row.substr(nextpos);
					removeSpecificChars(n_deaths, ' ');

					covidCollection[i].country = country;
					covidCollection[i].city = city;
					covidCollection[i].variant = variant;
					year = stoi(year_);
					if (year < 0)
						covidCollection[i].year = 0;
					else 
						covidCollection[i].year = year;

					covidCollection[i].nCases = stoi(n_cases);
					covidCollection[i].m_deaths = stoi(n_deaths);
				}
			}

		}

	}
	void CovidCollection::display(std::ostream& out)
	{
		int n_cases{0}, n_deaths{0}; 
		for_each(covidCollection.begin(), covidCollection.end(), [&](Covid covid)
			{
				out << covid  << "\n";

				if (!n_cases && !n_deaths)
				{
					int nCases_ = std::accumulate(covidCollection.begin(), covidCollection.end(), (int)0, [](int x, Covid y)
						{
							return x + y.nCases;
						});
					int nDeaths_ = std::accumulate(covidCollection.begin(), covidCollection.end(), (int)0, [](int x, Covid y)
						{
							return x + y.m_deaths;
						});
					n_cases = nCases_;
					n_deaths = nDeaths_;
				}
			});

		out.width(89);
		out.fill('-');
		out << "\n";
		out.fill(' ');
		out << "|";
		out.width(80);
		out << "Total Cases Around the World:  ";
		out << n_cases << " |\n";
		out << "|";
		out.width(80);
		out << "Total Deaths Around the World:  ";
		out << n_deaths << " |\n";
	}

	void CovidCollection::sort(std::string orderBy)
	{
			if (orderBy == "country")
				std::sort(covidCollection.begin(), covidCollection.end(), [](const Covid covid1, const Covid covid2)
					{
						return covid1.country < covid2.country;
					});
			else if (orderBy == "variant")
				std::sort(covidCollection.begin(), covidCollection.end(), [](const Covid covid1, const Covid covid2)
					{
						return covid1.variant < covid2.variant;
					});
			else if (orderBy == "cases")
				std::sort(covidCollection.begin(), covidCollection.end(), [](const Covid covid1, const Covid covid2)
					{
						return covid1.nCases < covid2.nCases;
					});
			else
				std::sort(covidCollection.begin(), covidCollection.end(), [](const Covid covid1, const Covid covid2)
					{
						return covid1.m_deaths < covid2.m_deaths;
					});
		
	}

	void CovidCollection::cleanList()
	{
		std::vector<Covid> covid_collection(covidCollection.size());
		
		std::transform(covidCollection.begin(), covidCollection.end(), covid_collection.begin(), [](Covid covid)
			{
				if (covid.variant == "[None]")
					covid.variant = " ";
				return covid;
			});
		covidCollection = covid_collection;
	}

	bool CovidCollection::inCollection(std::string variant) const
	{
		bool inCollection = std::any_of(covidCollection.begin(), covidCollection.end(), [=](const Covid& covid) {return (covid.variant == variant);});
		return inCollection;
	}

	std::list<Covid> CovidCollection::getListForVariant(std::string variant) const
	{
		int size = std::count_if(covidCollection.begin(), covidCollection.end(), [=](Covid covid)
			{
				return covid.variant == variant;
			});
		std::list<Covid> covidCollectionByVariant(size);
		std::copy_if(covidCollection.begin(), covidCollection.end(), covidCollectionByVariant.begin(), [=](const Covid covid)->bool{return (covid.variant == variant);});

		return covidCollectionByVariant;
	}

	std::ostream& operator<<(std::ostream& out, const Covid& theCovid)
	{
		out << "| ";
		out.width(20);
		out.setf(std::ios::left, std::ios::adjustfield); // why it does not work out by only using left

		out << theCovid.country;
		out.unsetf(std::ios::left);

		out << "  | ";
		out.width(15);
		out.setf(std::ios::left, std::ios::adjustfield);
		out << theCovid.city;
		out.unsetf(std::ios::left);
		out << " | ";
		out.width(20);
		out.setf(std::ios::left, std::ios::adjustfield);
		out << theCovid.variant;
		out.unsetf(std::ios::left);
		out << " | ";

		out.width(6);
		if (theCovid.year == 0)
		{
			out << "";
		}
		else
		{
			out << theCovid.year;
		}
		out << " |";
		out.width(5);
		out << theCovid.nCases;
		out << " |";
		out.width(4);
		out << theCovid.m_deaths;
		out << " |";
		
		return out;
	}
}