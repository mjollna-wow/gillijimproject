#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <wowfiles/Wdt.h>
#include <wowfiles/Wdl.h>
#include <wowfiles/alpha/WdtAlpha.h>
#include <wowfiles/lichking/AdtLk.h>
#include <wowfiles/cataclysm/AdtCata.h>
#include <utilities/Utilities.h>

int main (int argc, char **argv)
{
  std::string wdtName ("alpha_dm.wdt");
  WdtAlpha testWdtAlpha (wdtName);

  //Wdt testWdt (testWdtAlpha.toWdt());
  //testWdt.toFile();

  std::vector<int> adtsNums (testWdtAlpha.getExistingAdtsNumbers());
  std::vector<int> adtsOffsets (testWdtAlpha.getAdtOffsetsInMain());

  /*const int adtTotalNum (adtsNums.size());
  int currentAdt;

  for (currentAdt = 0 ; currentAdt < adtTotalNum ; ++currentAdt)
  {
    AdtAlpha testAdt (AdtAlpha(wdtName, adtsOffsets[adtsNums[currentAdt]], adtsNums[currentAdt]));
    AdtLk testAdtLk (testAdt.toAdtLk());
    testAdtLk.toFile();
  }*/

  /*AdtAlpha testAdt (AdtAlpha(wdtName, adtsOffsets[adtsNums[0]], adtsNums[0]));

  std::ofstream fileOut;
  fileOut.open ("debugfile.txt");

  fileOut << testAdt;

  AdtLk testAdtLk (testAdt.toAdtLk());
  testAdtLk.toFile();

  AdtLk testAdt2("Azeroth_30_43.adt");

  testAdt2.toFile();*/

  std::string wdlName ("development.wdl");
  Wdl testWdl (wdlName);

  std::ofstream fileOut;
  fileOut.open ("debugfile.txt");

  fileOut << testWdl;
  testWdl.toFile();

  return 0;
}