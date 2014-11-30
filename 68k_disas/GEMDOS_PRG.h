#pragma once


#include <string>
using std::string;

class GEMDOS_PRG
{
public:
	GEMDOS_PRG(void);
	GEMDOS_PRG(const char *fileName);
	virtual ~GEMDOS_PRG(void);

	void getTextSection(char **start, unsigned int &sectSize);
private:
	char *fName;
};

