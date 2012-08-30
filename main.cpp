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
  //std::string wdtName (argv[1]);
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
    AdtLk testAdtLk (testAdt.toAdtLk( testWdtAlpha.getMdnmFileNames(), testWdtAlpha.getMonmFileNames() ));
    testAdtLk.toFile();
  }*/

  AdtAlpha testAdt (AdtAlpha(wdtName, adtsOffsets[adtsNums[188]], adtsNums[188])); // azerothwdtFile00000000.xxx : ADT #1950 _ adtsNums[188] : 30_30 . ofs in wdt 148500798

  AdtLk testAdtLk ( testAdt.toAdtLk( testWdtAlpha.getMdnmFileNames(), testWdtAlpha.getMonmFileNames() ) );
  testAdtLk.toFile();

  std::ofstream fileOut;
  fileOut.open ("debugfile.txt");

  fileOut << testAdtLk;

  //////////////////// LK STUFF //////////////////// ok

  //std::vector<char> adtFile(0);
  //std::string adtName ("Azeroth_30_43.adt");
  //std::string adtName ("Azeroth_32_58.adt");
  //std::string adtName ("EmeraldDream_28_28.adt");
  //std::string adtName ("EdEdited_27_30.adt");
  //std::string adtName ("EdEdited_27_29_water.adt");
  //std::string adtName ("OtherTestMap_30_30.adt");
  //std::string adtName ("QA_DVD_30_26.adt");
  //std::string adtName ("Northrend_27_22.adt");
  
  /*Utilities::getWholeFile(adtName, adtFile);

  AdtLk testAdt2(adtFile, adtName);*/

  /*std::vector<std::string> m2Names ( testAdt2.getAllM2Names() );
  std::vector<int> m2Indices ( testAdt2.getAllM2Indices() );
  std::vector<Utilities::Point> m2Coords ( testAdt2.getAllM2Coords() );

  std::vector<std::string> wmoNames ( testAdt2.getAllWmoNames() );
  std::vector<int> wmoIndices ( testAdt2.getAllWmoIndices() );
  std::vector<Utilities::Point> wmoCoords ( testAdt2.getAllWmoCoords() );*/

  /*std::ofstream fileOut;
  fileOut.open ("debugfile.txt");

  fileOut << testAdt2;*/

  /*for ( int i = 0 ; i < m2Indices.size() ; ++i )
  {
    fileOut << m2Names[m2Indices[i]] << " : " << std::endl;
    fileOut << "x : " << m2Coords[i].x << std::endl;
    fileOut << "y : " << m2Coords[i].y << std::endl;
    fileOut << "z : " << m2Coords[i].z << std::endl;
  }

  for ( int i = 0 ; i < wmoIndices.size() ; ++i )
  {
    fileOut << wmoNames[wmoIndices[i]] << " : " << std::endl;
    fileOut << "x : " << wmoCoords[i].x << std::endl;
    fileOut << "y : " << wmoCoords[i].y << std::endl;
    fileOut << "z : " << wmoCoords[i].z << std::endl;
  }*/

  /*fileOut.close();

  testAdt2.toFile();*/

  /*std::string adtName2 ("Northrend_27_22.adt");
  Utilities::getWholeFile(adtName2, adtFile);

  AdtLk testAdt4(adtFile, adtName2);

  testAdt4.toFile();*/

  //////////////////// CATA/MOP STUFF ////////////////////

  //std::vector<char> adtFile(0);
 

  //std::string adtName ("mop/NewRaceStartZone_26_31.adt");
  //std::string adtName (argv[1]);
  /*std::string adtName ("Deephome_29_29.adt");

  Utilities::getWholeFile(adtName, adtFile);

  AdtCata testAdt3(adtName, adtFile);

  std::ofstream fileOut;
  fileOut.open ("debugfile.txt");
  fileOut << testAdt3;
  fileOut.close();

  testAdt3.toFile();*/

  /*AdtLk convertedAdt (testAdt3.toAdtLk());

  convertedAdt.toFile();

  testAdt3.toFile();*/

  /*std::string adtNameTex ("Deephome_29_29_tex0.adt");
  Utilities::getWholeFile(adtNameTex, adtFile);

  AdtCataTextures testAdt3tex(adtNameTex, adtFile);  
  std::ofstream fileOut2;
  fileOut2.open ("debugfileTex.txt");
  fileOut2 << testAdt3tex;
  fileOut2.close();

  testAdt3tex.toFile();*/

  //std::string adtNameObj (argv[1]);
  /*std::string adtNameObj ("Deephome_29_29_obj0.adt");
  
  Utilities::getWholeFile(adtNameObj, adtFile);

  AdtCataObjects testAdt3obj(adtNameObj, adtFile);

  std::ofstream fileOut3 ;
  fileOut3.open ("debugfileObj.txt");

  std::vector<std::string> m2Names ( testAdt3obj.getAllM2Names() );
  std::vector<int> m2Indices ( testAdt3obj.getAllM2Indices() );
  std::vector<Utilities::Point> m2Coords ( testAdt3obj.getAllM2Coords() );

  std::vector<std::string> wmoNames ( testAdt3obj.getAllWmoNames() );
  std::vector<int> wmoIndices ( testAdt3obj.getAllWmoIndices() );
  std::vector<Utilities::Point> wmoCoords ( testAdt3obj.getAllWmoCoords() );

  std::ofstream fileOut;
  fileOut.open ("debugfile.txt");

  for ( int i = 0 ; i < m2Indices.size() ; ++i )
  {
    fileOut << m2Names[m2Indices[i]] << " : " << std::endl;
    fileOut << "x : " << m2Coords[i].x << std::endl;
    fileOut << "y : " << m2Coords[i].y << std::endl;
    fileOut << "z : " << m2Coords[i].z << std::endl;
  }

  for ( int i = 0 ; i < wmoIndices.size() ; ++i )
  {
    fileOut << wmoNames[wmoIndices[i]] << " : " << std::endl;
    fileOut << "x : " << wmoCoords[i].x << std::endl;
    fileOut << "y : " << wmoCoords[i].y << std::endl;
    fileOut << "z : " << wmoCoords[i].z << std::endl;
  }

  fileOut.close();*/

  //fileOut3 << testAdt3obj;
  //fileOut3.close();

  /*std::ofstream fileOut4;
  fileOut4.open ("objectsCoords.txt", std::ios::app);
  
  std::vector<Utilities::Point> coords ( testAdt3obj.getAllObjectsCoords() );

  for (int i = 0 ; i < coords.size() ; ++i)
  {
    fileOut4 << coords[i].x << "\t" << coords[i].y << std::endl;
  }

  fileOut4.close();*/

  //testAdt3obj.toFile();

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