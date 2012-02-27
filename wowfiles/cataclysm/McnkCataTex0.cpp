#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../Chunk.h"
#include "McnkCataTex0.h"
#include "../../utilities/Utilities.h"

McnkCataTex0::McnkCataTex0(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
  const int chunkLettersAndSize = 8;
  offsetInFile = chunkLettersAndSize + offsetInFile;

  mcly = Chunk(adtFile, offsetInFile); // TODO : check that...
  offsetInFile = chunkLettersAndSize + offsetInFile + mcly.getGivenSize();

  mcal = Chunk(adtFile, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + mcal.getGivenSize();

  /*if (givenSize > offsetInFile) // TODO : I don't like the way that looks -_-
  {
    mcmt = Chunk(adtFile, offsetInFile);
    offsetInFile = chunkLettersAndSize + offsetInFile + mcmt.getGivenSize();
  }
  else
  {
    mcmt = Chunk();
  }*/
}

std::ostream & operator<<(std::ostream & os, const McnkCataTex0 & mcnkCataTex0)
{
  os << "Chunk letters : " << mcnkCataTex0.letters << std::endl;
  os << "Chunk givenSize : " << mcnkCataTex0.givenSize << std::endl;

  os << "------------------------------" << std::endl;

  os << mcnkCataTex0.mcly;
  os << mcnkCataTex0.mcal;
  /*os << mcnkCataTex0.mcmt;*/

  os << "------------------------------" << std::endl;
  return os;
}