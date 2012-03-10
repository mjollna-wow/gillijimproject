#ifndef MCNKALPHA_H_
#define MCNKALPHA_H_

#include <vector>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include "../Chunk.h"
#include "McnrAlpha.h"
#include "../lichking/McnkLk.h"
#include "../Mcal.h"

class McnkAlpha : public Chunk
{
  public:

    McnkAlpha(std::ifstream & wdtAlphaFile, int offsetInFile, int adtNum);
    //McnkAlpha(std::string letters, int givenSize, const std::vector<char> &data);
    McnkLk toMcnkLk() const;

    friend std::ostream & operator<<(std::ostream & os, const McnkAlpha & mcnkAlpha);

  private:

    int adtNumber;
    std::vector<char> mcnkHeader;
    Chunk mcvt;
    McnrAlpha mcnrAlpha;
    Chunk mcly;
    Chunk mcrf;
    Chunk mcsh;
    Mcal mcal;
    Chunk mclq;
};

#endif
