#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "Wdt.h"
#include "Mphd.h"
#include "Chunk.h"
#include "../utilities/Utilities.h"

Wdt::Wdt(const std::string & wdtFileName) : wdtName(wdtFileName)
{
  std::ifstream wdtFile;
  wdtFile.open(wdtName.c_str(), std::ios::binary);

  int offsetInFile = 0;

  mver = Chunk(wdtFile, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + mver.getGivenSize();

  mphd = Mphd(wdtFile, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + mphd.getGivenSize();

  main = Chunk(wdtFile, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + main.getGivenSize();

  if (Utilities::flagsExist(mphd.getFlags(), 0x1))
  {
    mwmo = Chunk(wdtFile, offsetInFile);
    offsetInFile = chunkLettersAndSize + offsetInFile + mwmo.getGivenSize();
  }

  if (mwmo.getGivenSize() != 0)
  {
    modf = Chunk(wdtFile, offsetInFile);
    offsetInFile = chunkLettersAndSize + offsetInFile + modf.getGivenSize();
  }
}

Wdt::Wdt(const std::string & name
  , const Chunk & cMver
  , const Mphd & cMphd
  , const Chunk & cMain
  , const Chunk & cMwmo
  , const Chunk & cModf
  ) : wdtName(name)
  , mver(cMver)
  , mphd(cMphd)
  , main(cMain)
  , mwmo(cMwmo)
  , modf(cModf)
{
}

void Wdt::toFile()
{
  std::string fileName = wdtName;
  fileName.append("_new");
  std::ofstream outputFile(fileName.c_str(), std::ios::out|std::ios::binary);
  if (outputFile.is_open())
  {
    outputFile.write((char *)&mver.getWholeChunk()[0], sizeof(char) * mver.getWholeChunk().size());
    outputFile.write((char *)&mphd.getWholeChunk()[0], sizeof(char) * mphd.getWholeChunk().size());
    outputFile.write((char *)&main.getWholeChunk()[0], sizeof(char) * main.getWholeChunk().size());

    if (!mwmo.isEmpty())
      outputFile.write((char *)&mwmo.getWholeChunk()[0], sizeof(char) * mwmo.getWholeChunk().size());
    
    if (!modf.isEmpty())
      outputFile.write((char *)&modf.getWholeChunk()[0], sizeof(char) * modf.getWholeChunk().size());
  }
  
  outputFile.close();
}

std::ostream & operator<<(std::ostream & os, const Wdt & wdt)
{
  os << wdt.wdtName << std::endl;
  os << "------------------------------" << std::endl;
  os << wdt.mver;
  os << wdt.mphd;
  os << wdt.main;
  os << wdt.mwmo;
  os << wdt.modf;

  return os;
}
