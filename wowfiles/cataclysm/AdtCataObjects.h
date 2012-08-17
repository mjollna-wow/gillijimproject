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
#include <wowfiles/Mmdx.h>
#include <wowfiles/Modf.h>
#include <wowfiles/Mwmo.h>
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

    std::vector<std::string> getAllM2Names() const; // TODO : change all that.
    std::vector<std::string> getAllWmoNames() const;
    std::vector<Utilities::Point> getAllM2Coords() const; 
    std::vector<Utilities::Point> getAllWmoCoords() const;
    std::vector<int> getAllM2Indices() const;
    std::vector<int> getAllWmoIndices() const;

    friend std::ostream & operator<<(std::ostream & os, const AdtCataObjects & adtCataObjects);

  private:

    std::string adtName;
    Chunk objectsMver;
    Mmdx mmdx;
    Chunk mmid;
    Mwmo mwmo;
    Chunk mwid;
    Mddf mddf;
    Modf modf;
    std::vector<McnkCataObjects> objectsMcnks;
	  std::vector<Chunk> objectsUnknown;
};

#endif