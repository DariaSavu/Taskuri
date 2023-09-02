#include "TaskuriGUI.h"
#include <QtWidgets/QApplication>
#include "Teste.h"
#include "Service.h"
int main(int argc, char *argv[])
{
   //testAll();
   QApplication a(argc, argv);
   Repo r("taskuri.txt");
   Validator val(r);
   Service s(r, val);
   TaskuriGUI w(s);
   return a.exec();
}
