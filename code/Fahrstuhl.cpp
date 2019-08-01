#include "fahrstuhl.h"


Fahrstuhl::Fahrstuhl(ALicht *pL1, ALicht *pL2,Licht *pT)
{
	L1 = pL1;
	L2 = pL2;
	T = pT;
	Stat = stUnten;
}

Fahrstuhl::~Fahrstuhl()
{
}
bool Fahrstuhl::check()
{
	bool rtn = false;
	switch (Stat)
	{
	case Fahrstuhl::stUnten:
		break;
	case Fahrstuhl::stStart:
		break;
	case Fahrstuhl::stHoch1:
		if (L1->check())
		{
			L1->wechsel();
			Stat = stHoch2;
		}
		break;
	case Fahrstuhl::stHoch2:
		if (L1->check())
		{
			L1->aus();
			L2->heller(ZEIT);
			Stat = stHoch3;
		}
		break;
	case Fahrstuhl::stHoch3:
		if (L2->check())
		{
			L2->wechsel();
			Stat = stHoch4;
		}
		break;
	case Fahrstuhl::stHoch4:
		if (L2->check())
		{
			L2->aus();
			Stat = stOben;
			T->ein();
			rtn = true;
		}
		break;
	case Fahrstuhl::stWarten:
		unsigned long jetzt;
		jetzt = millis();
		if (jetzt > Wechsel)
		{
			Stat = altStat;
			start();
		}	
	case Fahrstuhl::stRunter1:
		if (L2->check())
		{
			L2->wechsel();
			Stat = stRunter2;
		}
		break;
	case Fahrstuhl::stRunter2:
		if (L2->check())
		{
			L2->aus();
			L1->heller(ZEIT);
			Stat = stRunter3;
		}
		break;
	case Fahrstuhl::stRunter3:
		if (L1->check())
		{
			L1->wechsel();
			Stat = stRunter4;
		}
		break;
	case Fahrstuhl::stRunter4:
		if (L1->check())
		{
			L1->aus();
			Stat = stUnten;
			rtn = true;
		}
		break;
	
	
	case Fahrstuhl::stOben:
		break;
	default:
		break;
	}
	return rtn;
}
void Fahrstuhl::start(unsigned long pWarten)
{
	altStat = Stat;
	Stat = stWarten;
	Wechsel = millis() + pWarten;
}
void Fahrstuhl::start()
{
	switch (Stat)
	{
	case Fahrstuhl::stUnten:
		L1->heller(ZEIT);
		Stat = stHoch1;
		break;
	case Fahrstuhl::stOben:
		Stat = stRunter1;
		T->aus();
		L2->heller(ZEIT);
		break;
	default:
		break;
	}
}