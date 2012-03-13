#ifndef ADT_ALPHA_H_
#define ADT_ALPHA_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../WowChunkedFormat.h"
#include "../Chunk.h"
#include "McnkAlpha.h"
#include "../lichking/AdtLk.h"
#include "../Mcin.h"

class AdtAlpha : public WowChunkedFormat
{
  public:

    AdtAlpha(std::string & wdtAlphaName, int offsetInFile, int adtNum);
    int getXCoord() const;
    int getYCoord() const;
    AdtLk toAdtLk() const;

    void toFile();

    friend std::ostream & operator<<(std::ostream & os, const AdtAlpha & adtAlpha);

  private:

    std::string getAdtFileName(const std::string & wdtName) const;

    int adtNumber;
    std::string adtFileName;
    Chunk mhdr;
    Mcin mcin;
    Chunk mtex;
    Chunk mddf;
    Chunk modf;
    std::vector<McnkAlpha> mcnksAlpha;
};

#endif