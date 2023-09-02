#pragma once
#include "Repo.h"
#include "Validator.h"
#include "Observer.h"
class Service:public Observable
{
	Repo& repo;
	Validator& val;
public:
	Service(Repo& _repo, Validator& _val) :repo{ _repo }, val{ _val } {};
	/// <summary>
	/// Adauga un task in lista curenta
	/// </summary>
	/// <param name="id">id-ul curent</param>
	/// <param name="descriere">descriere</param>
	/// <param name="programatori">lista de programatori</param>
	/// <param name="stare">starea</param>
	void addService(int id, const string& descriere, vector<string>programatori, const string& stare);
	/// <summary>
	/// Returneaza lista de taskuri
	/// </summary>
	/// <returns></returns>
	vector<Task> getAllService();
	/// <summary>
	/// Filtreaza 
	/// </summary>
	/// <param name="flt"></param>
	/// <returns></returns>
	vector<Task>filtrare(const string& flt);
	void changeState(string s,const string& stare);
	~Service() = default;
};
