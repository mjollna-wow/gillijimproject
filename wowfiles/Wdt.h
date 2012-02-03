#ifndef WDT_H_
#define WDT_H_

#include <vector>
#include <string>
#include "Chunk.h"

class Wdt
{
	public:

		Wdt(const std::string & wdtFile);
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