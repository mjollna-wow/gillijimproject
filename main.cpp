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
  std::string wdtName ("alpha_dm.wdt");
  WdtAlpha testWdtAlpha (wdtName);

  /*Wdt testWdt (testWdtAlpha.toWdt());
  testWdt.toFile();*/

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

  AdtAlpha testAdt (AdtAlpha(wdtName, adtsOffsets[adtsNums[0]], adtsNums[0]));

  /*std::ofstream fileOut;
  fileOut.open ("debugfile.txt");

  fileOut << testAdt;*/

  AdtLk testAdtLk (testAdt.toAdtLk());
  testAdtLk.toFile();

  AdtLk testAdt2("Azeroth_30_43.adt");

  testAdt2.toFile();

  AdtLk testAdt4("Northrend_27_22.adt");

  testAdt4.toFile();

  /*std::string wdlName ("development.wdl");
  Wdl testWdl (wdlName);

  std::ofstream fileOut;
  fileOut.open ("debugfile.txt");

  fileOut << testWdl;
  testWdl.toFile();*/

  /*AdtCata testAdt3("HawaiiMainLand_19_19.adt");
  std::ofstream fileOut;
  fileOut.open ("debugfile.txt");
  fileOut << testAdt3;
  fileOut.close();

  AdtLk testAdt2("MonasteryInstances_30_30.adt");*/
  
  /*AdtCataTextures testAdt3tex("Deephome_29_29_tex0.adt");  
  std::ofstream fileOut2;
  fileOut2.open ("debugfileTex.txt");
  fileOut2 << testAdt3tex;
  fileOut2.close();*/

  /*AdtCataObjects testAdt3obj("Deephome_30_29_obj0.adt");
  std::ofstream fileOut3;
  fileOut3.open ("debugfileObj.txt");
  fileOut3 << testAdt3obj;
  fileOut3.close();*/

  return 0;
}