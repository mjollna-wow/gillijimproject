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

struct TestHeader
{
    int flags;
    int ix;
    int iy;
    int nLayers;
    int nDoodadRefs;
    int ofsHeight;
    int ofsNormal;
    int ofsLayer;
    int ofsRefs;
    int ofsAlpha;
    int sizeAlpha;
    int ofsShadow;
    int sizeShadow;
    int areaid;
    int nMapObjRefs;
    int holes;
    short s1;
    short s2;
    int d1;
    int d2;
    int d3;
    int predTex;
    int nEffectDoodad;
    int ofsSndEmitters;
    int nSndEmitters;
    int ofsLiquid;
    int sizeLiquid;
    float  zpos;
    float  xpos;
    float  ypos;
    int ofsMCCV;
    int unused1;
    int unused2;
};

#endif