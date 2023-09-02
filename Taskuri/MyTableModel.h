#include "Repo.h"
#include <qtableview.h>
class MyTableModel :public QAbstractTableModel
{
private:
	vector<Task>& taskuri;
public:
	MyTableModel(vector<Task> t) :taskuri{ t } {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
			return taskuri.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return 4;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
	{
		if (!index.isValid() || index.row() >= taskuri.size())
			return QVariant();
		int row = index.row();
		int column = index.column();
		if (role == Qt::DisplayRole)
		{
			Task t = taskuri[row];
			if (column == 0)
				return t.getId();
			if (column == 1)
				return QString::fromStdString(t.getDescriere());
			if (column == 2)
				return QString::fromStdString(t.getStare());
			if (column == 3)
				return t.getProgramatori().size();
			return QVariant();


		}
	}
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole)
	{
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal)
			{
				if (section == 0)
					return "Id";
				if (section == 1)
					return "Descriere";
				if (section == 2)
						return "Stare";
				if (section == 3)
					return "Numar programatori";
			}
		}
		return QVariant();
	}
	Qt::ItemFlags flags(const QModelIndex& index) const
	{
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	}
	void setData(vector<Task> t)
	{
		this->taskuri = t;
		emit layoutChanged();
	}
};
