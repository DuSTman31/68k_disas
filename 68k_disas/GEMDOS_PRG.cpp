#include "StdAfx.h"
#include "GEMDOS_PRG.h"

#include <cstdio>
#include <cstdint>

#include "endian_conversion.h"


GEMDOS_PRG::GEMDOS_PRG(void)
{
	fName = NULL;
}

GEMDOS_PRG::GEMDOS_PRG(const char *fileName)
{
	unsigned int namesize = 0;
	namesize = strlen(fileName);
	fName = new char[namesize+1];
	fName[namesize] = '\0';
	strcpy(fName, fileName);
}

GEMDOS_PRG::~GEMDOS_PRG(void)
{
	if(fName)
		delete[] fName;
}

void 
GEMDOS_PRG::getTextSection(char **start, unsigned int &sectSize)
{
	FILE *fHand = fopen(fName, "rb");
	fseek(fHand, 0, SEEK_END);
	unsigned int fSize = ftell(fHand);
	fseek(fHand, 0, SEEK_SET);

	char *buffer = new char[fSize];
	fread(buffer, 1, fSize, fHand);
	fclose(fHand);

	uint32_t tlen = *(uint32_t*)&(buffer[2]);
	
	tlen = bigToNative(tlen);

	char *textBuf = &buffer[0x1C];


	*start = new char[tlen];

	memcpy(*start, textBuf, tlen);
	sectSize = tlen;

}