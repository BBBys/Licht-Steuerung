///
/// @package : Licht
/// LED-Lichtsteuerung für Arduino.
///
/// @author Borys 30 28 Jul 2019
/// @note ALicht.cpp für analoge Lichtsteuerung
///
#include "Licht.h"
#include <math.h>
float fscale( float originalMin, float originalMax, float newBegin, float
newEnd, float inputValue, float curve){

  float OriginalRange = 0;
  float NewRange = 0;
  float zeroRefCurVal = 0;
  float normalizedCurVal = 0;
  float rangedValue = 0;
  boolean invFlag = 0;


  // condition curve parameter
  // limit range

  if (curve > 10) curve = 10;
  if (curve < -10) curve = -10;

  curve = (curve * -.1) ; // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output
  curve = pow(10, curve); // convert linear scale into lograthimic exponent for other pow function

  /*
   Serial.println(curve * 100, DEC);   // multply by 100 to preserve resolution  
   Serial.println();
   */

  // Check for out of range inputValues
  if (inputValue < originalMin) {
    inputValue = originalMin;
  }
  if (inputValue > originalMax) {
    inputValue = originalMax;
  }

  // Zero Refference the values
  OriginalRange = originalMax - originalMin;

  if (newEnd > newBegin){
    NewRange = newEnd - newBegin;
  }
  else
  {
    NewRange = newBegin - newEnd;
    invFlag = 1;
  }

  zeroRefCurVal = inputValue - originalMin;
  normalizedCurVal  =  zeroRefCurVal / OriginalRange;   // normalize to 0 - 1 float

  /*
  Serial.print(OriginalRange, DEC);  
   Serial.print("   ");  
   Serial.print(NewRange, DEC);  
   Serial.print("   ");  
   Serial.println(zeroRefCurVal, DEC);  
   Serial.println();  
   */

  // Check for originalMin > originalMax  - the math for all other cases i.e. negative numbers seems to work out fine
  if (originalMin > originalMax ) {
    return 0;
  }

  if (invFlag == 0){
    rangedValue =  (pow(normalizedCurVal, curve) * NewRange) + newBegin;

  }
  else     // invert the ranges
  {  
    rangedValue =  newBegin - (pow(normalizedCurVal, curve) * NewRange);
  }

  return rangedValue;
}
	ALicht::ALicht(int pPin) : Licht(pPin)
	{
		Stat = stAus;
		Wert = 0;
		analogWrite(Pin, Wert);
	}
	void ALicht::aus()
	{
		Stat = stAus;
		check();
		istAn = false;
	}
	/** Licht wird heller.
	*/
	void ALicht::heller(int pVon, int pBis, long pDauer)
	{
		Stat = stHeller;
		Von = pVon;
		Bis = pBis;
		Dauer=pDauer;
		Start = millis();
		Ende = Start + Dauer;
	}
	/** Licht wird dunkler.
	*/
	void ALicht::dunkler(int pVon, int pBis, long pDauer)
	{
		Stat = stDunkler;
		Von = pVon;
		Bis = pBis;
		Dauer=pDauer;
		Start = millis();
		Ende = Start + Dauer;
	}
	void ALicht::setzen(int pWert)
	{
		Stat = stZwischen;
		Wert = pWert;
		check();
	}
	void ALicht::halb()
	{
		setzen(99);
	}
	void ALicht::ein()
	{
		Stat = stEin;
		check();
		istAn = true;
	}
	/** Wechsel zwischen an und aus, heller und dunkler
	*/
	void ALicht::wechsel()
	{
		switch (Stat)
		{
		case stAus:
			Stat=stEin;
			break;
		case stEin:
			Stat=stAus;
			break;
		case stHeller:
			Stat=stDunkler;
			Start = Ende;
			Ende = Start + Dauer;
			break;
		case stDunkler:
			Stat=stHeller;
			Start = Ende;
			Ende = Start + Dauer;
			break;
		}
		check();
	}
	/** analogen Wert für Helligkeit setzen.
	* für Status An / Aus wird der Wert auf 255 / 0 gesetzt,
	* für Status Heller / Dunkler wird der Sollwert aus Anfangs-, End- und aktueller Zeit berechnet, 
	* dabei wird ein Exponentieller Vrlauf verwendet.
	* @return gibt true zurück, wenn Ende das heller/dunklerwerdens erreicht ist
	*/
	bool ALicht::check()
	{
		bool rtn = false;
		switch (Stat)
		{
			int soll;
		case stAus:
			Wert = 0;
			break;
		case stEin:
			Wert = 255;
			break;
		case stHeller:
			jetzt = millis();
			//int soll = map(jetzt, Start, Ende, 0, 255);
			soll=(int) (fscale(Start,Ende,0,255,jetzt,PHYSVAL)+0.5);
			Wert = constrain(soll, 0, 255);
			if (jetzt>Ende)
			{
				rtn = true;
			}
			break;
		case stDunkler:
			jetzt = millis();
			//int soll = map(jetzt, Start, Ende, 0, 255);
			soll=(int) (fscale(Start,Ende,255,0,jetzt,PHYSVAL)+0.5);
			Wert = constrain(soll, 0, 255);
			if (jetzt>Ende)
			{
				rtn = true;
			}
			break;
		}
		analogWrite(Pin, Wert);
		return rtn;
	}
