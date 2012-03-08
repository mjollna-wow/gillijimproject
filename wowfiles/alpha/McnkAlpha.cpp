#include <vector>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include "../Chunk.h"
#include "McnkAlpha.h"
#include "McnrAlpha.h"
#include "../lichking/McnrLk.h"
#include "../../utilities/Utilities.h"

McnkAlpha::McnkAlpha(std::ifstream & wdtAlphaFile, int offsetInFile) : Chunk(wdtAlphaFile, offsetInFile)
{
  const int mcnkHeaderSize = 128;
  const int chunkLettersAndSize = 8;
  const int headerStartOffset = offsetInFile;

  offsetInFile = chunkLettersAndSize + offsetInFile;

  mcnkHeader = Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcnkHeaderSize);

  const int mcvtOffset = 0x018;
  const int mcvtSize = 580;
  const int mcnrOffset = 0x01C;
  const int mcnrSize = 448;
  const int mclyOffset = 0x020;
  const int mcrfOffset = 0x024;
  const int mcshOffset = 0x030;
  const int mcshSizeOffset = 0x034;
  const int mcalOffset = 0x028;
  const int mcalSizeOffset = 0x02C;
  const int mcnkSizeOffset = 0x05C;
  const int mclqOffset = 0x064;

  offsetInFile = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::getIntFromCharVector(mcnkHeader, mcvtOffset);
  std::vector<char> mcvtData = Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcvtSize);
  mcvt = Chunk("TVCM", mcvtSize, mcvtData);

  offsetInFile = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::getIntFromCharVector(mcnkHeader, mcnrOffset);
  std::vector<char> mcnrData = Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcnrSize);
  mcnrAlpha = McnrAlpha("RNCM", mcnrSize, mcnrData);

  offsetInFile = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::getIntFromCharVector(mcnkHeader, mclyOffset);
  mcly = Chunk(wdtAlphaFile, offsetInFile);

  offsetInFile = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::getIntFromCharVector(mcnkHeader, mcrfOffset);
  mcrf = Chunk(wdtAlphaFile, offsetInFile);

  offsetInFile = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::getIntFromCharVector(mcnkHeader, mcshOffset);
  int mcshSize = Utilities::getIntFromCharVector(mcnkHeader, mcshSizeOffset);
  std::vector<char> mcshData = Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcshSize);
  mcsh = Chunk("HSCM", mcshSize, mcshData);

  offsetInFile = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::getIntFromCharVector(mcnkHeader, mcalOffset);
  int mcalSize = Utilities::getIntFromCharVector(mcnkHeader, mcalSizeOffset);
  std::vector<char> mcalData = Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcalSize);
  mcal = Chunk("LACM", mcalSize, mcalData);

  offsetInFile = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::getIntFromCharVector(mcnkHeader, mclqOffset);
  int mclqSize = Utilities::getIntFromCharVector(mcnkHeader, mcnkSizeOffset) - Utilities::getIntFromCharVector(mcnkHeader, mclqOffset);
  std::vector<char> mclqData = Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mclqSize);
  mclq = Chunk("QLCM", mclqSize, mclqData);

  // TODO (later) : constructor doesn't fill McnkAlpha.data
}

McnkLk McnkAlpha::toMcnkLk() const
{
	std::vector<char> emptyData(0); 
  Chunk emptyChunk = Chunk(); 

  McnrLk cMcnr = mcnrAlpha.toMcnrLk();

  // TODO : MCRF is plain wrong, copied from alpha since it's convenient (because of size).

  const int mcnkHeaderSize = 128;
  const int chunkLettersAndSize = 8;

  int offsetInHeader = chunkLettersAndSize + mcnkHeaderSize;

  std::vector<char> cMcnkHeader = emptyData;
  std::vector<char> emptyInt(4);
  std::vector<char> tempData(0);

  tempData = Utilities::getCharSubVector(mcnkHeader, 0x00, 4); 
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // flags

  tempData = Utilities::getCharSubVector(mcnkHeader, 0x04, 4); 
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // indexX
  
  tempData = Utilities::getCharSubVector(mcnkHeader, 0x08, 4); 
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // indexY
  
  tempData = Utilities::getCharSubVector(mcnkHeader, 0x10, 4); 
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // nLayers
  
  cMcnkHeader.insert(cMcnkHeader.end(), emptyInt.begin(), emptyInt.end()); // nDoodadsRefs

  tempData = Utilities::getCharVectorFromInt(offsetInHeader);
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // MCVT
  offsetInHeader = offsetInHeader + chunkLettersAndSize + mcvt.getRealSize();

  tempData = Utilities::getCharVectorFromInt(offsetInHeader);
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // MCNR
  offsetInHeader = offsetInHeader + chunkLettersAndSize + mcnrAlpha.getRealSize();

  tempData = Utilities::getCharVectorFromInt(offsetInHeader);
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // MCLY
  offsetInHeader = offsetInHeader + chunkLettersAndSize + mcly.getRealSize();

  tempData = Utilities::getCharVectorFromInt(offsetInHeader);
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // MCRF
  const int mcshOffset = offsetInHeader + chunkLettersAndSize + mcrf.getRealSize();
  
  offsetInHeader = mcshOffset + chunkLettersAndSize + mcsh.getRealSize();

  tempData = Utilities::getCharVectorFromInt(offsetInHeader);
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // MCAL
  offsetInHeader = offsetInHeader + chunkLettersAndSize + mcal.getRealSize();
  const int mclqOffset = offsetInHeader;
  
  tempData = Utilities::getCharVectorFromInt(mcal.getRealSize() + chunkLettersAndSize);
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // sizeAlpha
  offsetInHeader = mcshOffset;

  tempData = Utilities::getCharVectorFromInt(mcshOffset);
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // MCSH
  
  tempData = Utilities::getCharVectorFromInt(mcsh.getRealSize());
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // sizeShadow

  cMcnkHeader.insert(cMcnkHeader.end(), emptyInt.begin(), emptyInt.end()); // areaID
  cMcnkHeader.insert(cMcnkHeader.end(), emptyInt.begin(), emptyInt.end()); // nMapObjRefs
  cMcnkHeader.insert(cMcnkHeader.end(), emptyInt.begin(), emptyInt.end()); // holes

  tempData = Utilities::getCharSubVector(mcnkHeader, 0x44, 16); 
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // ReallyLowQualityTexturingMap ???

  cMcnkHeader.insert(cMcnkHeader.end(), emptyInt.begin(), emptyInt.end()); // predTex
  cMcnkHeader.insert(cMcnkHeader.end(), emptyInt.begin(), emptyInt.end()); // noEffectDoodad
  cMcnkHeader.insert(cMcnkHeader.end(), emptyInt.begin(), emptyInt.end()); // MCSE
  cMcnkHeader.insert(cMcnkHeader.end(), emptyInt.begin(), emptyInt.end()); // nSoundEmitters
  offsetInHeader = mclqOffset;

  tempData = Utilities::getCharVectorFromInt(offsetInHeader);
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // MCLQ
  
  tempData = Utilities::getCharVectorFromInt(mclq.getRealSize() + chunkLettersAndSize);  
  if (mclq.getRealSize() != 0)
  {
    cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // sizeLiquid
  }
  else 
  {
    cMcnkHeader.insert(cMcnkHeader.end(), emptyInt.begin(), emptyInt.end());
  }

  // junk

  float mcnkWidth = 33.33333333333;
  int adtX = 34; // TODO : remove this.
  int adtY = 32; // TODO : remove this.

  const int mcnkX = Utilities::getIntFromCharVector(Utilities::getCharSubVector(mcnkHeader, 0x04, 4), 0);
  const int mcnkY = Utilities::getIntFromCharVector(Utilities::getCharSubVector(mcnkHeader, 0x08, 4), 0);

  float temp = (((adtX - 32) * 533.333333));// + 266.666666)) + (mcnkWidth * mcnkX);//-(((adtX - 33) * 533.33333)) + (mcnkWidth * mcnkX);

  tempData = Utilities::getCharVectorFromFloat(temp);
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // PosX

  temp = (((adtY - 32) * 533.333333));//(((adtY - 32) * 533.333333 + 266.666666)) + (mcnkWidth * mcnkY);//-(((adtY - 31) * 533.33333)) + (mcnkWidth * mcnkY);

  tempData = Utilities::getCharVectorFromFloat(temp);
  cMcnkHeader.insert(cMcnkHeader.end(), tempData.begin(), tempData.end()); // PosY

  // end junk

  cMcnkHeader.insert(cMcnkHeader.end(), emptyInt.begin(), emptyInt.end()); // PosZ (better results with 0 here)
  
  cMcnkHeader.insert(cMcnkHeader.end(), emptyInt.begin(), emptyInt.end()); // MCCV
  cMcnkHeader.insert(cMcnkHeader.end(), emptyInt.begin(), emptyInt.end()); // MCLV
  cMcnkHeader.insert(cMcnkHeader.end(), emptyInt.begin(), emptyInt.end()); // Unused

  // more junk

  std::vector<char> cMcvtData(0);
  int i;

  for (i = mcvt.getRealSize() ; i < 0 ; i++)
  {
    //cMcvtData.push_back();
  }
  Chunk cMcvt = Chunk();

  // end more junk

	McnkLk mcnkLk = McnkLk(cMcnkHeader, mcvt, emptyChunk, cMcnr, mcly, mcrf, mcsh, mcal, mclq, emptyChunk);
	return mcnkLk;
}

std::ostream & operator<<(std::ostream & os, const McnkAlpha & mcnkAlpha)
{
  os << "Chunk letters : " << mcnkAlpha.letters << std::endl;
  os << "Chunk givenSize : " << mcnkAlpha.givenSize << std::endl;

  os << "------------------------------" << std::endl;

  os << "Header : " << std::endl;

  /*int currentHeaderByte;
  for (currentHeaderByte = 0 ; currentHeaderByte < mcnkAlpha.mcnkHeader.size() ; currentHeaderByte++)
  {
    os << "#0x" << std::hex << currentHeaderByte << " : 0x" << int(mcnkAlpha.mcnkHeader[currentHeaderByte]) << std::dec << std::endl;
  }*/
  
  // TODO : make this look nicer. Somehow.
 
  os << "#0x00 Flags \t\t\t\t\t\t: 0x" << std::hex << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x00) << std::dec << std::endl;
  os << "#0x04 IndexX\t\t\t\t\t\t: " << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x04) << std::dec << std::endl;
  os << "#0x08 IndexY\t\t\t\t\t\t: " << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x08) << std::dec << std::endl;
  os << "#0x0C Relative MCNK height\t\t\t: " << Utilities::getFloatFromCharVector(mcnkAlpha.mcnkHeader, 0x0C) << std::endl; 
  os << "#0x10 Layers number\t\t\t\t\t: " << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x10) << std::endl;
  os << "#0x14 WMOs number ?\t\t\t\t\t: " << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x14) << std::endl; 
  os << "#0x18 MCVT offset\t\t\t\t\t: 0x" << std::hex << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x18) << std::dec << std::endl; 
  os << "#0x1C MCNR offset\t\t\t\t\t: 0x" << std::hex << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x1C) << std::dec << std::endl; 
  os << "#0x20 MCLY offset\t\t\t\t\t: 0x" << std::hex << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x20) << std::dec << std::endl;
  os << "#0x24 MCRF offset\t\t\t\t\t: 0x" << std::hex << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x24) << std::dec << std::endl; 
  os << "#0x28 MCAL offset\t\t\t\t\t: 0x" << std::hex << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x28) << std::dec << std::endl; 
  os << "#0x2C MCAL size\t\t\t\t\t\t: " << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x2C) << std::dec << std::endl; 
  os << "#0x30 MCSH offset\t\t\t\t\t: 0x" << std::hex << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x30) << std::dec << std::endl;
  os << "#0x34 MCSH size\t\t\t\t\t\t: " << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x34) << std::dec << std::endl; 
  os << "#0x38 -> #0x3B\t\t\t\t\t\t: 0x" << std::hex << (int(mcnkAlpha.mcnkHeader[0x38])) << " 0x" << int(mcnkAlpha.mcnkHeader[0x39]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x3A]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x3B]) << std::dec << std::endl; 
  os << "#0x3C Doodads number\t\t\t\t: " << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x3C) << std::endl;
  os << "#0x40 -> #0x43\t\t\t\t\t\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x40]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x41]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x42]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x43]) << std::dec << std::endl;
  os << "#0x44 -> #0x47 Low Texturing map\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x44]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x45]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x46]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x47]) << std::dec << std::endl;
  os << "#0x48 -> #0x4B Low Texturing map\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x48]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x49]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x4A]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x4B]) << std::dec << std::endl;
  os << "#0x4C -> #0x4F Low Texturing map\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x4C]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x4D]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x4E]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x4F]) << std::dec << std::endl;
  os << "#0x50 -> #0x53 Low Texturing map\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x50]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x51]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x52]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x53]) << std::dec << std::endl;
  os << "#0x54 -> #0x57\t\t\t\t\t\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x54]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x55]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x56]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x57]) << std::dec << std::endl; 
  os << "#0x58 -> #0x5B\t\t\t\t\t\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x58]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x59]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x5A]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x5B]) << std::dec << std::endl; 
  //os << "#0x58 (try)\t\t\t\t\t: " << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x58) << std::dec << std::endl; 
  os << "#0x5C MCNK size (minus header)\t\t: " << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x5C) << std::endl; 
  os << "#0x60 -> #0x63\t\t\t\t\t\t: 0x" << std::hex << int(mcnkAlpha.mcnkHeader[0x60]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x61]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x62]) << " 0x" << int(mcnkAlpha.mcnkHeader[0x63]) << std::dec << std::endl;
  os << "#0x64 MCLQ offset\t\t\t\t\t: 0x" << std::hex << Utilities::getIntFromCharVector(mcnkAlpha.mcnkHeader, 0x64) << std::dec << std::endl; 
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