#ifndef ADTLK_H_
#define ADTLK_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../WowChunkedFormat.h"
#include "../Chunk.h"
#include "../Mh2o.h"
#include "../Mcin.h"
#include "../Mhdr.h"
#include "McnkLk.h"

class AdtLk : public WowChunkedFormat
{
  public:

    AdtLk(const std::string & adtFile);
    AdtLk(const std::string & name // <-- TODO : that constructor has a problem.
      , const Chunk & cMver
      , const int & mhdrFlags
      , const Mh2o & cMh2o
      , const Chunk & cMtex
      , const Chunk & cMmdx
      , const Chunk & cMmid
      , const Chunk & cMwmo
      , const Chunk & cMwid
      , const Chunk & cMddf
      , const Chunk & cModf
      , const std::vector<McnkLk> & cMcnks
      , const Chunk & cMfbo
      , const Chunk & cMtxf
      );

    void toFile();
    int getMcnksWholeSize();
    bool checkIntegrity();

    void mh2oToFile();
    void importMh2o(std::string mh2oName);

    friend std::ostream & operator<<(std::ostream & os, const AdtLk & adtLk);

  private:

    int getMhdrFlags();
    bool checkMcinOffsets();
    bool checkMhdrOffsets();
    void updateMhdrAndMcin();

    std::string adtName;
    Chunk mver;
    Mhdr mhdr;
    Mcin mcin;
    Mh2o mh2o;
    Chunk mtex;
    Chunk mmdx;
    Chunk mmid;
    Chunk mwmo;
    Chunk mwid;
    Chunk mddf;
    Chunk modf;
    std::vector<McnkLk> mcnks;
    Chunk mfbo;
    Chunk mtxf;
};

#endif