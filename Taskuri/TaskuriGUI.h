#pragma once
#include <qwidget.h>
#include <qtablewidget.h>
#include "Service.h"
#include <qlayout.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qtextlist.h>
#include <qmessagebox.h>
#include <qlistwidget.h>
class Ferestre :QWidget,public Observer
{
private:
	string stare;
	Service& s;
	QListWidget* lista = new QListWidget;
	QPushButton* open = new QPushButton("&Open");
	QPushButton* closed = new QPushButton("&Closed");
	QPushButton* inProgress = new QPushButton("&InProgress");
	QHBoxLayout* general = new QHBoxLayout;
public:
	Ferestre(const string& _stare, Service& _s) : stare{ _stare }, s{ _s } { initializare(); reloadList(); connectSignals(); this->show(); };
	void initializare()
	{
		this->setLayout(general);
		general->addWidget(lista);
		general->addWidget(open);
		general->addWidget(closed);
		general->addWidget(inProgress);
	}
	void connectSignals()
	{
		QObject::connect(open, &QPushButton::clicked, [&]()
			{
				auto el=lista->selectedItems().at(0)->text();
				s.changeState(el.toStdString(),"open");
				s.notify();
			});
		QObject::connect(closed, &QPushButton::clicked, [&]()
			{
				auto el = lista->selectedItems().at(0)->text();
				s.changeState(el.toStdString(),"closed");
				s.notify();
			});
		QObject::connect(inProgress, &QPushButton::clicked, [&]()
			{
				auto el = lista->selectedItems().at(0)->text();
				s.changeState(el.toStdString(),"inprogress");
				s.notify();
			});
	}
	void update() override
	{
		reloadList();
	}
	void reloadList()
	{
		vector<Task>t = s.getAllService();
		lista->clear();
		for (auto& el : t)
		{
			if (el.getStare() == stare)
				lista->addItem(new QListWidgetItem(QString::fromStdString(std::to_string(el.getId()) +" "+ el.getDescriere() + " " + el.getStare() + " " + el.printProgramatori())));
		}
	}
};
class TaskuriGUI :QWidget
{
private:
	Q_OBJECT
	Service& s;
	QTableWidget* tabelTaskuri = new QTableWidget(0,4);
	QHBoxLayout* general = new QHBoxLayout;
	QLineEdit* id = new QLineEdit;
	QLineEdit* descriere = new QLineEdit;
	QLineEdit* stare = new QLineEdit;
	QLineEdit* programatori=new QLineEdit;
	QFormLayout* form = new QFormLayout;
	QVBoxLayout* vertical = new QVBoxLayout;
	QLabel* filtru=new QLabel("Filtrare:");
	QLineEdit* filtrare = new QLineEdit;
	QPushButton* adauga = new QPushButton("&Adauga");

public:
	void reloadTabel(vector<Task>t)
	{
		int max = tabelTaskuri->rowCount();
		for (int i = max - 1; i >= 1; i--)
			tabelTaskuri->removeRow(i);
		int rc = 1;
		for (auto& el : t)
		{
			tabelTaskuri->insertRow(rc);
			tabelTaskuri->setItem(rc, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(el.getId()))));
			tabelTaskuri->setItem(rc, 1, new QTableWidgetItem(QString::fromStdString(el.getDescriere())));
			tabelTaskuri->setItem(rc, 2, new QTableWidgetItem(QString::fromStdString(el.getStare())));
			tabelTaskuri->setItem(rc, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(el.getProgramatori().size()))));
			rc++;
		}
	}
	void initializeComponents()
	{
		general->addWidget(tabelTaskuri);
		general->addLayout(vertical);
		vertical->addLayout(form);
		vertical->setAlignment(Qt::AlignTop);
		form->addRow("Id", id);
		form->addRow("Descriere", descriere);
		form->addRow("Stare", stare);
		form->addRow("Programatori", programatori);
		vertical->addWidget(adauga);
		vertical->addWidget(filtru);
		vertical->addWidget(filtrare);
		this->setLayout(general);
	}
	void connectSignals()
	{
		QObject::connect(adauga, &QPushButton::clicked, [&]()
			{
				int Id;
				string Descriere;
				vector<string>Programs;
				string Stare;
				string Toti;
				Id = id->text().toInt();
				Descriere = descriere->text().toStdString();
				Stare = stare->text().toStdString();
				Toti = programatori->text().toStdString();
				string c="";
				for (int i = 0; i < Toti.size(); i++)
				{
					if(Toti[i]!=';') c.push_back(Toti[i]);
					else
					{
						Programs.push_back(c);
						c = "";
					}
				}
				try
				{
					s.addService(Id, Descriere, Programs, Stare);
					reloadTabel(s.getAllService());
				}
				catch (std::exception& e)
				{
					QMessageBox* b = new QMessageBox;
					b->setText(QString::fromStdString(e.what()));
					b->show();
				}

			});
		QObject::connect(filtrare, &QLineEdit::textEdited, [&]()
			{
				string flt = filtrare->text().toStdString();
				reloadTabel(s.filtrare(flt));
			});
	}
	TaskuriGUI(Service& _s) :s{ _s }
	{
		initializeComponents();
		tabelTaskuri->insertRow(0);
		QTableWidgetItem* it = new QTableWidgetItem("Id");
		tabelTaskuri->setItem(0, 0, it);
		tabelTaskuri->setItem(0, 1,new QTableWidgetItem("Descriere"));
		tabelTaskuri->setItem(0, 2,new QTableWidgetItem("Stare"));
		tabelTaskuri->setItem(0, 3,new QTableWidgetItem("Nr programatori"));
		reloadTabel(s.getAllService());
		Ferestre* openF = new Ferestre("open", s);
		Ferestre* closedF = new Ferestre("closed", s);
		Ferestre* inprogressF = new Ferestre("inprogress", s);
		s.addObserver(openF);
		s.addObserver(closedF);
		s.addObserver(inprogressF);
		connectSignals();
		this->show();
	};

};

