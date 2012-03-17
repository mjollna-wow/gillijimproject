#ifndef _WOWFILES_CATACLYSM_MCNKCATA_H_
#define _WOWFILES_CATACLYSM_MCNKCATA_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include <wowfiles/Chunk.h>

class McnkCata : public Chunk
{
  public:

    McnkCata(std::ifstream & file, int offsetInFile);
    McnkCata(std::string letters, int givenSize, const std::vector<char> &data);

    friend std::ostream & operator<<(std::ostream & os, const McnkCata & mcnkCata);

  private:

    std::vector<char> mcnkHeader;
    Chunk mcvt;
    Chunk mccv;
    Chunk mclv;
    Chunk mcnr;
    Chunk mclq;
    Chunk mcse;
};

#endif