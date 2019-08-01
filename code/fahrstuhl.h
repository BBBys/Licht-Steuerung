#pragma once
#ifndef fahrstuhl_h
#define fahrstuhl_h
#include <licht.h>
class Fahrstuhl
{
public:
	Fahrstuhl(ALicht *L1, ALicht *L2, Licht *T);
	~Fahrstuhl();
	bool check();
	void start();
	void start(unsigned long pWarten);
private:
	ALicht *L1, *L2;
	Licht *T;
	const unsigned long ZEIT = 5000;
	unsigned long Wechsel;
	/** augenblicklicher Zustand */
	enum Status {
		stUnten, /**< in Ruhe unten*/
		stStart, /**< startet gleich*/
		stHoch1, stHoch2, stHoch3, stHoch4, /**< fährt hoch*/
		stOben, stRunter1, stRunter2, stRunter3, stRunter4,stWarten
	} Stat,altStat;
};
#endif // !fahrstuhl_h
