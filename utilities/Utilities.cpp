#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "Utilities.h"

namespace Utilities
{
  int getIntFromCharVector(const std::vector<char> & someData, int offset)
  {
    std::vector<char>::const_iterator dataIter;
    char curValues[4];
    int i = 0;
	
    for (dataIter = someData.begin() + offset ; dataIter != someData.begin() + offset + 4 ; ++dataIter)
    {
      curValues[i] = *dataIter;
      i++;
    }
    memcpy(&offset, curValues, sizeof(offset));
	
    return offset;
  }

  float getFloatFromCharVector(const std::vector<char> & someData, int offset)
  {
    float result;
    std::vector<char>::const_iterator dataIter;
    char curValues[4];
    int i = 0;
	
    for (dataIter = someData.begin() + offset ; dataIter != someData.begin() + offset + 4 ; ++dataIter)
    {
      curValues[i] = *dataIter;
      i++;
    }
    memcpy(&result, curValues, sizeof(result));
	
    return result;
  }

  std::string getStringFromCharVector(const std::vector<char> & someData, int start, int stringLength)
  {
    std::string letters = "";
	
    std::vector<char>::const_iterator adtIter;
    for (adtIter = someData.begin() + start ; adtIter != someData.begin() + start + stringLength ; ++adtIter)
    {
      letters = letters + *adtIter;
    }
    return letters;
  }

  std::vector<char> getCharSubVector(const std::vector<char> & someData, int start, int length)
  {
    std::vector<char> subVector;
    std::vector<char>::const_iterator dataIter;

    for (dataIter = someData.begin() + start ; dataIter != someData.begin() + start + length ; ++dataIter)
    {
      subVector.push_back(*dataIter);
    }

    return subVector;
  }

  std::string getLettersFromFile(std::ifstream & adtFile, int position)
  {
    std::string letters = "";

    adtFile.seekg(position, std::ios::beg);
    char lettersBuffer[4];
    adtFile.read(lettersBuffer, 4);

    int i;
    for (i = 0 ; i < sizeof(lettersBuffer) ; i++)
    {
      letters = letters + lettersBuffer[i];
    }
    return letters;
  }

  int getIntFromFile(std::ifstream & adtFile, int position)
  {
    int givenSize = 0;

    adtFile.seekg(position, std::ios::beg);
    char sizeBuffer[4];
    adtFile.read(sizeBuffer, 4);

    memcpy(&givenSize, sizeBuffer, sizeof(givenSize));

    return givenSize;
  }

  std::vector<char> getCharVectorFromFile(std::ifstream & adtFile, int position, int length)
  {
    std::vector<char> data(0);

    adtFile.seekg(position, std::ios::beg);

    char * dataBuffer = new char[length];

    adtFile.read(dataBuffer, length);

    int i;
    for (i = 0 ; i < length ; i++)
    {
      data.push_back(dataBuffer[i]);
    } 

    delete[] dataBuffer;

    return data;
  }

  std::vector<char> getCharVectorFromInt(const int someValue)
  {
    std::vector<char> charVector(0);

    char size[4];
    size[0] = someValue & 0xff;
    charVector.push_back(size[0]);
    size[1] = (someValue >> 8)  & 0xff;
    charVector.push_back(size[1]);
    size[2] = (someValue >> 16) & 0xff;
    charVector.push_back(size[2]);
    size[3] = (someValue >> 24) & 0xff;
    charVector.push_back(size[3]);

    return charVector;
  }

  std::vector<char> getCharVectorFromFloat(const float someValue)
  {
    std::vector<char> charVector(0);
    unsigned char * tempStorage = (unsigned char *)&someValue;

    int i;
    for (i = 0 ; i < sizeof(someValue) ; i++)
    {
      charVector.push_back(tempStorage[i]);
    }

    return charVector;
  }

  bool flagsExist(const int & bitmask, const int & whichFlags)
  {
    return (bitmask & whichFlags) == whichFlags;
  }

  int getAdtVersion(std::string & adtName)
  {
    std::ifstream adtFile;
    adtFile.open(adtName, std::ios::binary);

    const int mcinOffset = 0x18;
    adtFile.seekg(mcinOffset, std::ios::beg);

    int value;
    adtFile.read((char*)&value, sizeof(int)); 

    adtFile.close();

    if (value == 0)
      return 4;
    else 
      return 3;
  }
  
  int getWdtVersion(std::string & wdtName)
  {
    std::ifstream wdtFile;
    wdtFile.open(wdtName, std::ios::binary);

    const int mainOffset = 0x98;
    wdtFile.seekg(mainOffset, std::ios::beg);

    int value;
    wdtFile.read((char*)&value, sizeof(int)); 

    wdtFile.close();

    if (value == 65536)
      return 0;
    else
      return 1;
  }
}