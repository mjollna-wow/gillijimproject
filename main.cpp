#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "wowfiles/Wdt.h"
#include "wowfiles/alpha/WdtAlpha.h"
#include "wowfiles/lichking/AdtLk.h"
#include "wowfiles/cataclysm/AdtCata.h"
#include "utilities/Utilities.h"

int main(int argc, char **argv)
{
  //std::string adtName = "Azeroth_30_43.adt"; 
  //std::string adtName = "Northrend_27_22.adt";
  //std::string adtName = "Northrend_32_21.adt";
  //std::string adtName = "EdEdited_27_29.adt";
  std::string adtName = "EdEdited_27_29_water.adt";
  AdtLk testAdt = AdtLk(adtName);

  //std::string adtName = "Deephome_29_29.adt"; // --> Cata files don't work.
  //AdtCata testAdt = AdtCata(adtName);

  //std::string wdtName = "Kalimdor.wdt";
  //std::string wdtName = "alpha_dm.wdt";
  //std::string wdtName = "alpha_azsharacrater.wdt";
  //std::string wdtName = "alpha_kalimdor.wdt";
  //std::string wdtName = "alpha_kraull.wdt";
  //std::string wdtName = "alpha_uldaman.wdt";
  //std::string wdtName = "azerothwdtFile00000000.xxx";
  //std::string wdtName = "kalidarFile00000000.xxx";
  //std::string wdtName = "__testWdtLk.wdttest";
  //--> WdtAlpha testWdtAlpha = WdtAlpha(wdtName);

  //Wdt testWdt = Wdt(wdtName);

  //--> std::vector<int> adtsNums = testWdtAlpha.getExistingAdtsNumbers();
  //--> std::vector<int> adtsOffsets = testWdtAlpha.getAdtOffsetsInMain();

  std::ofstream fileOut;
  fileOut.open("debugfile.txt");

  /*const int adtTotalNum = adtsNums.size();
  int currentAdt;

  for (currentAdt = 0 ; currentAdt < adtTotalNum ; currentAdt++)
  {
    AdtAlpha testAdt = AdtAlpha(wdtName, adtsOffsets[adtsNums[currentAdt]], adtsNums[currentAdt]);
    AdtLk testAdtLk = testAdt.toAdtLk();
    fileOut << testAdtLk;
    testAdtLk.toFile();
  }*/

  /*AdtAlpha testAdt = AdtAlpha(wdtName, adtsOffsets[adtsNums[550]], adtsNums[550]); // 15
  fileOut << testAdt;
  AdtLk testAdtLk = testAdt.toAdtLk();
  testAdtLk.toFile();*/
  
  //std::string wdtName = "EmeraldDream422.wdt";
  //--> Wdt testWdt = testWdtAlpha.toWdt();
  //AdtLk testAdtLk = testAdt.toAdtLk();

  fileOut << testAdt;
  //fileOut << testWdt;
  //fileOut << testWdtAlpha;
  //fileOut << testAdtLk;

  testAdt.toFile();
  testAdt.mh2oToFile();

  //testWdt.toFile();

  //testAdtLk.toFile();*/

  /*std::string adtName = argv[1];
  std::string mh2oName = argv[2];
  
  AdtLk inputAdt = AdtLk(adtName);
  AdtLk outputAdt = inputAdt.importMh2o(mh2oName);
  
  outputAdt.toFile();*/

  return 0;
}