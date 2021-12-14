#ifndef _MAPLOADER_H
#define _MAPLOADER_H

// typedef struct
// {
// 	short 	width;
// 	short 	height;
// 	char	***data;
// } TableData;

char ***LoadTableToMem(const char *fileName);
void ClearTableFromMem();
#endif
