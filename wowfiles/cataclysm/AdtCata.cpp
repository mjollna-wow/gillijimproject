#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <wowfiles/cataclysm/AdtCata.h>
#include <wowfiles/Chunk.h>
#include <wowfiles/Mddf.h>
#include <wowfiles/Modf.h>
#include <wowfiles/Mhdr.h>
#include <wowfiles/Mh2o.h>
#include <wowfiles/Mcnk.h>
#include <wowfiles/cataclysm/McnkCataTerrain.h>
#include <wowfiles/cataclysm/McnrCata.h>
#include <utilities/Utilities.h>
#include <wowfiles/lichking/AdtLk.h>

AdtCata::AdtCata(const std::string & adtFileName, const std::vector<char> & adtFile) : adtName(adtFileName)
{
  terrain = AdtCataTerrain(adtName, adtFile);
  
  texName = adtFileName;
  texName = texName.substr(0, texName.size() - 4);
  texName.append("_tex0.adt");

  std::vector<char> texFile(0);
  Utilities::getWholeFile(texName, texFile);

  textures = AdtCataTextures(texName, texFile);

  objName = adtFileName;
  objName = objName.substr(0, objName.size() - 4);
  objName.append("_obj0.adt");
  
  std::vector<char> objFile(0);
  Utilities::getWholeFile(objName, objFile);

  objects = AdtCataObjects(objName, objFile);
}

void AdtCata::changeHeight(const int & heightToAdd)
{
  objects.addToObjectsHeight(heightToAdd);
  terrain.addToTerrainHeight(heightToAdd);
}

void AdtCata::toFile()
{
  terrain.toFile();
  textures.toFile();
  objects.toFile();
}

void AdtCata::toFile(const std::string & fileName)
{
  terrain.toFile(fileName);
  
  std::string texturesName = fileName;
  texturesName = texturesName.substr(0, texturesName.size() - 4);
  texturesName.append("_tex0.adt");  
  textures.toFile(texturesName);
  
  std::string objectsName = fileName;
  objectsName = objectsName.substr(0, objectsName.size() - 4);
  objectsName.append("_obj0.adt");  
  objects.toFile(objectsName);
}

/*AdtLk AdtCata::toAdtLk() // TODO : conversion is only partial, only terrain (other chunks are empty), and it's weird to have method in Cata terrain.
{
  std::string cName (adtName);

  std::vector<char> mverData;
  mverData.push_back(0x12);
  mverData.push_back(0x0);
  mverData.push_back(0x0);
  mverData.push_back(0x0);
  Chunk cMver ("REVM", 4, mverData);

  Mh2o (cMh2o);
  if (!mh2o.isEmpty())
    cMh2o = mh2o;
  
  std::vector<char> emptyData(0);

  Chunk cMtex ("XETM", 0, emptyData); // TODO : fill emptiness for objects
  Mmdx cMmdx ("XDMM", 0, emptyData); 
  Mmid cMmid ("DIMM", 0, emptyData);
  Mwmo cMwmo ("OMWM", 0, emptyData);
  Mwid cMwid ("DIWM", 0, emptyData);
  Mddf cMddf ("FDDM", 0, emptyData);
  Modf cModf ("FDOM", 0, emptyData);
  
  std::vector<McnkLk> cMcnks;
  int currentMcnk;

  for (currentMcnk = 0 ; currentMcnk < 256 ; ++currentMcnk)
  {
    cMcnks.push_back(terrainMcnks[currentMcnk].toMcnkLk());
  }

  Chunk (cMfbo);
  Chunk (cMtxf);

  const int mhdrFlags = 0;

  AdtLk adtLk(cName, cMver, mhdrFlags, cMh2o, cMtex, cMmdx, cMmid, cMwmo, cMwid, cMddf, cModf, cMcnks, cMfbo, cMtxf);
  return adtLk;  
}*/

std::ostream & operator<<(std::ostream & os, const AdtCata & adtCata)
{
  os << adtCata.terrain << std::endl;
  os << "------------------------------" << std::endl;
  os << adtCata.textures << std::endl;
  os << "------------------------------" << std::endl;
  os << adtCata.objects << std::endl;

  return os;
}