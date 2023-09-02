#pragma once
#include "Task.h"
#include <fstream>
class Repo
{
private:
	string fileName;
	vector<Task>taskuri;
	void loadFromFile();
	void saveToFile();
public:
	Repo(const string& _fileName) :fileName{ _fileName } { this->loadFromFile(); };
	void addRepo(const Task& t);
	void changeStateRepo(string s,const string& stare);
	const vector<Task>& getAll();
	~Repo()=default;

};