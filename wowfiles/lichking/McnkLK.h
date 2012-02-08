#ifndef MCNKLK_H_
#define MCNKLK_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "../Chunk.h"
#include "McnrLk.h"

class McnkLk : public Chunk
{
  public:

    McnkLk(std::ifstream & file, int offsetInFile);
    McnkLk(const std::vector<char> & fullAdtData, int position, int sizeAdjustments);
    McnkLk(std::string letters, int givenSize, const std::vector<char> &data);
    friend std::ostream & operator<<(std::ostream & os, const McnkLk & mcnkLk);

  private:

    std::vector<char> mcnkHeader;
    Chunk mcvt;
    Chunk mccv;
    McnrLk mcnr;
    Chunk mcly;
    Chunk mcrf;
    Chunk mcsh;
    Chunk mcal;
    Chunk mclq;
    Chunk mcse;
};

#endif