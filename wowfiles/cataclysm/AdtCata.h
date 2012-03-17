#ifndef _WOWFILES_CATACLYSM_ADTCATA_H_
#define _WOWFILES_CATACLYSM_ADTCATA_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/WowChunkedFormat.h>
#include <wowfiles/Chunk.h>
#include <wowfiles/cataclysm/McnkCata.h>
#include <wowfiles/cataclysm/McnkCataTex0.h>
#include <wowfiles/cataclysm/McnkCataObj0.h>

class AdtCata : public WowChunkedFormat
{
  public:

    AdtCata(const std::string & adtFile);
    std::string getTex0FileName() const;
    std::string getObj0FileName() const;

    void toFile();

    friend std::ostream & operator<<(std::ostream & os, const AdtCata & adtCata);

  private:

    std::string adtName;

    Chunk terrainMver;
    Chunk mhdr;
    Chunk mh2o;
    std::vector<McnkCata> terrainMcnks;
    Chunk mfbo;

    Chunk tex0Mver;
    Chunk mamp;
    Chunk mtex;
    std::vector<McnkCataTex0> tex0Mcnks;
    /*Chunk mtxf;

    Chunk obj0Mver;
    Chunk mmdx;
    Chunk mmid;
    Chunk mwmo;
    Chunk mwid;
    Chunk mmdf;
    Chunk modf;
    std::vector<McnkCataObj0> obj0Mcnks;*/
};

#endif