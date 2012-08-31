#ifndef _WOWFILES_CATACLYSM_ADTCATATERRAIN_H_
#define _WOWFILES_CATACLYSM_ADTCATATERRAIN_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/WowChunkedFormat.h>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mhdr.h>
#include <wowfiles/Mh2o.h>
#include <wowfiles/Mcnk.h>
#include <wowfiles/cataclysm/McnkCataTerrain.h>
#include <wowfiles/lichking/AdtLk.h>

class AdtCataTerrain : public WowChunkedFormat
{
  public:

    AdtCataTerrain();
    AdtCataTerrain(const std::string & adtName, const std::vector<char> & adtFile);

    void addToTerrainHeight(const int & heightToAdd);

    void toFile();
    void toFile(const std::string & fileName);
    AdtLk toAdtLk();

    friend std::ostream & operator<<(std::ostream & os, const AdtCataTerrain & adtCataTerrain);

  private:

    std::string adtName;

    Chunk terrainMver;
    Mhdr mhdr;
    Mh2o mh2o;
    std::vector<McnkCataTerrain> terrainMcnks;
    Chunk mbmh;
    Chunk mbmi;
    Chunk mbmv;
    Chunk mfbo;
	  std::vector<Chunk> terrainUnknown;
};

#endif