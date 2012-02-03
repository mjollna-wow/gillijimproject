#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include "AdtCata.h"
#include "../Chunk.h"
#include "../Mhdr.h"
#include "../Mh2o.h"
#include "McnkCata.h"
#include "McnkCataTex0.h"
#include "McnkCataObj0.h"
#include "../../utilities/FileHandling.h"

AdtCata::AdtCata(const std::string & adtFile) : adtName(adtFile)
{
	const int chunkLettersAndSize = 8;
	int fullDataOffset = 0;
	int sizeAdjustments = 0;
	int currentMcnk;

	const int mh2oOffset = 40;
	const int mfboOffset = 36;

	FileHandling file(adtFile);
	std::vector<char> terrainFullData = file.getFullFile();

	terrainMver = Chunk(terrainFullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = chunkLettersAndSize + fullDataOffset + terrainMver.getGivenSize();

	mhdr = Mhdr(terrainFullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = chunkLettersAndSize + fullDataOffset + mhdr.getGivenSize();

	if (mhdr.getOffset(mh2oOffset) != 0)
	{
		mh2o = Chunk(terrainFullData, fullDataOffset, sizeAdjustments);
		fullDataOffset = chunkLettersAndSize + fullDataOffset + mh2o.getRealSize();
	}

	for (currentMcnk = 0 ; currentMcnk < 256 ; currentMcnk++)
	{
		terrainMcnks.push_back(McnkCata(terrainFullData, fullDataOffset, sizeAdjustments));
		fullDataOffset = chunkLettersAndSize + fullDataOffset + terrainMcnks[currentMcnk].getGivenSize();
	}

	if (mhdr.getOffset(mfboOffset) != 0)
	{
		mfbo = Chunk(terrainFullData, fullDataOffset, sizeAdjustments);
		fullDataOffset = fullDataOffset + mfbo.getGivenSize(); 
	}



	fullDataOffset = 0;
	std::string tex0FileName = getTex0FileName();

	FileHandling tex0File(tex0FileName);
	std::vector<char> tex0FullData = tex0File.getFullFile();

	tex0Mver = Chunk(tex0FullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = chunkLettersAndSize + fullDataOffset + tex0Mver.getGivenSize();

	mamp = Chunk(tex0FullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = chunkLettersAndSize + fullDataOffset + mamp.getGivenSize();

	mtex = Chunk(tex0FullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = chunkLettersAndSize + fullDataOffset + mtex.getGivenSize();

	for (currentMcnk = 0 ; currentMcnk < 256 ; currentMcnk++)
	{
		tex0Mcnks.push_back(McnkCataTex0(tex0FullData, fullDataOffset, sizeAdjustments));
		fullDataOffset = chunkLettersAndSize + fullDataOffset + tex0Mcnks[currentMcnk].getGivenSize();
	}

	/*if (fullDataOffset != tex0FullData.size())
	{
		mtxf = Chunk(terrainFullData, fullDataOffset, sizeAdjustments);
		fullDataOffset = chunkLettersAndSize + fullDataOffset + mtxf.getGivenSize();
	}*/



	/*fullDataOffset = 0;
	std::string obj0FileName =  getObj0FileName();

	FileHandling obj0File(obj0FileName);
	std::vector<char> obj0FullData = obj0File.getFullFile();

	obj0Mver = Chunk(obj0FullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = fullDataOffset + obj0Mver.getGivenSize();

	mmdx = Chunk(obj0FullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = fullDataOffset + mmdx.getGivenSize();

	mmid = Chunk(obj0FullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = fullDataOffset + mmid.getGivenSize();

	mwmo = Chunk(obj0FullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = fullDataOffset + mwmo.getGivenSize();

	mwid = Chunk(obj0FullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = fullDataOffset + mwid.getGivenSize();

	mmdf = Chunk(obj0FullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = fullDataOffset + mmdf.getGivenSize();

	modf = Chunk(obj0FullData, fullDataOffset, sizeAdjustments);
	fullDataOffset = fullDataOffset + modf.getGivenSize();

	for (currentMcnk = 0 ; currentMcnk < 256 ; currentMcnk++)
	{
		obj0Mcnks[currentMcnk] = McnkCataObj0(obj0FullData, fullDataOffset, sizeAdjustments);
		fullDataOffset = fullDataOffset + obj0Mcnks[currentMcnk].getGivenSize();
	}*/
}

std::string AdtCata::getTex0FileName() const
{
	std::string extensionReplacement = "_tex0.adt";
	std::string tex0Name = adtName;
	return tex0Name.replace(tex0Name.size() - 4, tex0Name.size(), extensionReplacement);
}

std::string AdtCata::getObj0FileName() const
{
	std::string extensionReplacement = "_obj0.adt";
	std::string obj0Name = adtName;
	return obj0Name.replace(obj0Name.size() - 4, obj0Name.size(), extensionReplacement);
}

std::ostream & operator<<(std::ostream & os, const AdtCata & adtCata)
{
	os << adtCata.adtName << std::endl;
	os << "------------------------------" << std::endl;
	os << adtCata.terrainMver;
	os << adtCata.mhdr;
	os << adtCata.mh2o;

	std::vector<McnkCata>::const_iterator mcnksIter;
	int i = 0;

	for (mcnksIter = adtCata.terrainMcnks.begin() ; mcnksIter != adtCata.terrainMcnks.end() ; ++mcnksIter)
	{
		os << "MCNK #" << i << " : " << std::endl;
		os << *mcnksIter;
		i++;
	}

	os << adtCata.mfbo;

	os << "------------------------------" << std::endl;
	os << adtCata.getTex0FileName() << std::endl;
	os << "------------------------------" << std::endl;
	os << adtCata.tex0Mver;
	os << adtCata.mamp;
	os << adtCata.mtex;

	std::vector<McnkCataTex0>::const_iterator mcnkstex0Iter;
	i = 0;

	for (mcnkstex0Iter = adtCata.tex0Mcnks.begin() ; mcnkstex0Iter != adtCata.tex0Mcnks.end() ; ++mcnkstex0Iter)
	{
		os << "MCNK (tex0) #" << i << " : " << std::endl;
		os << *mcnkstex0Iter;
		i++;
	}

	/*os << adtCata.mtxf;*/

	os << "------------------------------" << std::endl;
	os << adtCata.getObj0FileName() << std::endl;
	os << "------------------------------" << std::endl;
	/*os << adtCata.obj0Mver;
	os << adtCata.mmdx;
	os << adtCata.mmid;
	os << adtCata.mwmo;
	os << adtCata.mwid;
	os << adtCata.mddf;
	os << adtCata.modf;

	i = 0;

	for (mcnksIter = adtCata.obj0Mcnks.begin() ; mcnksIter != adtCata.obj0Mcnks.end() ; ++mcnksIter)
	{
		os << "MCNK (obj0) #" << i << " : " << std::endl;
		os << *mcnksIter;
		i++;
	}*/

	return os;
}