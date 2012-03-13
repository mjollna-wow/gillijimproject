#ifndef WDT_ALPHA_H_
#define WDT_ALPHA_H_

#include <vector>
#include <string>
#include "../Wdt.h"
#include "../WowChunkedFormat.h"
#include "../Chunk.h"
#include "MphdAlpha.h"
#include "MainAlpha.h"
#include "Monm.h"
#include "AdtAlpha.h"

class WdtAlpha : public WowChunkedFormat
{
  public:

    WdtAlpha(const std::string & wdtAlphaName);
    Wdt toWdt() const;
    std::vector<int> getExistingAdtsNumbers() const;
    std::vector<int> getAdtOffsetsInMain() const; // TODO : change this

    void toFile();

    friend std::ostream & operator<<(std::ostream & os, const WdtAlpha & wdtAlpha);

  private:

    std::string wdtName;
    Chunk mver;
    MphdAlpha mphd;
    MainAlpha main;
    Chunk mdnm;
    Monm monm;
    Chunk modf;
};

#endif