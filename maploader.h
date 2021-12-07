#ifndef _MAPLOADER_H
#define _MAPLOADER_H

typedef struct
{
	short 	width;
	short 	height;
} MapData;

BYTE *LoadFileToMem(const char *fileName);

#endif
