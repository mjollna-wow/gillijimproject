#ifndef _WOWFILES_ALPHA_ADTALPHA_H_
#define _WOWFILES_ALPHA_ADTALPHA_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/WowChunkedFormat.h>
#include <wowfiles/Chunk.h>
#include <wowfiles/alpha/McnkAlpha.h>
#include <wowfiles/lichking/AdtLk.h>
#include <wowfiles/Mcin.h>
#include <wowfiles/Mddf.h>
#include <wowfiles/Modf.h>

class AdtAlpha : public WowChunkedFormat
{
  public:

    AdtAlpha(std::string & wdtAlphaName, int offsetInFile, int adtNum);
    int getXCoord() const;
    int getYCoord() const;
    AdtLk toAdtLk() const;

    friend std::ostream & operator<<(std::ostream & os, const AdtAlpha & adtAlpha);

  private:

    std::string getAdtFileName(const std::string & wdtName) const;

    std::vector<int> getM2IndicesForMmdx(const std::vector<int> & mddfIndices) const;

    int adtNumber;
    std::string adtFileName;
    Chunk mhdr;
    Mcin mcin;
    Chunk mtex;
    Mddf mddf;
    Modf modf;
    std::vector<McnkAlpha> mcnksAlpha;
};

#endif