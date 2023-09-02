#include "Task.h"

int Task::getId() const
{
	return this->id;
}
const string& Task::getDescriere() const
{
	return this->descriere;
}
const vector<string>& Task::getProgramatori() const
{
	return this->programatori;
}
const string& Task::getStare() const
{
	return this->stare;
}
string Task::printProgramatori() const
{
	string s;
	for (auto el : programatori)
	{
		s.append(el);
		s.append(" ");
	}
	return s;
}