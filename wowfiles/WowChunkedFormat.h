#ifndef WOWCHUNKEDFORMAT_H_
#define WOWCHUNKEDFORMAT_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Chunk.h"

class WowChunkedFormat
{
  public:

    virtual void toFile() = 0;
		
    static const int chunkLettersAndSize = 8;
};

#endif