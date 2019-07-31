///
/// @package : Licht
/// LED-Lichtsteuerung für Arduino.
///
/// @author Borys 30 28 Jul 2019
/// @note licht.cpp
///
#include "Licht.h"

Licht::Licht(int pPin)
	{
		Pin = pPin;
		pinMode(Pin, OUTPUT);
		digitalWrite(Pin, LOW);
		istAn = false;
	}
	/** LED ausschalten. */
	Licht::aus()
	{
		digitalWrite(Pin, LOW);
		istAn = false;
	}
	/** LED einschalten. */
	Licht::ein()
	{
		digitalWrite(Pin, HIGH);
		istAn = true;
	}
	/** LED schalten.
	 * @param p true für ein, false für aus
	 */
	Licht::setzen(bool p)
	{
		if (p)ein();
		else aus();
	}
	/** blinkt 22 mal langsamer werdend, dann aus.
	@note blocking für etwa 8 Sekunden
	*/
	Licht::weg()
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
	Licht::hin()
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

void BLicht::set(int pTan, int pTaus)
	{
		set(pTan, pTaus, 0);
	}
	void BLicht::set(int pTan, int pTaus, int pW)
	{
		Tan = pTan;
		Taus = pTaus;
		wechsel = millis() + pW;
		istAn = false;
		digitalWrite(Pin, istAn);
	}
	/** LED an Pin und Blinkzeiten vereinbaren.
* Pin-Nummer wird gespeichert, als Ausgabe vereinbart und ausgeschaltet
* @param pPin die Nummer
* @param pTan Dauer an
* @param pTaus Dauer aus
*/
	BLicht::BLicht(int pPin, int pTan, int pTaus) : Licht(pPin)
	{
		Tan = pTan;
		Taus = pTaus;
		wechsel = 0;
		Stat = stAus;
	}
	void BLicht::blinken(bool pAn)
	{
		if (pAn)Stat = stBlink;
		else
		{
			Stat = stAus;
			digitalWrite(Pin, LOW);
		}
	}
	void BLicht::check()
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
