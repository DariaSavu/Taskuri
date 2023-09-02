#include "Repo.h"
#include <string>

void Repo::loadFromFile()
{
	std::ifstream myfile;
	myfile.open(fileName);
	if (!myfile.is_open())
		throw std::exception();
	int id;
	string descriere;
	vector<string>prg;
	string stare;
	string citeste;
	while (!myfile.eof())
	{
		myfile >> id >> descriere;
		myfile >> citeste;
		while (citeste != "open" && citeste != "closed" && citeste != "inprogress")
		{
			prg.push_back(citeste);
			myfile >> citeste;
		}
		stare = citeste;
		Task t(id, descriere, prg, stare);
		this->taskuri.push_back(t);
		prg.clear();
	}
	myfile.close();
}
void Repo::changeStateRepo(string s,const string& stare)
{
	for (auto& el : taskuri)
	{
		
		string m = std::to_string(el.getId()) + " " + el.getDescriere() + " " + el.getStare() + " " + el.printProgramatori();
		if (m == s)
		{
			el.changeState(stare);
		}
		
	}
}
void Repo::saveToFile()
{
	std::ofstream myfile;
	myfile.open(fileName);
	if (!myfile.is_open())
		throw std::exception();
	if (this->taskuri.empty())
		return;
	Task t = taskuri[0];
	myfile << t.getId() << " " << t.getDescriere() <<" "<< t.printProgramatori() << t.getStare();
	for (int i = 1; i < taskuri.size(); i++)
	{
		t = taskuri[i];
		myfile <<'\n'<< t.getId() << " " << t.getDescriere() <<" "<< t.printProgramatori() << t.getStare();
	}
	myfile.close();
}
const vector<Task>& Repo::getAll()
{
	return taskuri;
}
void Repo::addRepo(const Task& t)
{
	taskuri.push_back(t);
	saveToFile();
}