#ifndef Licht_h
#define Licht_h

#include "Arduino.h"
///
/// @package : Licht
/// LED-Lichtsteuerung für Arduino.
///
/// @author Borys 30 28 Jul 2019
/// @note licht.h
///

/** Basisklasse.
 * eine LED an einem Arduino-Pin 
 *
 */
class Licht
{
private:
protected:
	unsigned long Dauer;
	/** verwendeter Arduino-Pin */
	int Pin;
	/** LED an oder aus*/
	bool istAn;
public:
	/** LED an Pin vereinbaren.
	* Pin-Nummer wird gespeichert, als Ausgabe vereinbart und ausgeschaltet
	* @param pPin die Nummer
	*/
	Licht(int pPin);
	/** LED ausschalten. */
	aus();
	/** LED einschalten. */
	ein();
	/** LED schalten.
	 * @param p true für ein, false für aus
	 */
	setzen(bool p);
	/** blinkt 22 mal langsamer werdend, dann aus.
	@note blocking für etwa 8 Sekunden
	*/
	weg();
	/** blinkt 22 mal schneller werdend, dann an.
	@note blocking für etwa 8 Sekunden
	*/
	hin();
};
/** Klasse für analog angesteuerte LED.
 * eine LED an einem Arduino-Pin, Helligkeit einstellbar 
 *
 *
 */
class ALicht : public Licht
{
private:
	/** für physiologische Helligkeitsrampe.*/
	const float PHYSVAL = (-3);
	/** aktueller Zustand*/
	enum Status { stAus, /**< ist ganz aus*/
		stHeller, /**< wird heller*/
		stZwischen, /**< steht zwischen an und aus*/
		stDunkler, /**< wird dunkler*/
		stEin /**< ist ganz an*/
	} Stat;
	/** aktueller analoger Wert*/
	int Wert;
	/** Grenzen für Änderung*/
	int Von,Bis;
	unsigned long jetzt, Start, Ende;
public:
	ALicht(int pPin) ;
	void aus();
	void wechsel();
	void setzen(int pWert);
	void halb();
	void ein();
	bool check();
	void heller(int von, int bis, long dauer);
	void dunkler(int von, int bis, long dauer);
	void heller(long dauer) {heller(0, 255, dauer);};
	void dunkler(long dauer) {dunkler(255, 0, dauer);};
};
/** Klassse für Blinklicht.
 * Parameter: Dauer für an und aus
 */
class BLicht : public Licht
{
private:
	/** augenblicklicher Zustand */
	enum Status {
		stAus, /**< ist konstant aus*/
		stBlink, /**< blinkt mit den eingestellten Parametern*/
		stEin /** ist konstant an*/
	} Stat;
	/** Zeiten*/
	unsigned long wechsel, Tan, Taus;
public:
	void set(int pTan, int pTaus);
	void set(int pTan, int pTaus, int pW);
	BLicht(int pPin, int pTan, int pTaus);
	void blinken(bool pAn);
	void check();
};
/** Klassse für Leuchtstoffröhre.
 * Parameter: Dauer für an und aus
 */
class LLicht : public Licht
{
private:
	/** augenblicklicher Zustand */
	enum Status {
		stAus, /**< ist konstant aus*/
		stZ1,stZ2,stZ3,stZ4,stZ5,stZ6, /**< zünden*/
		stEin /**< ist konstant an*/
	} Stat;
	/** Zeiten*/
	unsigned long Wechsel, Ein1, Aus2, Ein3, Aus4,Ein5,Aus6;
	const unsigned long EIN10 = 20, EIN11 = 5 * EIN10, EIN30 = 200, EIN31 = 7 * EIN30;
	const unsigned long AUS20 = 200, AUS21 = 3 * AUS20, AUS40 = 400, AUS41 = 3 * AUS20;
public:
	LLicht(int pPin);	
	void aus();
	void ein();
	void check();
};
#endif