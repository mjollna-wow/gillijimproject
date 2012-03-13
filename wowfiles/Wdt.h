#ifndef WDT_H_
#define WDT_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "WowChunkedFormat.h"
#include "Chunk.h"

class Wdt : public WowChunkedFormat
{
  public:

    Wdt(const std::string & wdtFileName);
    Wdt(const std::string & name
      , const Chunk & cMver
      , const Chunk & cMphd
      , const Chunk & cMain
      , const Chunk & cMwmo
      , const Chunk & cModf
    );
    void toFile();
    friend std::ostream & operator<<(std::ostream & os, const Wdt & wdt);

  private:

    std::string wdtName;
    Chunk mver;
    Chunk mphd;
    Chunk main;
    Chunk mwmo;
    Chunk modf;
};

#endif