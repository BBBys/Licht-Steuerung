///
/// @package : Licht
/// LED-Lichtsteuerung für Arduino.
///
/// @author Borys 28 Jul 2019
/// @note licht.h
///
#include "Licht.h"
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
    Licht(int pPin)
    {
      Pin = pPin;
      pinMode(Pin, OUTPUT);
      digitalWrite(Pin, LOW);
      istAn = false;
    }
	/** LED ausschalten. */
    aus()
    {
      digitalWrite(Pin, LOW);
      istAn = false;
    }
	/** LED einschalten. */
    ein()
    {
      digitalWrite(Pin, HIGH);
      istAn = true;
    }
	/** LED schalten.
	 * @param p true für ein, false für aus 
	 */
    setzen(bool p)
    {
      if (p)ein();
      else aus();
    }
	/** blinkt 22 mal langsamer werdend, dann aus. 
	@note blocking für etwa 8 Sekunden
	*/
    weg()
    {
      int d;
      for (d = 500; d > 50; d = d - 20)
      {
        aus();
        delay(75);
        ein();
        delay(d);
      }
      aus();
    }
	/** blinkt 22 mal schneller werdend, dann an. 
	@note blocking für etwa 8 Sekunden
	*/
    hin()
    {
      int d;
      for (d = 50; d < 500; d = d + 20)
      {
        ein();
        delay(d);
        aus();
        delay(75);
      }
      ein();
    }
};
/** Klasse für analog angesteuerte LED.
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
    ALicht(int pPin): Licht(pPin)
    {
      Stat = stAus;
      Wert=0;
       analogWrite(Pin, Wert);
    }
  aus()
    {
      Stat = stAus;
      check();
      istAn = false;
    }
     setzen(int pWert)
    {
      Stat = stZwischen;
      Wert=pWert;
      check();
      }
     halb()
    {
      setzen(99);
      }
    ein()
    {
      Stat = stEin;
      check();
      istAn = true;
    }
    void check()
    {
      switch (Stat)
      {
        case stAus:
          Wert = 0;
          break;
        case stEin:
          Wert = 255;
          break;
      }
      analogWrite(Pin, Wert);
    }
};
class BLicht : Licht
{
  private:
    enum Status {stAus, stBlink, stEin} Stat;

    unsigned long wechsel, Tan, Taus;
  public:
    set(int pTan, int pTaus)
    {
      set(pTan, pTaus, 0);
    }
    set(int pTan, int pTaus, int pW)
    {
      Tan = pTan;
      Taus = pTaus;
      wechsel = millis() + pW;
      istAn = false;
      digitalWrite(Pin, istAn);
    }
    BLicht(int pPin, int pTan, int pTaus): Licht(pPin)
    {
      Tan = pTan;
      Taus = pTaus;
      wechsel = 0;
      Stat = stAus;
    }
    blinken(bool pAn)
    {
      if (pAn)Stat = stBlink;
      else
      {
        Stat = stAus;
        digitalWrite(Pin, LOW);
      }
    }
    check()
    {
      if (Stat = stBlink)
      {
        unsigned long jetzt;
        jetzt = millis();
        if (jetzt > wechsel)
        {
          istAn = !istAn;
          digitalWrite(Pin, istAn);
          wechsel = istAn ? jetzt + Tan : jetzt + Taus;
        }
      }
    }
};
