#include "stdafx.h"

#include "68k.h"

#include <cstdio>
#include "endian_conversion.h"

void decode(void *buf, unsigned int offset)
{
	uint8_t oo = 0;
	uint8_t ot = 0;
	uint16_t out = bigToNative(*(uint16_t*)((char*)buf+offset));
	oo = ((uint8_t*)&out)[0];
	ot = ((uint8_t*)&out)[1];
	printf("%x %x \n", oo, ot);
}


void scanInput(void *buf, unsigned int offset, opDetails &od)
{
	uint8_t opcodeShort = 0;
	uint16_t opcodeWord = 0;

	opcodeWord = *(uint16_t*)(((char*)buf)+offset);
	opcodeWord = bigToNative(opcodeWord);

	opcodeShort = ((opcodeWord & 0xF000) >> 12);

	decode(buf, offset);

	switch(opcodeShort)
	{
	case 0x00:
		if((opcodeWord & 0x0006))
		{
			SEOps::addi(opcodeWord, buf, offset, od);
		}
		else if(opcodeWord == 0)
		{
			SEOps::ori(opcodeWord, buf, offset, od);
		}
		break;
	case 0x01:
		SEOps::move_b(opcodeWord, buf, offset, od);
		break;
	case 0x02:
		if((opcodeWord & 0x01C0) == 0x0040)
		{
			SEOps::movea_l(opcodeWord, buf, offset, od);
		}
		else
		{
			SEOps::move_l(opcodeWord, buf, offset, od);
		}
		break;
	case 0x03:
		if((opcodeWord & 0x01C0) == 0x0040)
		{
			SEOps::movea_w(opcodeWord, buf, offset, od);
		}
		else
		{
			SEOps::move_w(opcodeWord, buf, offset, od);
		}
		break;
	case 0x04:
		if((opcodeWord & 0xF1C0) == 0x41C0)
		{
			SEOps::lea(opcodeWord, buf, offset, od);
		}
		else if(opcodeWord == 0x4E77)
		{
			SEOps::rtr(opcodeWord, buf, offset, od);
		}
		else if(opcodeWord == 0x4E71)
		{
			SEOps::nop(opcodeWord, buf, offset, od);
		}
		else if(opcodeWord == 0x4E75)
		{
			SEOps::rts(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFFC0) == 0x4E00)
		{
			//jmp
			SEOps::jmp(opcodeWord, buf, offset, od);
		}
		else if(opcodeWord == 0x4600)
		{
			SEOps::not(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x4E00)
		{
			if((opcodeWord & 0xFFF0) == 0x4E40)
				SEOps::trap(opcodeWord, buf, offset, od);
		}
		break;
	case 0x05:
		if((opcodeWord & 0xF0F8) == 0x50C8)
		{
			if((opcodeWord & 0xFF00) == 0x5200)
			{
				// DBHI
				SEOps::dbhi(opcodeWord, buf, offset, od);
			}
			else if((opcodeWord & 0xFF00) == 0x5300)
			{
				// DBLS
				SEOps::dbls(opcodeWord, buf, offset, od);
			}
			else if((opcodeWord & 0xFF00) == 0x5400)
			{
				// DBCC
				SEOps::dbcc(opcodeWord, buf, offset, od);
			}
			else if((opcodeWord & 0xFF00) == 0x5500)
			{
				// DBCS
				SEOps::dbcs(opcodeWord, buf, offset, od);
			}
			else if((opcodeWord & 0xFF00) == 0x5600)
			{
				// DBNE
				SEOps::dbne(opcodeWord, buf, offset, od);
			}
			else if((opcodeWord & 0xFF00) == 0x5700)
			{
				// DBEQ
				SEOps::dbeq(opcodeWord, buf, offset, od);
			}
			else if((opcodeWord & 0xFF00) == 0x5800)
			{
				// DBVC
				SEOps::dbvc(opcodeWord, buf, offset, od);
			}
			else if((opcodeWord & 0xFF00) == 0x5900)
			{
				// DBVS
				SEOps::dbvs(opcodeWord, buf, offset, od);
			}
			else if((opcodeWord & 0xFF00) == 0x5A00)
			{
				// DBPL
				SEOps::dbpl(opcodeWord, buf, offset, od);
			}
			else if((opcodeWord & 0xFF00) == 0x5B00)
			{
				// DBMI
				SEOps::dbmi(opcodeWord, buf, offset, od);
			}
			else if((opcodeWord & 0xFF00) == 0x5C00)
			{
				// DBGE
				SEOps::dbge(opcodeWord, buf, offset, od);
			}
			else if((opcodeWord & 0xFF00) == 0x5D00)
			{
				// DBLT
				SEOps::dblt(opcodeWord, buf, offset, od);
			}
			else if((opcodeWord & 0xFF00) == 0x5E00)
			{
				// DBGT
				SEOps::dbgt(opcodeWord, buf, offset, od);
			}
			else if((opcodeWord & 0xFF00) == 0x5F00)
			{
				// DBLE
				SEOps::dble(opcodeWord, buf, offset, od);
			}
		}
		else if((opcodeWord & 0xF100) == 0x5100)
		{
			SEOps::subq(opcodeWord, buf, offset, od);
		}
		else
		{
			SEOps::addq(opcodeWord, buf, offset, od);
		}
		break;
	case 0x06:
		if((opcodeWord & 0xFF00) == 0x6000)
		{
			// BRA
			SEOps::bra(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x6200)
		{
			// BHI
			SEOps::bhi(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x6300)
		{
			// BLS
			SEOps::bls(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x6400)
		{
			// BCC
			SEOps::bcc(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x6500)
		{
			// BCS
			SEOps::bcs(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x6600)
		{
			// BNE
			SEOps::bne(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x6700)
		{
			// BEQ
			SEOps::beq(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x6800)
		{
			// BVC
			SEOps::bvc(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x6900)
		{
			// BVS
			SEOps::bvs(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x6A00)
		{
			// BPL
			SEOps::bpl(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x6B00)
		{
			// BMI
			SEOps::bmi(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x6C00)
		{
			// BGE
			SEOps::bge(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x6D00)
		{
			// BLT
			SEOps::blt(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x6E00)
		{
			// BGT
			SEOps::bgt(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x6F00)
		{
			// BLE
			SEOps::ble(opcodeWord, buf, offset, od);
		}
		break;
	case 0x08:
		SEOps::or(opcodeWord, buf, offset, od);
		break;
	case 0x0C:
		SEOps::add(opcodeWord, buf, offset, od);
		break;
	case 0x0D:
		if((opcodeWord & 0xD100) == 0xD100)
		{
			SEOps::addx(opcodeWord, buf, offset, od);
		}
		else
		{
			SEOps::adda(opcodeWord, buf, offset, od);
		}
		break;
	}
}


unsigned char addonWords(uint8_t mode, uint8_t reg, uint8_t size)
{
	switch(mode)
	{
	case 0x00:
		break;
	case 0x01:
		break;
	case 0x02:
		break;
	case 0x03:
		break;
	case 0x04:
		break;
	case 0x05:
		return 1;
		break;
	case 0x06:
		return 1;
		break;
	case 0x07:
		if(reg == 0)
			return 1;
		else if(reg == 4)
		{
			if(size == 1)
				return 1;
			else if(size == 2)
				return 1;
			else if(size == 4)
				return 2;
		}
		else
			return 2;
		break;
	}
	return 0;
}

namespace SEOps
{
	void addq(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;

		unsigned char dataSize = (opcodeWord & 0x00C0) >>6;
		if(dataSize == 0)
		{
			od.operandSize = "B";
			size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 1);
		}
		if(dataSize == 1)
		{
			od.operandSize = "W";
			size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 2);
		}
		if(dataSize == 2)
		{
			od.operandSize = "L";
			size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 4);
		}
		od.mnemonic = "ADDQ";

		od.size = size;
	}

	void subq(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 1);
		od.size = size;
		od.mnemonic = "SUBQ";
	}

	void add(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "ADD";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;
	}

	void addx(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "ADDX";
		od.size = size;
	}

	void addi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "ADDI";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;
	}

	void adda(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "ADDA";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;
	}


	void move_b(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "MOVE";
		od.operandSize = "B";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		size += addonWords(((opcodeWord & 0x01C0) >> 6), ((opcodeWord & 0x0E00) >> 9), 1);
		od.size = size;
	}

	void move_w(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "MOVE";
		od.operandSize = "W";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 2);
		size += addonWords(((opcodeWord & 0x01C0) >> 6), ((opcodeWord & 0x0E00) >> 9), 2);
		od.size = size;
	}

	void move_l(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "MOVE";
		od.operandSize = "L";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4);
		size += addonWords(((opcodeWord & 0x01C0) >> 6), ((opcodeWord & 0x0E00) >> 9), 4);
		od.size = size;
	}

	void movea_w(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "MOVEA";
		od.operandSize = "W";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;		
	}

	void movea_l(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "MOVEA";
		od.operandSize = "L";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4);
		od.size = size;		
	}

	void not(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "NOT";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;		
	}

	void ori(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "ORI";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;		
	}


	void or(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "OR";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;		
	}

	void trap(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "TRAP";
		od.size = size;		
	}

	void bra(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			od.operandSize = "w";
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			od.operandSize = "l";
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "bra";
	}

	void jmp(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;
		od.mnemonic = "jmp";
	}

	void bsr(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			od.operandSize = "w";
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			od.operandSize = "l";
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "bsr";
	}

	void jsr(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;
		od.mnemonic = "jsr";
	}


	void rtr(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "rtr";
		od.size = size;
	}
	
	void rts(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "rts";
		od.size = size;
	}

	void nop(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "nop";
		od.size = size;
	}

	void bhi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "bhi";
	}

	void bls(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "bls";
	}

	void bcc(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "bcc";
	}

	void bcs(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "bcs";
	}

	void bne(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "bne";
	}

	void beq(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "beq";
	}

	void bvc(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "bvc";
	}

	void bvs(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "bvs";
	}

	void bpl(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "bpl";
	}

	void bmi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "bmi";
	}

	void bge(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "bge";
	}

	void blt(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "blt";
	}

	void bgt(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "bgt";
	}

	void ble(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00FF) == 0x00)
		{
			size += 1;
			//.w - 16 bit displacement
		}
		else if((opcodeWord & 0x00FF) == 0xFF)
		{
			size += 2;
			// .l - 32 bit displacement
		}
		od.size = size;
		od.mnemonic = "ble";
	}



	void dbhi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 2;
		od.size = size;
		od.mnemonic = "dbhi";
	}

	void dbls(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 2;

		od.size = size;
		od.mnemonic = "dbls";
	}

	void dbcc(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 2;

		od.size = size;
		od.mnemonic = "dbcc";
	}

	void dbcs(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 2;
		od.size = size;
		od.mnemonic = "dbcs";
	}

	void dbne(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 2;
		od.size = size;
		od.mnemonic = "dbne";
	}

	void dbeq(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 2;
		od.size = size;
		od.mnemonic = "dbeq";
	}

	void dbvc(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 2;
		od.size = size;
		od.mnemonic = "dbvc";
	}

	void dbvs(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 2;
		od.size = size;
		od.mnemonic = "dbvs";
	}

	void dbpl(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 2;
		od.size = size;
		od.mnemonic = "dbpl";
	}

	void dbmi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 2;
		od.size = size;
		od.mnemonic = "dbmi";
	}

	void dbge(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 2;
		od.size = size;
		od.mnemonic = "dbge";
	}

	void dblt(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 2;
		od.size = size;
		od.mnemonic = "dblt";
	}

	void dbgt(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 2;
		od.size = size;
		od.mnemonic = "dbgt";
	}

	void dble(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 2;
		od.size = size;
		od.mnemonic = "dble";
	}

	void lea(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;
		od.mnemonic = "lea";
	}

}