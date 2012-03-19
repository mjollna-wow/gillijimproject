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
  std::string wdtName ("azerothwdtFile00000000.xxx");
  WdtAlpha testWdtAlpha (wdtName);

  std::vector<int> adtsNums (testWdtAlpha.getExistingAdtsNumbers());
  std::vector<int> adtsOffsets (testWdtAlpha.getAdtOffsetsInMain());

  const int adtTotalNum (adtsNums.size());
  int currentAdt;

  for (currentAdt = 0 ; currentAdt < adtTotalNum ; ++currentAdt)
  {
    AdtAlpha testAdt (AdtAlpha(wdtName, adtsOffsets[adtsNums[currentAdt]], adtsNums[currentAdt]));
    AdtLk testAdtLk (testAdt.toAdtLk());
    testAdtLk.toFile();
  }

  return 0;
}