cmake_minimum_required (VERSION 2.6)
project (gillijimproject)

set ( utilities
  utilities/Utilities.h
  utilities/Utilities.cpp
  )

set ( wowfiles
  wowfiles/alpha/AdtAlpha.h
  wowfiles/alpha/AdtAlpha.cpp
  wowfiles/alpha/WdtAlpha.h
  wowfiles/alpha/WdtAlpha.cpp	
  wowfiles/alpha/McnkAlpha.h
  wowfiles/alpha/McnkAlpha.cpp
  wowfiles/alpha/Monm.h
  wowfiles/alpha/Monm.cpp
  wowfiles/alpha/MphdAlpha.h
  wowfiles/alpha/MphdAlpha.cpp	
  wowfiles/alpha/MainAlpha.h
  wowfiles/alpha/MainAlpha.cpp	
	
  wowfiles/cataclysm/AdtCata.h
  wowfiles/cataclysm/AdtCata.cpp
  wowfiles/cataclysm/McnkCata.h
  wowfiles/cataclysm/McnkCata.cpp
  wowfiles/cataclysm/McnkCataObj0.h
  wowfiles/cataclysm/McnkCataObj0.cpp
  wowfiles/cataclysm/McnkCataTex0.h
  wowfiles/cataclysm/McnkCataTex0.cpp
	
  wowfiles/lichking/AdtLk.h
  wowfiles/lichking/AdtLk.cpp
  wowfiles/lichking/McnkLk.h
  wowfiles/lichking/McnkLk.cpp
  wowfiles/lichking/McnrLk.h
  wowfiles/lichking/McnrLk.cpp	

  wowfiles/Chunk.h
  wowfiles/Chunk.cpp
  wowfiles/Main.h
  wowfiles/Main.cpp
  wowfiles/Mcin.h
  wowfiles/Mcin.cpp
  wowfiles/Mhdr.h
  wowfiles/Mhdr.cpp
  wowfiles/Mh2o.h
  wowfiles/Mh2o.cpp
  wowfiles/Mphd.h
  wowfiles/Mphd.cpp
  wowfiles/Wdt.h	
  wowfiles/Wdt.cpp		
  )
	
set ( alpha_sources
  main.cpp
  )

add_executable( gillijimproject 
  ${utilities}
  ${wowfiles}
  ${alpha_sources}
  )