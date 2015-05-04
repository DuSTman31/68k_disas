// 68k_disas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "68k.h"

#include "GEMDOS_PRG.h"

int _tmain(int argc, _TCHAR* argv[])
{
	GEMDOS_PRG *np = new GEMDOS_PRG("TEST3.PRG");
	char *tSect = NULL;
	unsigned int tSectSize = 0;

	np->getTextSection(&tSect, tSectSize);

	//decode(tSect, 0);
	opDetails a;
	unsigned int index = 0;
	while(index < tSectSize)
	{
		memset(&a, 0, sizeof(opDetails));
		scanInput(tSect, index, a);
		if(a.operandSize)
			printf("Opcode:\t%s.%s\n", a.mnemonic, a.operandSize);
		else
			printf("Opcode:\t%s\n", a.mnemonic);

		printf("Size:\t%u\n", a.size);

		index += (a.size * 2);
		
	}
	return 0;
}

