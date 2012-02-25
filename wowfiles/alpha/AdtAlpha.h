#ifndef ADT_ALPHA_H_
#define ADT_ALPHA_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../Chunk.h"
#include "McnkAlpha.h"
#include "../lichking/AdtLk.h"
#include "../Mcin.h"

class AdtAlpha
{
  public:

    AdtAlpha(std::string & wdtAlphaName, int offsetInFile, int adtNum);
    AdtLk toAdtLk() const;

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