#include <vector>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include "../Chunk.h"
#include "McnkAlpha.h"
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
  mcnr = Chunk("RNCM", mcnrSize, mcnrData);

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
}

McnkLk McnkAlpha::toMcnkLk() const
{
	std::vector<char> emptyData(0); // TODO : fill emptiness

	std::vector<char> cMcnkHeader = emptyData;
  Chunk cMcvt = Chunk("TVCM", 0, emptyData);
	Chunk cMccv = Chunk("VCCM", 0, emptyData);
  McnrLk cMcnr = McnrLk("RNCM", 0, emptyData);
  Chunk cMcly = Chunk("YLCM", 0, emptyData);
  Chunk cMcrf = Chunk("FRCM", 0, emptyData);
  Chunk cMcsh = Chunk("HSCM", 0, emptyData);
  Chunk cMcal = Chunk("LACM", 0, emptyData);
  Chunk cMclq = Chunk("QLCM", 0, emptyData);
	Chunk cMcse = Chunk("ESCM", 0, emptyData);

	McnkLk mcnkLk = McnkLk(cMcnkHeader, cMcvt, cMccv, cMcnr, cMcly, cMcrf, cMcsh, cMcal, cMclq, cMcse);
	return mcnkLk;
}

std::ostream & operator<<(std::ostream & os, const McnkAlpha & mcnkAlpha)
{
  os << "Chunk letters : " << mcnkAlpha.letters << std::endl;
  os << "Chunk givenSize : " << mcnkAlpha.givenSize << std::endl;

  os << "------------------------------" << std::endl;

  os << mcnkAlpha.mcvt;
  os << mcnkAlpha.mcnr;
  os << mcnkAlpha.mcly;
  os << mcnkAlpha.mcrf;
  os << mcnkAlpha.mcsh;
  os << mcnkAlpha.mcal;
  os << mcnkAlpha.mclq;

  os << "------------------------------" << std::endl;
  return os;
}