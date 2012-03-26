#include <vector>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>
#include <wowfiles/alpha/McnkAlpha.h>
#include <wowfiles/alpha/McnrAlpha.h>
#include <wowfiles/alpha/McvtAlpha.h>
#include <wowfiles/lichking/McnrLk.h>
#include <utilities/Utilities.h>

McnkAlpha::McnkAlpha(std::ifstream & wdtAlphaFile, int offsetInFile, int adtNum) : Chunk(wdtAlphaFile, offsetInFile), adtNumber(adtNum)
{  
  const int mcnkHeaderSize (128);
  const int chunkLettersAndSize (8);
  const int headerStartOffset (offsetInFile);

  offsetInFile = chunkLettersAndSize + offsetInFile;

  mcnkHeader = Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcnkHeaderSize);

  const int mcvtOffset (0x018);
  const int mcvtSize (580);
  const int mcnrOffset (0x01C);
  const int mcnrSize (448);
  const int mclyOffset (0x020);
  const int mcrfOffset (0x024);
  const int mcshOffset (0x030);
  const int mcshSizeOffset (0x034);
  const int mcalOffset (0x028);
  const int mcalSizeOffset (0x02C);
  const int mcnkSizeOffset (0x05C);
  const int mclqOffset (0x064);

  offsetInFile = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::get<int>(mcnkHeader, mcvtOffset);
  std::vector<char> mcvtData (Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcvtSize));
  mcvt = McvtAlpha("TVCM", mcvtSize, mcvtData);

  offsetInFile = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::get<int>(mcnkHeader, mcnrOffset);
  std::vector<char> mcnrData (Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcnrSize));
  mcnrAlpha = McnrAlpha("RNCM", mcnrSize, mcnrData);

  offsetInFile = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::get<int>(mcnkHeader, mclyOffset);
  mcly = Chunk(wdtAlphaFile, offsetInFile);

  offsetInFile = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::get<int>(mcnkHeader, mcrfOffset);
  mcrf = Chunk(wdtAlphaFile, offsetInFile);

  offsetInFile = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::get<int>(mcnkHeader, mcshOffset);
  const int mcshSize (Utilities::get<int>(mcnkHeader, mcshSizeOffset));
  std::vector<char> mcshData (Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcshSize));
  mcsh = Chunk("HSCM", mcshSize, mcshData);

  offsetInFile = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::get<int>(mcnkHeader, mcalOffset);
  const int mcalSize (Utilities::get<int>(mcnkHeader, mcalSizeOffset));
  std::vector<char> mcalData (Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mcalSize));
  mcal = Mcal("LACM", mcalSize, mcalData);

  offsetInFile = headerStartOffset + mcnkHeaderSize + chunkLettersAndSize + Utilities::get<int>(mcnkHeader, mclqOffset);
  const int mclqSize (Utilities::get<int>(mcnkHeader, mcnkSizeOffset) - Utilities::get<int>(mcnkHeader, mclqOffset));
  std::vector<char> mclqData (Utilities::getCharVectorFromFile(wdtAlphaFile, offsetInFile, mclqSize));
  mclq = Chunk("QLCM", mclqSize, mclqData);
}

McnkLk McnkAlpha::toMcnkLk() const // TODO : yes I know, it's a whole mess again in there, I'm testing out things. It'll be better tomorrow :)
{
  std::vector<char> emptyData (0); 
  Chunk (emptyChunk); 

  McnrLk cMcnr (mcnrAlpha.toMcnrLk());

  // TODO : MCRF is plain wrong, copied from alpha since it's convenient (because of size).

  const int mcnkHeaderSize (128); // TODO : get rid of this
  const int chunkLettersAndSize (8);

  int offsetInHeader = chunkLettersAndSize + mcnkHeaderSize;

  const int emptyInt (0);

  McnkLkHeader (cMcnkHeader);// TODO : change that absolutely when I have a proper alpha header, it's temporary

  // flags
  memcpy(&cMcnkHeader.flags, &mcnkHeader[0], 4);

  // indexX
  memcpy(&cMcnkHeader.indexX, &mcnkHeader[0x04], 4);

  // indexY
  memcpy(&cMcnkHeader.indexY, &mcnkHeader[0x08], 4);

  // nLayers
  memcpy(&cMcnkHeader.nLayers, &mcnkHeader[0x10], 4);

  // nDoodadsRefs
  memcpy(&cMcnkHeader.m2Number, &emptyInt, sizeof(int));

  // MCVT
  memcpy(&cMcnkHeader.mcvtOffset, &offsetInHeader, sizeof(int));
  offsetInHeader = offsetInHeader + chunkLettersAndSize + mcvt.getRealSize();

  // MCNR
  memcpy(&cMcnkHeader.mcnrOffset, &offsetInHeader, sizeof(int));
  offsetInHeader = offsetInHeader + chunkLettersAndSize + mcnrAlpha.getRealSize();

  // MCLY
  memcpy(&cMcnkHeader.mclyOffset, &offsetInHeader, sizeof(int)); 
  offsetInHeader = offsetInHeader + chunkLettersAndSize + mcly.getRealSize();

  // MCRF
  memcpy(&cMcnkHeader.mcrfOffset, &offsetInHeader, sizeof(int)); 
  const int mcshOffset (offsetInHeader + chunkLettersAndSize + mcrf.getRealSize());  
  offsetInHeader = mcshOffset + chunkLettersAndSize + mcsh.getRealSize();

  // MCAL
  memcpy(&cMcnkHeader.mcalOffset, &offsetInHeader, sizeof(int)); 
  offsetInHeader = offsetInHeader + chunkLettersAndSize + mcal.getRealSize();
  const int mclqOffset (offsetInHeader);
  
  // sizeAlpha
  int tempData (mcal.getRealSize() + chunkLettersAndSize);
  memcpy(&cMcnkHeader.mcalSize, &tempData, sizeof(int)); 
  offsetInHeader = mcshOffset;

  // MCSH
  memcpy(&cMcnkHeader.mcshOffset, &mcshOffset, sizeof(int));
  
  // sizeShadow
  tempData = mcsh.getRealSize();
  memcpy(&cMcnkHeader.mcshSize, &tempData, sizeof(int));

  // areaID
  memcpy(&cMcnkHeader.areaId, &emptyInt, sizeof(int));
  
  // nMapObjRefs
  memcpy(&cMcnkHeader.wmoNumber, &emptyInt, sizeof(int));
  
  // holes
  memcpy(&cMcnkHeader.holes, &emptyInt, sizeof(int));

  // ReallyLowQualityTexturingMap
  memcpy(&cMcnkHeader.groundEffectsMap1, &mcnkHeader[0x44], 4);
  memcpy(&cMcnkHeader.groundEffectsMap2, &mcnkHeader[0x48], 4);
  memcpy(&cMcnkHeader.groundEffectsMap3, &mcnkHeader[0x4C], 4);
  memcpy(&cMcnkHeader.groundEffectsMap4, &mcnkHeader[0x50], 4);

  // predTex
  memcpy(&cMcnkHeader.predTex, &emptyInt, sizeof(int));
  
  // noEffectDoodad
  memcpy(&cMcnkHeader.nEffectDoodad, &emptyInt, sizeof(int));
  
  // MCSE
  memcpy(&cMcnkHeader.mcseOffset, &emptyInt, sizeof(int));
  
  // nSoundEmitters
  memcpy(&cMcnkHeader.nSndEmitters, &emptyInt, sizeof(int));
  offsetInHeader = mclqOffset;

  // MCLQ
  memcpy(&cMcnkHeader.mclqOffset, &offsetInHeader, sizeof(int)); 
  
  // sizeLiquid
  tempData = mclq.getRealSize() + chunkLettersAndSize;
  if (mclq.getRealSize() != 0) 
  {
    memcpy(&cMcnkHeader.mclqSize, &tempData, sizeof(int));
  }
  else 
  {
    memcpy(&cMcnkHeader.mclqSize, &emptyInt, sizeof(int));
  }

  // ------------- junk

  int adtX (adtNumber % 64);
  int adtY (adtNumber / 64);

  // PosX
  float temp ((adtX - 32) * 533.33333);
  memcpy(&cMcnkHeader.posX, &temp, sizeof(float));

  // PosY
  temp = ((adtY - 32) * 533.33333);
  memcpy(&cMcnkHeader.posY, &temp, sizeof(float));

  // ------------- end junk

  // PosZ (better results with 0 here)
  memcpy(&cMcnkHeader.posZ, &emptyInt, sizeof(int));
  
  // MCCV
  memcpy(&cMcnkHeader.mccvOffset, &emptyInt, sizeof(int));
  
  // MCLV
  memcpy(&cMcnkHeader.mclvOffset, &emptyInt, sizeof(int));
  
  // Unused
  memcpy(&cMcnkHeader.unused, &emptyInt, sizeof(int));

  Chunk cMcvt ("TVCM", 0, emptyData);
  cMcvt = mcvt.toMcvt();

  McnkLk mcnkLk = McnkLk(cMcnkHeader, cMcvt, emptyChunk, cMcnr, mcly, mcrf, mcsh, mcal, mclq, emptyChunk);
  return mcnkLk;
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