#include <vector>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/ChunkHeaders.h>
#include <wowfiles/alpha/McnkAlpha.h>
#include <wowfiles/alpha/McnrAlpha.h>
#include <wowfiles/alpha/McvtAlpha.h>
#include <wowfiles/lichking/McnrLk.h>
#include <utilities/Utilities.h>

McnkAlpha::McnkAlpha(std::ifstream & wdtAlphaFile, int offsetInFile, const int headerSize, int adtNum) : Mcnk(wdtAlphaFile, offsetInFile, mcnkTerrainHeaderSize), adtNumber(adtNum)
{  
  const int headerStartOffset (offsetInFile);
  const int mcvtSize (580);
  const int mcnrSize (448);

  offsetInFile = chunkLettersAndSize + offsetInFile;

  mcnkHeader = Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcnkTerrainHeaderSize);
  getHeaderFromFile(wdtAlphaFile, offsetInFile, mcnkTerrainHeaderSize);

  offsetInFile = headerStartOffset + mcnkTerrainHeaderSize + chunkLettersAndSize + mcnkAlphaHeader.mcvtOffset;
  std::vector<char> mcvtData (Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcvtSize));
  mcvt = McvtAlpha("TVCM", mcvtSize, mcvtData);

  offsetInFile = headerStartOffset + mcnkTerrainHeaderSize + chunkLettersAndSize + mcnkAlphaHeader.mcnrOffset;
  std::vector<char> mcnrData (Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcnrSize));
  mcnrAlpha = McnrAlpha("RNCM", mcnrSize, mcnrData);

  offsetInFile = headerStartOffset + mcnkTerrainHeaderSize + chunkLettersAndSize + mcnkAlphaHeader.mclyOffset;
  mcly = Chunk(wdtAlphaFile, offsetInFile);

  offsetInFile = headerStartOffset + mcnkTerrainHeaderSize + chunkLettersAndSize + mcnkAlphaHeader.mcrfOffset;
  mcrf = Chunk(wdtAlphaFile, offsetInFile);

  offsetInFile = headerStartOffset + mcnkTerrainHeaderSize + chunkLettersAndSize + mcnkAlphaHeader.mcshOffset;
  std::vector<char> mcshData (Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcnkAlphaHeader.mcshSize));
  mcsh = Chunk("HSCM", mcnkAlphaHeader.mcshSize, mcshData);

  offsetInFile = headerStartOffset + mcnkTerrainHeaderSize + chunkLettersAndSize + mcnkAlphaHeader.mcalOffset;
  std::vector<char> mcalData (Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcnkAlphaHeader.mcalSize));
  mcal = Mcal("LACM", mcnkAlphaHeader.mcalSize, mcalData);

  offsetInFile = headerStartOffset + mcnkTerrainHeaderSize + chunkLettersAndSize + mcnkAlphaHeader.mclqOffset;
  const int mclqSize (mcnkAlphaHeader.mcnkChunksSize - mcnkAlphaHeader.mclqOffset);
  std::vector<char> mclqData (Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mclqSize));
  mclq = Chunk("QLCM", mclqSize, mclqData);
}

McnkLk McnkAlpha::toMcnkLk() const
{
  McnkHeader (cMcnkHeader);  
  int offsetInHeader (chunkLettersAndSize + mcnkTerrainHeaderSize);

  cMcnkHeader.flags = mcnkAlphaHeader.flags;
  cMcnkHeader.indexX = mcnkAlphaHeader.indexX;
  cMcnkHeader.indexY = mcnkAlphaHeader.indexY;
  cMcnkHeader.nLayers = mcnkAlphaHeader.nLayers;
  cMcnkHeader.m2Number = 0; // TODO
  
  cMcnkHeader.mcvtOffset = offsetInHeader;
  offsetInHeader = offsetInHeader + chunkLettersAndSize + mcvt.getRealSize();  
  
  cMcnkHeader.mcnrOffset = offsetInHeader;  
  offsetInHeader = offsetInHeader + chunkLettersAndSize + mcnrAlpha.getRealSize();  
  
  cMcnkHeader.mclyOffset = offsetInHeader; 
  offsetInHeader = offsetInHeader + chunkLettersAndSize + mcly.getRealSize();
  
  cMcnkHeader.mcrfOffset = offsetInHeader;   
  const int mcshOffset (offsetInHeader + chunkLettersAndSize + mcrf.getRealSize());  
  offsetInHeader = mcshOffset + chunkLettersAndSize + mcsh.getRealSize();  
  
  cMcnkHeader.mcalOffset = offsetInHeader;
  offsetInHeader = offsetInHeader + chunkLettersAndSize + mcal.getRealSize();
  const int mclqOffset (offsetInHeader);
  
  cMcnkHeader.mcalSize = mcal.getRealSize() + chunkLettersAndSize;  
  offsetInHeader = mcshOffset;
  
  cMcnkHeader.mcshOffset = mcshOffset;
  cMcnkHeader.mcshSize = mcsh.getRealSize();
  cMcnkHeader.areaId = 0; // TODO
  cMcnkHeader.wmoNumber = 0; // TODO  
  cMcnkHeader.holes = 0; // TODO
  cMcnkHeader.groundEffectsMap1 = mcnkAlphaHeader.groundEffectsMap1;    
  cMcnkHeader.groundEffectsMap2 = mcnkAlphaHeader.groundEffectsMap2; 
  cMcnkHeader.groundEffectsMap3 = mcnkAlphaHeader.groundEffectsMap3; 
  cMcnkHeader.groundEffectsMap4 = mcnkAlphaHeader.groundEffectsMap4;   
  cMcnkHeader.predTex = 0; 
  cMcnkHeader.nEffectDoodad = 0;  
  cMcnkHeader.mcseOffset = 0;    
  cMcnkHeader.nSndEmitters = 0; 
  cMcnkHeader.mclqOffset = mclqOffset; 
  
  if (mclq.getRealSize() != 0) 
    cMcnkHeader.mclqSize = mclq.getRealSize() + chunkLettersAndSize; 
  else 
    cMcnkHeader.mclqSize = 0;

  // ------------- junk

  int adtX (adtNumber % 64);
  int adtY (adtNumber / 64);

  cMcnkHeader.posX = ((adtX - 32) * 533.33333); 
  cMcnkHeader.posY = ((adtY - 32) * 533.33333); 

  // ------------- end junk

  cMcnkHeader.posZ = 0;
  cMcnkHeader.mccvOffset = 0;
  cMcnkHeader.mclvOffset = 0;
  cMcnkHeader.unused = 0;  

  // TODO : MCRF is plain wrong, copied from alpha since it's convenient (because of size).  
  
  std::vector<char> emptyData (0); 
  Chunk (emptyChunk); 

  McnrLk cMcnr (mcnrAlpha.toMcnrLk());  
  
  Chunk cMcvt ("TVCM", 0, emptyData);
  cMcvt = mcvt.toMcvt();

  McnkLk mcnkLk = McnkLk(cMcnkHeader, cMcvt, emptyChunk, cMcnr, mcly, mcrf, mcsh, mcal, mclq, emptyChunk);
  return mcnkLk;
}

void McnkAlpha::getHeaderFromFile(std::ifstream & adtFile, const int position, const int length)
{
  adtFile.seekg(position, std::ios::beg);
  char * dataBuffer = new char[length];

  adtFile.read(dataBuffer, length);

  mcnkAlphaHeader = *reinterpret_cast<McnkAlphaHeader*>(dataBuffer);

  delete[] dataBuffer;
}

std::ostream & operator<<(std::ostream & os, const McnkAlpha & mcnkAlpha)
{
  os << "Chunk letters : " << mcnkAlpha.letters << std::endl;
  os << "Chunk givenSize : " << mcnkAlpha.givenSize << std::endl;

  os << "------------------------------" << std::endl;

  os << "Header : " << std::endl;
  
  // TODO : make this look nicer. Somehow.
 
  os << "#0x00 Flags \t\t\t\t\t\t: 0x" << std::hex << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x00) << std::dec << std::endl;
  os << "#0x04 IndexX\t\t\t\t\t\t: " << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x04) << std::dec << std::endl;
  os << "#0x08 IndexY\t\t\t\t\t\t: " << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x08) << std::dec << std::endl;
  os << "#0x0C Relative MCNK height\t\t\t: " << Utilities::get<float>(mcnkAlpha.mcnkHeader, 0x0C) << std::endl; 
  os << "#0x10 Layers number\t\t\t\t\t: " << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x10) << std::endl;
  os << "#0x14 WMOs number ?\t\t\t\t\t: " << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x14) << std::endl; 
  os << "#0x18 MCVT offset\t\t\t\t\t: 0x" << std::hex << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x18) << std::dec << std::endl; 
  os << "#0x1C MCNR offset\t\t\t\t\t: 0x" << std::hex << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x1C) << std::dec << std::endl; 
  os << "#0x20 MCLY offset\t\t\t\t\t: 0x" << std::hex << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x20) << std::dec << std::endl;
  os << "#0x24 MCRF offset\t\t\t\t\t: 0x" << std::hex << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x24) << std::dec << std::endl; 
  os << "#0x28 MCAL offset\t\t\t\t\t: 0x" << std::hex << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x28) << std::dec << std::endl; 
  os << "#0x2C MCAL size\t\t\t\t\t\t: " << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x2C) << std::dec << std::endl; 
  os << "#0x30 MCSH offset\t\t\t\t\t: 0x" << std::hex << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x30) << std::dec << std::endl;
  os << "#0x34 MCSH size\t\t\t\t\t\t: " << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x34) << std::dec << std::endl; 
  os << "#0x38 -> #0x3B\t\t\t\t\t\t: 0x" << std::hex << (int(mcnkAlpha.mcnkHeader[0x38])) << " 0x" << int(mcnkAlpha.mcnkHeader[0x39]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x3A]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x3B]) << std::dec << std::endl; 
  os << "#0x3C Doodads number\t\t\t\t: " << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x3C) << std::endl;
  os << "#0x40 -> #0x43\t\t\t\t\t\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x40]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x41]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x42]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x43]) << std::dec << std::endl;
  os << "#0x44 -> #0x47 Low Texturing map\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x44]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x45]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x46]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x47]) << std::dec << std::endl;
  os << "#0x48 -> #0x4B Low Texturing map\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x48]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x49]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x4A]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x4B]) << std::dec << std::endl;
  os << "#0x4C -> #0x4F Low Texturing map\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x4C]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x4D]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x4E]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x4F]) << std::dec << std::endl;
  os << "#0x50 -> #0x53 Low Texturing map\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x50]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x51]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x52]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x53]) << std::dec << std::endl;
  os << "#0x54 -> #0x57\t\t\t\t\t\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x54]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x55]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x56]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x57]) << std::dec << std::endl; 
  os << "#0x58 -> #0x5B\t\t\t\t\t\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x58]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x59]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x5A]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x5B]) << std::dec << std::endl; 
  //os << "#0x58 (try)\t\t\t\t\t: " << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x58) << std::dec << std::endl; 
  os << "#0x5C MCNK size (minus header)\t\t: " << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x5C) << std::endl; 
  os << "#0x60 -> #0x63\t\t\t\t\t\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x60]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x61]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x62]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x63]) << std::dec << std::endl;
  os << "#0x64 MCLQ offset\t\t\t\t\t: 0x" << std::hex << Utilities::get<int>(mcnkAlpha.mcnkHeader, 0x64) << std::dec << std::endl; 
  os << "#0x68 -> #0x6B\t\t\t\t\t\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x68]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x69]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x6A]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x6B]) << std::dec << std::endl; 
  os << "#0x6C -> #0x6F\t\t\t\t\t\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x6C]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x6D]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x6E]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x6F]) << std::dec << std::endl; 
  os << "#0x70 -> #0x73\t\t\t\t\t\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x70]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x71]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x72]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x73]) << std::dec << std::endl;
  os << "#0x74 -> #0x77\t\t\t\t\t\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x74]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x75]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x76]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x77]) << std::dec << std::endl; 
  os << "#0x78 -> #0x7B\t\t\t\t\t\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x78]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x79]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x7A]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x7B]) << std::dec << std::endl; 
  os << "#0x7C -> #0x7F\t\t\t\t\t\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x7C]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x7D]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x7E]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x7F]) << std::dec << std::endl;

  os << "------------------------------" << std::endl;

  os << mcnkAlpha.mcvt;
  os << mcnkAlpha.mcnrAlpha;
  os << mcnkAlpha.mcly;
  os << mcnkAlpha.mcrf;
  os << mcnkAlpha.mcsh;
  os << mcnkAlpha.mcal;
  os << mcnkAlpha.mclq;

  os << "------------------------------" << std::endl;
  return os;
}