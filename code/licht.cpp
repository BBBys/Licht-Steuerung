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
	/** LED an Pin vereinbaren.
	* Pin-Nummer wird gespeichert, als Ausgabe vereinbart und ausgeschaltet
	* @param pPin die Nummer
	*/
	LLicht::LLicht(int pPin) : Licht(pPin)
	{
		Wechsel = 0;
		Stat = stAus;
	}
	void LLicht::aus()
	{
		Stat = stAus;
		Licht::aus();
	}
	void LLicht::ein()
	{
		Licht::ein();
		Ein1 = random(EIN10, EIN11);
		Ein3 = random(EIN30, EIN31);
		Ein5 = random(EIN30, EIN31);
		Aus2 = random(AUS20, AUS21);
		Aus4 = random(AUS40, AUS41);
		Aus6 = random(AUS40, AUS41);
		Stat = stZ1;
		Wechsel = millis() + Ein1;
		check();
	}
	void LLicht::check()
	{
		unsigned long jetzt;
		jetzt = millis();
		switch (Stat)
		{
		//case LLicht::stAus:
		//	Licht::aus();
		//	break;
		case LLicht::stZ1:
			if (jetzt > Wechsel)
			{
				Licht::aus();
				Stat = stZ2;
				Wechsel = jetzt + Aus2;
			}
			break;
		case LLicht::stZ2:
			if (jetzt > Wechsel)
			{
				Licht::ein();
				Stat = stZ3;
				Wechsel = jetzt + Ein3;
			}
			break;
		case LLicht::stZ3:
			if (jetzt > Wechsel)
			{
				Licht::aus();
				Stat = stZ4;
				Wechsel = jetzt + Aus4;
			}
			break;
		case LLicht::stZ4:
			if (jetzt > Wechsel)
			{
				Licht::ein();
				Stat = stZ5;
				Wechsel = jetzt + Ein5;
			}
			break;
		case LLicht::stZ5:
			if (jetzt > Wechsel)
			{
				Licht::aus();
				Stat = stZ6;
				Wechsel = jetzt + Aus6;
			}
			break;
		case LLicht::stZ6:
			if (jetzt > Wechsel)
			{
				Licht::ein();
				Stat = stEin;
			}
			break;
			//case LLicht::stEin:
		//	Licht::ein();
		//	break;
		default:
			break;
		}
	}
		