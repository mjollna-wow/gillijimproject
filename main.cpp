#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "wowfiles/Wdt.h"
#include "wowfiles/alpha/WdtAlpha.h"
#include "wowfiles/lichking/AdtLk.h"
#include "wowfiles/cataclysm/AdtCata.h"

int main(int argc, char **argv)
{
	//std::string adtName = "Azeroth_30_43.adt"; 
	//std::string adtName = "Northrend_27_22.adt";
	//std::string adtName = "Northrend_32_21.adt";
	//std::string adtName = "EdEdited_26_29.adt";
	//std::string adtName = "EdEdited_27_29.adt";
	//std::string adtName = "EdEdited_27_29_water.adt";
	//AdtLk testAdt = AdtLk(adtName);

	//std::string adtName = "Deephome_29_29.adt"; // --> Cata files don't work.
	//AdtCata testAdt = AdtCata(adtName);

	//std::string wdtName = "alpha_dm.wdt";
  //std::string wdtName = "alpha_azsharacrater.wdt";
  std::string wdtName = "alpha_kalimdor.wdt";
  //std::string wdtName = "alpha_kraull.wdt";
	//std::string wdtName = "alpha_uldaman.wdt";
	//std::string wdtName = "azerothwdtFile00000000.wdt";
	//std::string wdtName = "kalidarFile00000000.xxx";
	WdtAlpha testWdtAlpha = WdtAlpha(wdtName);

	//std::string wdtName = "EmeraldDream422.wdt";
	//Wdt testWdt = testWdtAlpha.toWdt();

	std::ofstream fileOut;
	fileOut.open("debugfile.txt");
	//fileOut << testAdt;
	//fileOut << testWdt;
	fileOut << testWdtAlpha;

	//testWdt.toFile();
	//testAdt.toFile();
	
	return 0;
}