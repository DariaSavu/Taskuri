#include "Teste.h"
#include <assert.h>
#include "Repo.h"
#include "Service.h"
void testDomain()
{
	Task t1{ 12,"Creare proiect",{"Andrei_Alina","Matei_Matei"},"open" };
	assert(t1.getDescriere() == "Creare proiect");
	assert(t1.getProgramatori().size() == 2);
	assert(t1.getId() == 12);
	assert(t1.getStare() == "open");
	assert(t1.printProgramatori() == "Andrei_Alina Matei_Matei ");
}
void testRepo()
{
	Task t1{ 12,"Creare proiect",{"Andrei_Alina","Matei_Matei"},"open" }; 
	Task t2{ 15,"Modificare proiect",{"Andrei_Alina","Matei_Matei"},"inprogress" };
	std::ofstream myfile;
	myfile.open("test.txt");
	myfile.close();
	Repo r("teste.txt");
	r.addRepo(t1);
	r.addRepo(t2);
	assert(r.getAll().size() == 2);

}
void testService()
{
	Task t1{ 12,"Creare proiect",{"Andrei_Alina","Matei_Matei"},"open" };
	Task t2{ 15,"Modificare proiect",{"Andrei_Alina","Matei_Matei"},"inprogress" };
	Task t3{ 1," proiect",{"Programator1","Programator2"},"closed" };
	std::ofstream myfile;
	myfile.open("test.txt");
	myfile.close();
	Repo r("teste.txt");
	r.addRepo(t1);
	r.addRepo(t2);
	r.addRepo(t3);
	Validator val(r);
	Service s(r, val);
	assert(s.getAllService().size() == 3);
	try
	{
		s.addService(12, "Creare proiect", { "Andrei_Alina","Matei_Matei" }, "open");
		assert(false);
	}
	catch (...)
	{
		assert(true);
	}
	try
	{
		s.addService(17, "Creare proiect", { "Andrei_Alina","Matei_Matei" }, "open");
		assert(true);
	}
	catch (...)
	{
		assert(false);
	}
}
void testAll()
{
	testDomain();
	testRepo();
	testService();
}