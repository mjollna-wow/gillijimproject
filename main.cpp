#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <wowfiles/Wdt.h>
#include <wowfiles/Wdl.h>
#include <wowfiles/alpha/WdtAlpha.h>
#include <wowfiles/lichking/AdtLk.h>
#include <wowfiles/cataclysm/AdtCata.h>
#include <wowfiles/cataclysm/AdtCataTextures.h>
#include <wowfiles/cataclysm/AdtCataObjects.h>
#include <utilities/Utilities.h>

int main (int argc, char **argv)
{
  /* Yes, it's horribly messy, testing junk :p */

  //////////////////// ALPHA STUFF ////////////////////

  std::string wdtName ("azerothwdtFile00000000.xxx");
  WdtAlpha testWdtAlpha (wdtName);

  Wdt testWdt (testWdtAlpha.toWdt());
  testWdt.toFile();

  std::vector<int> adtsNums (testWdtAlpha.getExistingAdtsNumbers());
  std::vector<int> adtsOffsets (testWdtAlpha.getAdtOffsetsInMain());

  const int adtTotalNum (adtsNums.size());
  int currentAdt;

  /*for (currentAdt = 0 ; currentAdt < adtTotalNum ; ++currentAdt)
  {
    AdtAlpha testAdt (AdtAlpha(wdtName, adtsOffsets[adtsNums[currentAdt]], adtsNums[currentAdt]));
    AdtLk testAdtLk (testAdt.toAdtLk());
    testAdtLk.toFile();
  }*/

  AdtAlpha testAdt (AdtAlpha(wdtName, adtsOffsets[adtsNums[188]], adtsNums[188])); // azerothwdtFile00000000.xxx : ADT #1950 _ adtsNums[188] : 30_30 . ofs in wdt 148500798

  std::ofstream fileOut;
  fileOut.open ("debugfile.txt");

  fileOut << testAdt;

  //AdtLk testAdtLk (testAdt.toAdtLk());
  //testAdtLk.toFile();

  //////////////////// LK STUFF //////////////////// ok

  /*std::vector<char> adtFile(0);
  std::string adtName ("Azeroth_30_43.adt");
  //std::string adtName ("Azeroth_32_58.adt");
  //std::string adtName ("EmeraldDream_28_28.adt");
  //std::string adtName ("EdEdited_27_30.adt");
  //std::string adtName ("EdEdited_27_29_water.adt");
  //std::string adtName ("OtherTestMap_30_30.adt");
  Utilities::getWholeFile(adtName, adtFile);
  
  AdtLk testAdt2(adtFile, adtName);

  std::ofstream fileOut;
  fileOut.open ("debugfile.txt");

  fileOut << testAdt2;

  testAdt2.toFile();*/

  /*std::string adtName2 ("Northrend_27_22.adt");
  Utilities::getWholeFile(adtName2, adtFile);

  AdtLk testAdt4(adtFile, adtName2);

  testAdt4.toFile();*/

  //////////////////// CATA/MOP STUFF ////////////////////

  /*std::vector<char> adtFile(0);
  
  std::string adtName ("mop/NewRaceStartZone_26_31.adt");
  Utilities::getWholeFile(adtName, adtFile);

  AdtCata testAdt3(adtName, adtFile);
  std::ofstream fileOut;
  fileOut.open ("debugfile.txt");
  fileOut << testAdt3;
  fileOut.close();*/

  /*AdtLk convertedAdt (testAdt3.toAdtLk());

  convertedAdt.toFile();

  testAdt3.toFile();*/

  /*std::string adtName ("Deephome_29_29_tex0.adt");
  Utilities::getWholeFile(adtName, adtFile);

  AdtCataTextures testAdt3tex(adtName, adtFile);  
  std::ofstream fileOut2;
  fileOut2.open ("debugfileTex.txt");
  fileOut2 << testAdt3tex;
  fileOut2.close();

  testAdt3tex.toFile();*/

  /*std::string adtName ("Deephome_30_29_obj0.adt");
  Utilities::getWholeFile(adtName, adtFile);

  AdtCataObjects testAdt3obj(adtName, adtFile);
  std::ofstream fileOut3;
  fileOut3.open ("debugfileObj.txt");
  fileOut3 << testAdt3obj;
  fileOut3.close();

  testAdt3obj.toFile();*/

  //////////////////// WDT (non-alpha) STUFF //////////////////// ok

  /*std::vector<char> wdtFile(0);
  std::string wdtName ("Kalimdor.wdt");
  Utilities::getWholeFile(wdtName, wdtFile);
  
  Wdt testWdt (wdtFile, wdtName);

  std::ofstream fileOut;
  fileOut.open ("debugfile.txt");

  fileOut << testWdt;
  testWdt.toFile();*/

  //////////////////// WDL STUFF //////////////////// ok

  /*std::vector<char> wdlFile(0);
  std::string wdlName ("development.wdl");
  Utilities::getWholeFile(wdlName, wdlFile);
  
  Wdl testWdl (wdlFile, wdlName);

  std::ofstream fileOut;
  fileOut.open ("debugfile.txt");

  fileOut << testWdl;
  testWdl.toFile();*/

  return 0;
}