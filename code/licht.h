#ifndef Licht_h
#define Licht_h

#include "Arduino.h"
///
/// @package : Licht
/// LED-Lichtsteuerung f�r Arduino.
///
/// @author Borys 28 Jul 2019
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
	 * @param p true f�r ein, false f�r aus 
	 */
    setzen(bool p);
	/** blinkt 22 mal langsamer werdend, dann aus. 
	@note blocking f�r etwa 8 Sekunden
	*/
    weg();
	/** blinkt 22 mal schneller werdend, dann an. 
	@note blocking f�r etwa 8 Sekunden
	*/
    hin();
};
/** Klasse f�r analog angesteuerte LED.
 * eine LED an einem Arduino-Pin, Helligkeit einstellbar 
 *
 *
 */
class ALicht : public Licht
{
  private:
  /** aktueller Zustand*/
    enum Status {stAus, stHeller, stZwischen,stDunkler, stEin} Stat;
int Wert;
    unsigned long wechsel, Tan, Taus;
  public:
    ALicht(int pPin): Licht(pPin);
  aus();
     setzen(int pWert);
     halb();
    ein();
    void check();
};
class BLicht : Licht
{
  private:
    enum Status {stAus, stBlink, stEin} Stat;
    unsigned long wechsel, Tan, Taus;
  public:
    set(int pTan, int pTaus);
    set(int pTan, int pTaus, int pW);
    BLicht(int pPin, int pTan, int pTaus): Licht(pPin);
    blinken(bool pAn);
    check();
};
#endif