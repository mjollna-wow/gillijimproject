#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <wowfiles/cataclysm/AdtCata.h>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mh2o.h>
#include <wowfiles/cataclysm/McnkCata.h>
#include <wowfiles/cataclysm/McnkCataTex0.h>
#include <wowfiles/cataclysm/McnkCataObj0.h>

AdtCata::AdtCata(const std::string & adtFileName) : adtName(adtFileName)
{
  std::ifstream adtTerrainFile;
  adtTerrainFile.open(adtFileName.c_str(), std::ios::binary);

  int offsetInFile (0);
  int currentMcnk;

  const int mh2oOffset (40);
  const int mfboOffset (36);

  terrainMver = Chunk(adtTerrainFile, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + terrainMver.getGivenSize();

  mhdr = Chunk(adtTerrainFile, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + mhdr.getGivenSize();

  if (mhdr.getOffset(mh2oOffset) != 0)
  {
    mh2o = Chunk(adtTerrainFile, offsetInFile);
    offsetInFile = chunkLettersAndSize + offsetInFile + mh2o.getRealSize();
  }

  for (currentMcnk = 0 ; currentMcnk < 256 ; ++currentMcnk)
  {
    terrainMcnks.push_back(McnkCata(adtTerrainFile, offsetInFile));
    offsetInFile = chunkLettersAndSize + offsetInFile + terrainMcnks[currentMcnk].getGivenSize();
  }

  if (mhdr.getOffset(mfboOffset) != 0)
  {
    mfbo = Chunk(adtTerrainFile, offsetInFile);
  }




  offsetInFile = 0;
  std::string tex0FileName = getTex0FileName();

  std::ifstream adtTex0File;
  adtTex0File.open(tex0FileName.c_str(), std::ios::binary);

  tex0Mver = Chunk(adtTex0File, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + tex0Mver.getGivenSize();

  mamp = Chunk(adtTex0File, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + mamp.getGivenSize();

  mtex = Chunk(adtTex0File, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + mtex.getGivenSize();

  for (currentMcnk = 0 ; currentMcnk < 256 ; ++currentMcnk)
  {
    tex0Mcnks.push_back(McnkCataTex0(adtTex0File, offsetInFile));
    offsetInFile = chunkLettersAndSize + offsetInFile + tex0Mcnks[currentMcnk].getGivenSize();
  }

  /*if (offsetInFile != tex0FullData.size()) // TODO : get filesize correctly
  {
    mtxf = Chunk(adtTex0File, offsetInFile);
  }*/



  /*offsetInFile = 0;
  std::string obj0FileName = getObj0FileName();

  std::ifstream adtObj0File;
  adtObj0File.open(obj0FileName, std::ios::binary);

  obj0Mver = Chunk(adtObj0File, offsetInFile);
  offsetInFile = offsetInFile + obj0Mver.getGivenSize();

  mmdx = Chunk(adtObj0File, offsetInFile);
  offsetInFile = offsetInFile + mmdx.getGivenSize();

  mmid = Chunk(adtObj0File, offsetInFiles);
  offsetInFile = offsetInFile + mmid.getGivenSize();

  mwmo = Chunk(adtObj0File, offsetInFiles);
  offsetInFile = offsetInFile + mwmo.getGivenSize();

  mwid = Chunk(adtObj0File, offsetInFilets);
  offsetInFile = offsetInFile + mwid.getGivenSize();

  mmdf = Chunk(adtObj0File, offsetInFile);
  offsetInFile = offsetInFile + mmdf.getGivenSize();

  modf = Chunk(adtObj0File, offsetInFile);
  offsetInFile = offsetInFile + modf.getGivenSize();

  for (currentMcnk = 0 ; currentMcnk < 256 ; ++currentMcnk)
  {
    obj0Mcnks[currentMcnk] = McnkCataObj0(adtObj0File, offsetInFile);
    offsetInFile = offsetInFile + obj0Mcnks[currentMcnk].getGivenSize();
  }*/
}

std::string AdtCata::getTex0FileName() const
{
  std::string extensionReplacement ("_tex0.adt");
  std::string tex0Name (adtName);
  return tex0Name.replace(tex0Name.size() - 4, tex0Name.size(), extensionReplacement);
}

std::string AdtCata::getObj0FileName() const
{
  std::string extensionReplacement ("_obj0.adt");
  std::string obj0Name (adtName);
  return obj0Name.replace(obj0Name.size() - 4, obj0Name.size(), extensionReplacement);
}

void AdtCata::toFile()
{
  // TODO.
}

std::ostream & operator<<(std::ostream & os, const AdtCata & adtCata)
{
  os << adtCata.adtName << std::endl;
  os << "------------------------------" << std::endl;
  os << adtCata.terrainMver;
  os << adtCata.mhdr;
  os << adtCata.mh2o;

  std::vector<McnkCata>::const_iterator mcnksIter;
  int i (0);

  for (mcnksIter = adtCata.terrainMcnks.begin() ; mcnksIter != adtCata.terrainMcnks.end() ; ++mcnksIter)
  {
    os << "MCNK #" << i << " : " << std::endl;
    os << *mcnksIter;
    ++i;
  }

  os << adtCata.mfbo;

  os << "------------------------------" << std::endl;
  os << adtCata.getTex0FileName() << std::endl;
  os << "------------------------------" << std::endl;
  os << adtCata.tex0Mver;
  os << adtCata.mamp;
  os << adtCata.mtex;

  std::vector<McnkCataTex0>::const_iterator mcnkstex0Iter;
  i = 0;

  for (mcnkstex0Iter = adtCata.tex0Mcnks.begin() ; mcnkstex0Iter != adtCata.tex0Mcnks.end() ; ++mcnkstex0Iter)
  {
    os << "MCNK (tex0) #" << i << " : " << std::endl;
    os << *mcnkstex0Iter;
    ++i;
  }

  /*os << adtCata.mtxf;*/

  os << "------------------------------" << std::endl;
  os << adtCata.getObj0FileName() << std::endl;
  os << "------------------------------" << std::endl;
  /*os << adtCata.obj0Mver;
  os << adtCata.mmdx;
  os << adtCata.mmid;
  os << adtCata.mwmo;
  os << adtCata.mwid;
  os << adtCata.mddf;
  os << adtCata.modf;

  i = 0;

  for (mcnksIter = adtCata.obj0Mcnks.begin() ; mcnksIter != adtCata.obj0Mcnks.end() ; ++mcnksIter)
  {
    os << "MCNK (obj0) #" << i << " : " << std::endl;
    os << *mcnksIter;
    ++i;
  }*/

  return os;
}
