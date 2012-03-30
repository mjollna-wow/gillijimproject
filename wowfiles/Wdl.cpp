#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <wowfiles/Wdl.h>
#include <wowfiles/Chunk.h>
#include <utilities/Utilities.h>

Wdl::Wdl(const std::string & wdlFileName) : wdlName(wdlFileName)
{
  std::ifstream wdlFile;
  wdlFile.open(wdlName.c_str(), std::ios::binary);

  wdlFile.seekg(0, std::ios::end);
  const int fileSize = wdlFile.tellg();
  wdlFile.seekg(0, std::ios::beg);
  
  int offsetInFile (0);

  mwmo = Chunk(wdlFile, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + mwmo.getGivenSize();

  mwid = Chunk(wdlFile, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + mwid.getGivenSize();

  modf = Chunk(wdlFile, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + modf.getGivenSize();

  maof = Chunk(wdlFile, offsetInFile);
  offsetInFile = chunkLettersAndSize + offsetInFile + maof.getGivenSize();  

  while (offsetInFile < fileSize)
  {
    mareAndMaho.push_back(Chunk(wdlFile, offsetInFile));
	offsetInFile = chunkLettersAndSize + offsetInFile + mareAndMaho.back().getGivenSize();
  }
}

Wdl::Wdl(const std::string & name // TODO : that one is untested but should work
      , const Chunk & cMwmo
      , const Chunk & cMwid
      , const Chunk & cModf
      , const Chunk & cMaof
      , const std::vector<Chunk> & cMareAndMaho
  ) : wdlName(name)
  , mwmo(cMwmo)
  , mwid(cMwid)
  , modf(cModf)
  , maof(cMaof)
  , mareAndMaho(cMareAndMaho)
{
}

void Wdl::toFile()
{
  std::string fileName (wdlName);
  fileName.append("_new");
  std::ofstream outputFile (fileName.c_str(), std::ios::out|std::ios::binary);
  if (outputFile.is_open())
  {
    outputFile.write((char *)&mwmo.getWholeChunk()[0], sizeof(char) * mwmo.getWholeChunk().size());
    outputFile.write((char *)&mwid.getWholeChunk()[0], sizeof(char) * mwid.getWholeChunk().size());
    outputFile.write((char *)&modf.getWholeChunk()[0], sizeof(char) * modf.getWholeChunk().size());
    outputFile.write((char *)&maof.getWholeChunk()[0], sizeof(char) * maof.getWholeChunk().size());	

    std::vector<Chunk>::const_iterator mareAndMahoIter;

    for (mareAndMahoIter = mareAndMaho.begin() ; mareAndMahoIter != mareAndMaho.end() ; ++mareAndMahoIter)
    {
	  outputFile.write((char *)&(*mareAndMahoIter).getWholeChunk()[0], sizeof(char) * (*mareAndMahoIter).getWholeChunk().size());
    }	
  }
  
  outputFile.close();
}

std::ostream & operator<<(std::ostream & os, const Wdl & wdl)
{
  os << wdl.wdlName << std::endl;
  os << "------------------------------" << std::endl;
  os << wdl.mwmo;
  os << wdl.mwid;
  os << wdl.modf;
  os << wdl.maof;

  std::vector<Chunk>::const_iterator mareAndMahoIter;

  for (mareAndMahoIter = wdl.mareAndMaho.begin() ; mareAndMahoIter != wdl.mareAndMaho.end() ; ++mareAndMahoIter)
  {
    os << *mareAndMahoIter;
  }
  
  return os;
}
