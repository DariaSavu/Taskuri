#include "Validator.h"

string Validator::validate(const Task& t)
{
	string msg="";
	for (auto& el : r.getAll())
	{
		if (el.getId() == t.getId())
		{
			msg.append("Exista deja un task cu acest id!\n");
			break;
		}
	}
	if (t.getDescriere() == "")
		msg.append("Descrierea nu poate fi vida\n");
	if (t.getProgramatori().size() < 1 || t.getProgramatori().size() > 4)
		msg.append("Un task are minim 1 si maxim 4 programatori care lucreaza la el!\n");
	if (t.getStare() != "open" && t.getStare() != "closed" && t.getStare() != "inprogress")
		msg.append("Un task poate fi open, in progress sau closed!\n");
	return msg;
}