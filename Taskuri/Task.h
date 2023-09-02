#pragma once
#include <iostream>
#include <vector>
using std::string;
using std::vector;
class Task
{
private:
	int id;
	string descriere;
	vector<string>programatori;
	string stare;
public:
	//constructor
	Task(int _id, const string _descriere, const vector<string> _programatori, const string _stare) :
		id{ _id }, descriere{ _descriere }, programatori{ _programatori }, stare{ _stare } {};
	//constructor de copiere
	Task(const Task& ot) :
		id{ ot.id }, descriere{ ot.descriere }, programatori{ ot.programatori }, stare{ ot.stare } {};

	//getere pentru atributele taskului
	int getId() const;
	const string& getDescriere() const;
	const vector<string>& getProgramatori() const;
	const string& getStare() const;
	string printProgramatori() const;
	void changeState(string s)
	{
		stare = s;
	}
	~Task()=default;

};