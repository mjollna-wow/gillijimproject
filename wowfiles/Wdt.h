#ifndef WDT_H_
#define WDT_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "WowChunkedFormat.h"
#include "Chunk.h"
#include "Mphd.h"

class Wdt : public WowChunkedFormat
{
  public:

    Wdt(const std::string & wdtFileName);
    Wdt(const std::string & name
      , const Chunk & cMver
      , const Mphd & cMphd
      , const Chunk & cMain
      , const Chunk & cMwmo
      , const Chunk & cModf
    );
    void toFile();
    friend std::ostream & operator<<(std::ostream & os, const Wdt & wdt);

  private:

    std::string wdtName;
    Chunk mver;
    Mphd mphd;
    Chunk main;
    Chunk mwmo;
    Chunk modf;
};

#endif