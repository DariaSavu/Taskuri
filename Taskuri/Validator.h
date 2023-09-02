#pragma once
#include "Repo.h"
class Validator
{
	Repo& r;
public:
	Validator(Repo& repo) :r{ repo } {};
	string validate(const Task& t);
	~Validator() = default;
};