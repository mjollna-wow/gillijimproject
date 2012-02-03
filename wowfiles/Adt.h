#ifndef ADT_H_
#define ADT_H_

#include <vector>
#include <string>
#include "Chunk.h"
#include "Mhdr.h"

class Adt
{
	public:

	// TODO : See if need some virtual functions or not. If not, delete.

	Adt(const std::string & adtFile);

	protected:

	Chunk mver;
	Mhdr mhdr;
	Chunk mh2o;
	Chunk mtex;
	Chunk mmdx;
	Chunk mmid;
	Chunk mwmo;
	Chunk mwid;
	Chunk mmdf;
	Chunk modf;
	Chunk mtxf;
	Chunk mfbo;
};

#endif