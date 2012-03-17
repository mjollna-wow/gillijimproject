#ifndef _WOWFILES_LICHKING_MCNKLK_H_
#define _WOWFILES_LICHKING_MCNKLK_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mcal.h>
#include <wowfiles/lichking/McnrLk.h>

class McnkLk : public Chunk
{
  public:

    McnkLk(std::ifstream & file, int offsetInFile);
    McnkLk(std::string letters, int givenSize, const std::vector<char> &data);
    McnkLk(const std::vector<char> & cMcnkHeader
      , const Chunk & cMcvt
      , const Chunk & cMccv
      , const McnrLk & cMcnr
      , const Chunk & cMcly
      , const Chunk & cMcrf
      , const Chunk & cMcsh
      , const Mcal & cMcal
      , const Chunk & cMclq
      , const Chunk & cMcse
      );

    void toFile(std::ofstream & adtFile, std::string & adtFileName);
    int getWholeSize();

    friend std::ostream & operator<<(std::ostream & os, const McnkLk & mcnkLk);

  private:

    std::vector<char> mcnkHeader;
    Chunk mcvt;
    Chunk mccv;
    McnrLk mcnr;
    Chunk mcly;
    Chunk mcrf;
    Chunk mcsh;
    Mcal mcal;
    Chunk mclq;
    Chunk mcse;
};

#endif