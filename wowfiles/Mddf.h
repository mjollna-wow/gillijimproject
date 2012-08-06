#ifndef _WOWFILES_MDDF_H_
#define _WOWFILES_MDDF_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <wowfiles/Chunk.h>

class Mddf : public Chunk
{
  public:

    Mddf();
    Mddf(std::ifstream & adtFile, int offsetInFile);
	  Mddf(const std::vector<char> & wholeFile, int offsetInFile);
    Mddf(std::string letters, int givenSize, const std::vector<char> & chunkData);
	
    void addToObjectsHeight(const int & heightToAdd);

    std::vector<int> getM2IndicesForMmdx() const;
    void updateIndicesForLk(std::vector<int> & alphaIndices);

    friend std::ostream & operator<<(std::ostream & os, const Mddf & mddf);	

  private: 

    std::vector<int> getEntriesIndices() const;
    std::vector<float> getObjectsHeights() const;

};

#endif