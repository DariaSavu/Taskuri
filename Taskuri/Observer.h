#pragma once
#include <vector>
using std::vector;
class Observer
{
public:
	virtual void update() = 0;
};
class Observable
{
private:
	vector<Observer*>obs;
public:
	void addObserver(Observer* ob)
	{
		obs.push_back(ob);
	}
	void notify()
	{
		for (auto el : obs)
			el->update();
	}
};