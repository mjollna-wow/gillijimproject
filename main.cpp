#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <wowfiles/Wdt.h>
#include <wowfiles/alpha/WdtAlpha.h>
#include <wowfiles/lichking/AdtLk.h>
#include <wowfiles/cataclysm/AdtCata.h>
#include <utilities/Utilities.h>

int main (int argc, char **argv)
{
  //std::string adtName ("Azeroth_30_43.adt");
  //std::string adtName ("Northrend_27_22.adt");
  //std::string adtName ("Northrend_32_21.adt");
  //std::string adtName ("EdEdited_27_29.adt");
  //const std::string adtName ("azeroth_32_35.adt");
  //const std::string adtName ("EdEdited_27_29_water.adt");
  //std::string adtName ("MonasteryInstances_30_30.adt");
  //AdtLk testAdt (adtName);

  //std::string adtName (Deephome_29_29.adt); // --> Cata files don't work.
  //AdtCata testAdt (adtName);

  //std::string wdtName ("Kalimdor.wdt");
  //std::string wdtName ("alpha_dm.wdt");
  //std::string wdtName ("alpha_azsharacrater.wdt");
  //std::string wdtName ("alpha_kalimdor.wdt");
  //std::string wdtName ("alpha_kraull.wdt");
  //std::string wdtName ("alpha_uldaman.wdt");
  std::string wdtName ("azerothwdtFile00000000.xxx");
  //std::string wdtName ("kalidarFile00000000.xxx");
  //std::string wdtName ("__testWdtLk.wdttest");
  WdtAlpha testWdtAlpha (wdtName);

  //Wdt testWdt (Wdt(wdtName));

  std::vector<int> adtsNums (testWdtAlpha.getExistingAdtsNumbers());
  std::vector<int> adtsOffsets (testWdtAlpha.getAdtOffsetsInMain());

  //std::ofstream fileOut;
  //fileOut.open ("debugfile.txt");

  //fileOut << testAdt;
  //testAdt.toFile();

  const int adtTotalNum (adtsNums.size());
  int currentAdt;

  for (currentAdt = 0 ; currentAdt < adtTotalNum ; ++currentAdt)
  {
    AdtAlpha testAdt (AdtAlpha(wdtName, adtsOffsets[adtsNums[currentAdt]], adtsNums[currentAdt]));
    //std::cout << currentAdt << std::endl;
    AdtLk testAdtLk (testAdt.toAdtLk());
    testAdtLk.toFile();
  }

  //AdtAlpha testAdt (AdtAlpha(wdtName, adtsOffsets[adtsNums[0]], adtsNums[0])); // 15
  //fileOut << testAdt;
  //AdtLk testAdtLk (testAdt.toAdtLk());
  //testAdtLk.toFile();

  //std::string wdtName ("EmeraldDream422.wdt");
  //--> Wdt testWdt (testWdtAlpha.toWdt());
  //AdtLk testAdtLk (testAdt.toAdtLk());

  //fileOut << testWdt;
  //fileOut << testWdtAlpha;
  //fileOut << testAdtLk;

  //fileOut << testAdt;
  //testAdt.toFile();
  //testAdt.mh2oToFile();

  //const std::string reimportAdtName ("MonasteryInstances_30_30_for_import.adt");
  //std::string reimportAdtName ("Northrend_27_22.adt");
  //std::string reimportAdtName = "EdEdited_27_29_water.adt";
  //AdtLk reimportAdt (reimportAdtName);

  //reimportAdt.importMh2o ("Northrend_27_22.mh2o");
  //fileOut << reimportAdt;
  //reimportAdt.toFile ("test");

  //testWdt.toFile();

  //testAdtLk.toFile();*/

  /*std::string adtName (argv[1]);
  std::string mh2oName (argv[2]);

  AdtLk inputAdt (AdtLk(adtName));
  AdtLk outputAdt (inputAdt.importMh2o(mh2oName));

  outputAdt.toFile();*/

  return 0;
}
