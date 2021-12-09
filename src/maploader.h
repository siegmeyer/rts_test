#ifndef _MAPLOADER_H
#define _MAPLOADER_H

typedef struct
{
	short 	width;
	short 	height;
	BYTE	***data;
} MapData;

BYTE ***LoadFileToMem(const char *fileName);
void ClearTableFromMem();
#endif
