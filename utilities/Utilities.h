#ifndef _UTILITIES_UTILITIES_H_
#define _UTILITIES_UTILITIES_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

namespace Utilities
{
  int getIntFromCharVector(const std::vector<char> & someData, int offset);
  float getFloatFromCharVector(const std::vector<char> & someData, int offset);
  std::string getStringFromCharVector(const std::vector<char> & someData, int start, int stringLength);
  std::vector<char> getCharSubVector(const std::vector<char> & someData, int start, int length);

  std::string getLettersFromFile(std::ifstream & adtFile, int position);
  int getIntFromFile(std::ifstream & adtFile, int position);
  std::vector<char> getCharVectorFromFile(std::ifstream & adtFile, int position, int length);

  std::vector<char> getCharVectorFromInt(const int someValue);
  std::vector<char> getCharVectorFromFloat(const float someValue);

  bool flagsExist(const int & bitmask, const int & whichFlags);

  int getAdtVersion(std::string & adtName);
  int getWdtVersion(std::string & wdtName);
};

#endif