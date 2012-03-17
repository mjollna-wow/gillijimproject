#ifndef _WOWFILES_CATACLYSM_MCNKCATAOBJ0_H_
#define _WOWFILES_CATACLYSM_MCNKCATAOBJ0_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/Chunk.h>

class McnkCataObj0 : public Chunk
{
  public:

    McnkCataObj0(std::ifstream & file, int offsetInFile);
    McnkCataObj0(std::string letters, int givenSize, const std::vector<char> &data);

  private:

    std::vector<char> mcnkHeader;
    Chunk mcrd;
    Chunk mcrw;
};

#endif