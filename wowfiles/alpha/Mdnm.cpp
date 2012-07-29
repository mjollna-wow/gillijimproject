#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/alpha/Mdnm.h>
#include <utilities/Utilities.h>

Mdnm::Mdnm() : Chunk()
{
}

Mdnm::Mdnm(std::ifstream & wdtAlphaFile, int offsetInFile) : Chunk(wdtAlphaFile, offsetInFile)
{
}

Mdnm::Mdnm(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("MNDM", givenSize, data) 
{
}

std::ostream & operator<<(std::ostream & os, const Mdnm & mdnm)
{
  os << "Chunk letters : " << mdnm.letters << std::endl;
  os << "Chunk givenSize : " << mdnm.givenSize << std::endl;
  os << "File names in MDNM : " << std::endl;

  std::vector<std::string> mdnmFiles = Utilities::getFileNames(mdnm.data);

  std::vector<std::string>::iterator filesIter;

  for (filesIter = mdnmFiles.begin() ; filesIter != mdnmFiles.end() ; ++filesIter)
  {
    os << *filesIter << std::endl;
  }

  os << "------------------------------" << std::endl;
  return os;
}