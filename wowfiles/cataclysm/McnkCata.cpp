#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mcnk.h>
#include <wowfiles/cataclysm/McnkCata.h>
#include <wowfiles/cataclysm/McnrCata.h>
#include <wowfiles/lichking/McnkLk.h>
#include <utilities/Utilities.h>

McnkCata::McnkCata(const std::vector<char> & adtFile, int offsetInFile, const int & headerSize) : Mcnk(adtFile, offsetInFile, mcnkTerrainHeaderSize)
{
  const int headerStartOffset (offsetInFile + chunkLettersAndSize);
  const int absoluteMcnkEnd = offsetInFile + chunkLettersAndSize + givenSize;

  offsetInFile = chunkLettersAndSize + offsetInFile;

  mcnkHeader = *reinterpret_cast<McnkHeader*>(&data[0]);

  offsetInFile = headerStartOffset + mcnkTerrainHeaderSize;
  
  int chunkName;

  while (offsetInFile < absoluteMcnkEnd)
  {
    chunkName = Utilities::get<int>(adtFile, offsetInFile);

    switch (chunkName)
    {
      case 'MCVT' :
        mcvt = Chunk(adtFile, offsetInFile);
        offsetInFile = offsetInFile + chunkLettersAndSize + mcvt.getGivenSize();
        break;  

      case 'MCCV' :
        mccv = Chunk(adtFile, offsetInFile);
        offsetInFile = offsetInFile + chunkLettersAndSize + mccv.getGivenSize();
        break;  		

      case 'MCLV' :
        mclv = Chunk(adtFile, offsetInFile);
        offsetInFile = offsetInFile + chunkLettersAndSize + mclv.getGivenSize();
        break;  

      case 'MCNR' :
        mcnr = McnrCata(adtFile, offsetInFile);
        offsetInFile = offsetInFile + chunkLettersAndSize + mcnr.getGivenSize();
        break;  		

      case 'MCLQ' :
        mclq = Chunk(adtFile, offsetInFile);
        offsetInFile = offsetInFile + chunkLettersAndSize + mclq.getGivenSize();
        break;  
		
      case 'MCSE' :
        mcse = Chunk(adtFile, offsetInFile);
        offsetInFile = offsetInFile + chunkLettersAndSize + mcse.getGivenSize();
        break; 

      case 'MCBB' :
        mcbb = Chunk(adtFile, offsetInFile);
        offsetInFile = offsetInFile + chunkLettersAndSize + mcbb.getGivenSize();
        break;  	
		
      default :
        terrainMcnkUnknown.push_back(Chunk(adtFile, offsetInFile));
        offsetInFile = offsetInFile + chunkLettersAndSize + terrainMcnkUnknown.back().getGivenSize();
    }
  }		
}

void McnkCata::setRelativeHeight(const int & heightToAdd)
{
  mcnkHeader.posZ += heightToAdd;
}

std::vector<char> McnkCata::getWholeChunk() const
{
  std::vector<char> wholeChunk (0);

  std::vector<char> tempData (letters.begin(), letters.end());
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(givenSize);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.flags);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());
  
  tempData = Utilities::getCharVectorFromInt(mcnkHeader.indexX);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.indexY);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.nLayers);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.m2Number);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.mcvtOffset);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.mcnrOffset);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.mclyOffset);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.mcrfOffset);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.mcalOffset);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.mcalSize);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.mcshOffset);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.mcshSize);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.areaId);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.wmoNumber);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.holes);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.groundEffectsMap1);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.groundEffectsMap2);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.groundEffectsMap3);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.groundEffectsMap4);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.predTex);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.nEffectDoodad);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.mcseOffset);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.nSndEmitters);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.mclqOffset);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.mclqSize);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromFloat(mcnkHeader.posX);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromFloat(mcnkHeader.posY);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromFloat(mcnkHeader.posZ);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.mccvOffset);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.mclvOffset);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = Utilities::getCharVectorFromInt(mcnkHeader.unused);
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  tempData = mcvt.getWholeChunk();
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  if (!mccv.isEmpty())
  {
    tempData = mccv.getWholeChunk();
    wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());
  }

  if (!mclv.isEmpty())
  {
    tempData = mclv.getWholeChunk();
    wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());
  }

  tempData = mcnr.getWholeChunk();
  wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());

  if (!mclq.isEmpty())
  {
    tempData = mclq.getWholeChunk();
    wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());
  }

  if (!mcse.isEmpty())
  {
    tempData = mcse.getWholeChunk();
    wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());
  }  

  if (!mcbb.isEmpty())
  {
    tempData = mcbb.getWholeChunk();
    wholeChunk.insert(wholeChunk.end(), tempData.begin(), tempData.end());
  }  

  return wholeChunk;
}

void McnkCata::toFile()
{
  // TODO
}

McnkLk McnkCata::toMcnkLk() // TODO : probably shouldn't be here.
{
  std::vector<char> emptyData (0); 
  Chunk (emptyChunk); 

  McnrLk cMcnr(mcnr.toMcnrLk());

  Chunk (cMccv);
  if (!mccv.isEmpty())
    cMccv = mccv;

  Chunk cMcly ("YLCM", 0, emptyData);
  Mcrf cMcrf ("FRCM", 0, emptyData);
  Chunk cMcsh ("HSCM", 0, emptyData);
  Mcal (cMcal);

  McnkLk mcnkLk = McnkLk(mcnkHeader, mcvt, cMccv, cMcnr, cMcly, cMcrf, cMcsh, cMcal, emptyChunk, emptyChunk);
  return mcnkLk;
}

std::ostream & operator<<(std::ostream & os, const McnkCata & mcnkCata)
{
  os << "Chunk letters : " << mcnkCata.letters << std::endl;
  os << "Chunk givenSize : " << mcnkCata.givenSize << std::endl;

  os << std::endl;

  os << "flags : " << std::hex << "0x" << mcnkCata.mcnkHeader.flags << std::dec << std::endl;
  os << "indexX : " << mcnkCata.mcnkHeader.indexX << std::endl;
  os << "indexY : " << mcnkCata.mcnkHeader.indexY << std::endl;
  os << "areaID : " << mcnkCata.mcnkHeader.areaId << std::endl;
  os << "posX : " << mcnkCata.mcnkHeader.posX << std::endl;
  os << "posY : " << mcnkCata.mcnkHeader.posY << std::endl;
  os << "posZ : " << mcnkCata.mcnkHeader.posZ << std::endl;

  os << "------------------------------" << std::endl;

  os << mcnkCata.mcvt;
  os << mcnkCata.mccv;
  os << mcnkCata.mclv;
  os << mcnkCata.mcnr;
  os << mcnkCata.mclq;
  os << mcnkCata.mcse;
  os << mcnkCata.mcbb;

  os << "Hi, in here we're unknown !" << std::endl;
  os << std::endl;

  std::vector<Chunk>::const_iterator unknownIter;

  for (unknownIter = mcnkCata.terrainMcnkUnknown.begin() ; unknownIter != mcnkCata.terrainMcnkUnknown.end() ; ++unknownIter)
  {
    os << *unknownIter;
  }
  
  os << "------------------------------" << std::endl;
  return os;
}