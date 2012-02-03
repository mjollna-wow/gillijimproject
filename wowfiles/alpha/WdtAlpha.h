#ifndef WDT_ALPHA_H_
#define WDT_ALPHA_H_

#include <vector>
#include <string>
#include "../Wdt.h"
#include "../Chunk.h"
#include "MphdAlpha.h"
#include "MainAlpha.h"
#include "Monm.h"
#include "AdtAlpha.h"

class WdtAlpha
{
	public:

		WdtAlpha(const std::string & wdtFile);
		Wdt toWdt();
		friend std::ostream & operator<<(std::ostream & os, const WdtAlpha & wdtAlpha);

	private:

		std::string wdtName;
		Chunk mver;
		MphdAlpha mphd;
		MainAlpha main;
		Chunk mdnm;
		Monm monm;
		Chunk modf;
		std::vector<AdtAlpha> adts;
};

#endif