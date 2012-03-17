#ifndef _WOWFILES_CATACLYSM_MCNKCATATEX0_H_
#define _WOWFILES_CATACLYSM_MCNKCATATEX0_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>

class McnkCataTex0 : public Chunk
{
  public:

    McnkCataTex0(std::ifstream & file, int offsetInFile);
    McnkCataTex0(std::string letters, int givenSize, const std::vector<char> &data);

    friend std::ostream & operator<<(std::ostream & os, const McnkCataTex0 & mcnkCataTex0);

  private:

    Chunk mcly;
    Chunk mcal;
    /*Chunk mcmt;*/
};

#endif