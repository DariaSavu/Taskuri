#include "Service.h"
#include <algorithm>
bool compare(Task a, Task b)
{
	return a.getStare() < b.getStare();
}
void Service::addService(int id,const string& descriere,vector<string>programatori,const string& stare)
{
	Task t{ id,descriere,programatori,stare };
	string result = val.validate(t);
	if (result != "")
	{
		throw std::invalid_argument(result);
	}
	repo.addRepo(t);
}
vector<Task> Service::getAllService()
{
	vector<Task>elems = this->repo.getAll();
	sort(elems.begin(), elems.end(), compare);
	return elems;
}
bool match(string s1, string s2)
{
	int k= 0;
	bool gasit;
	for (int i = 0; i < s1.size(); i++)
	{
		k = 0;
		for (int j = i; j < s1.size(); j++)
		{
			if (s1[j] != s2[k]) break;
			k++;
		}
		if (k == s2.size()) return true;
	}
	return false;
}
void Service::changeState(string s,const string& stare)
{
	repo.changeStateRepo(s,stare);
}
vector<Task> Service::filtrare(const string& flt)
{
	vector<Task>elems;
	for (auto el : repo.getAll())
	{
		string t = el.printProgramatori();
		if(match(t,flt))
		{
			elems.push_back(el);
		}
	}
	sort(elems.begin(), elems.end(), compare);
	return elems;
}