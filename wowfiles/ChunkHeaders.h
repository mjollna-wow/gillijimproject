#ifndef _WOWFILES_CHUNKHEADERS_H_
#define _WOWFILES_CHUNKHEADERS_H_

struct McnkHeader
{
  int flags;
  int indexX;
  int indexY;
  int nLayers;
  int m2Number;
  int mcvtOffset;
  int mcnrOffset;
  int mclyOffset;
  int mcrfOffset;
  int mcalOffset;
  int mcalSize;
  int mcshOffset;
  int mcshSize;
  int areaId;
  int wmoNumber;
  int holes;
  int groundEffectsMap1;
  int groundEffectsMap2;
  int groundEffectsMap3;
  int groundEffectsMap4;
  int predTex;
  int nEffectDoodad;
  int mcseOffset;
  int nSndEmitters;
  int mclqOffset;
  int mclqSize;
  float posX;
  float posY;
  float posZ;
  int mccvOffset;
  int mclvOffset;
  int unused;
};

struct McnkAlphaHeader
{
  int flags;
  int indexX;
  int indexY;
  float unknown1;
  int nLayers;
  int unknown2;
  int mcvtOffset; 
  int mcnrOffset;
  int mclyOffset;
  int mcrfOffset;
  int mcalOffset;
  int mcalSize;
  int mcshOffset;
  int mcshSize;
  int unknown3;
  int unknown4;
  int unknown5;
  int groundEffectsMap1;
  int groundEffectsMap2;
  int groundEffectsMap3;
  int groundEffectsMap4;  
  int unknown6;
  int unknown7;
  int mcnkChunksSize;
  int unknown8;
  int mclqOffset;
  int unused1;
  int unused2;
  int unused3;
  int unused4;
  int unused5;
  int unused6;
};

#endif