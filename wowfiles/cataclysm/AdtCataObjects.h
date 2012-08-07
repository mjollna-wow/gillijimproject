#ifndef _WOWFILES_CATACLYSM_ADTCATAOBJECTS_H_
#define _WOWFILES_CATACLYSM_ADTCATAOBJECTS_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <wowfiles/WowChunkedFormat.h>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mcnk.h>
#include <wowfiles/Mddf.h>
#include <wowfiles/Modf.h>
#include <wowfiles/cataclysm/McnkCataObjects.h>
#include <utilities/Utilities.h>

class AdtCataObjects : public WowChunkedFormat
{
  public:

    AdtCataObjects(const std::string & adtName, const std::vector<char> & adtFile);

    void addToObjectsHeight(const int & heightToAdd);

    std::vector<Utilities::Point> getAllObjectsCoords() const;

    void toFile();
    void toFile(const std::string & fileName);

    friend std::ostream & operator<<(std::ostream & os, const AdtCataObjects & adtCataObjects);

  private:

    std::string adtName;
    Chunk objectsMver;
    Chunk mmdx;
    Chunk mmid;
    Chunk mwmo;
    Chunk mwid;
    Mddf mddf;
    Modf modf;
    std::vector<McnkCataObjects> objectsMcnks;
	  std::vector<Chunk> objectsUnknown;
};

#endif