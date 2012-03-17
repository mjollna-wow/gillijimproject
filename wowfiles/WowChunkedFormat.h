#ifndef _WOWFILES_WOWCHUNKEDFORMAT_H_
#define _WOWFILES_WOWCHUNKEDFORMAT_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <wowfiles/Chunk.h>

class WowChunkedFormat
{
  public:

    virtual void toFile() = 0;
    
    static const int chunkLettersAndSize = 8;
};

#endif