#ifndef CHUNK_H_
#define CHUNK_H_

#include <vector>
#include <iostream>
#include <fstream>

// TODO : get rid of sizeAdjustments (?), and make specific chunk constructors for chunks that really need it (MCNR for LK and... ?)

class Chunk
{
	public:

		Chunk();
    Chunk(std::ifstream & fullAdtData, int position);
		Chunk(const std::vector<char> & fullAdtData, int position, int sizeAdjustments);
		Chunk(std::string letters, int givenSize, const std::vector<char> & chunkData);
		int getGivenSize();
		int getRealSize();
		bool isEmpty();
		std::vector<char> getWholeChunk() const;
		int getOffset(const int offsetInData);
		friend std::ostream & operator<<(std::ostream & os, const Chunk & chunk);

	protected:

		int getChunkSizeFromFullData(const std::vector<char> & fullData, int position);

		std::string letters;
		int givenSize;
		std::vector<char> data;
};

#endif