#ifndef _UTILITIES_UTILITIES_H_
#define _UTILITIES_UTILITIES_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

namespace Utilities
{
  template<typename T> T get (const std::vector<char>& data, std::size_t offset)
  {
    return T (*reinterpret_cast<const T*> (&data[offset]));
  }

  std::string getStringFromCharVector(const std::vector<char> & someData, const int start, const int stringLength);

  std::string getLettersFromFile(std::ifstream & adtFile, const int position);
  int getIntFromFile(std::ifstream & adtFile, const int position);
  std::vector<char> getCharVectorFromFile(std::ifstream & adtFile, const int position, const int length);

  std::vector<char> getCharVectorFromInt(const int someValue);
  std::vector<char> getCharVectorFromFloat(const float someValue);

  bool flagsExist(const int & bitmask, const int & whichFlags);

  int getAdtVersion(const std::string & adtName);
  int getWdtVersion(const std::string & wdtName);
};

struct McnkLkHeader
{
    int flags;
    int indexX;
    int indexY;
    int nLayers;
    int m2Number;
    int mcvtOffset;
    int mcnrOffset;
    int mclyOffset;
    int mcrfOffset;
    int mcalOffset;
    int mcalSize;
    int mcshOffset;
    int mcshSize;
    int areaId;
    int wmoNumber;
    int holes;
    int groundEffectsMap1;
    int groundEffectsMap2;
    int groundEffectsMap3;
    int groundEffectsMap4;
    int predTex;
    int nEffectDoodad;
    int mcseOffset;
    int nSndEmitters;
    int mclqOffset;
    int mclqSize;
    float posX;
    float posY;
    float posZ;
    int mccvOffset;
    int mclvOffset;
    int unused;
};

#endif