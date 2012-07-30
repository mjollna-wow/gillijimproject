#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mmdx.h>
#include <utilities/Utilities.h>

Mmdx::Mmdx() : Chunk()
{
}

Mmdx::Mmdx(std::ifstream & adtFile, int offsetInFile) : Chunk(adtFile, offsetInFile)
{
}

Mmdx::Mmdx(const std::vector<char> & wholeFile, int offsetInFile) : Chunk(wholeFile, offsetInFile)
{
}

Mmdx::Mmdx(std::string letters, int givenSize, const std::vector<char> & data) : Chunk("XDMM", givenSize, data)
{
}

std::ostream & operator<<(std::ostream & os, const Mmdx & mmdx)
{
  os << "Chunk letters : " << mmdx.letters << std::endl;
  os << "Chunk givenSize : " << mmdx.givenSize << std::endl;
  os << "File names in MMDX : " << std::endl;

  std::vector<std::string> mmdxFiles = Utilities::getFileNames(mmdx.data);

  std::vector<std::string>::iterator filesIter;

  for (filesIter = mmdxFiles.begin() ; filesIter != mmdxFiles.end() ; ++filesIter)
  {
    os << *filesIter << std::endl;
  }

  os << "------------------------------" << std::endl;
  return os;
}