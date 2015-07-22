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
		if((opcodeWord & 0xFF00) == 0x0000)
		{
			SEOps::ori(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x0200)
		{
			SEOps::addi(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x0400)
		{
			SEOps::subi(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFF00) == 0x0600)
		{
			SEOps::addi(opcodeWord, buf, offset, od);
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
		if((opcodeWord & 0xFF00) == 0x4200)
		{
			if ((opcodeWord & 0xFFC0) == 0x42C0)
			{
				SEOps::move_ccr(opcodeWord, buf, offset, od);
			}
			else
			{
				SEOps::clr(opcodeWord, buf, offset, od);
			}
		}
		else if((opcodeWord & 0xF1C0) == 0x41C0)
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
	case 0x07:
		if((opcodeWord & 0xF100) == 0x7000)
		{
			SEOps::moveq(opcodeWord, buf, offset, od);
		}
		break;
	case 0x08:
		SEOps::or(opcodeWord, buf, offset, od);
		break;
	case 0x09:
		if((opcodeWord & 0xF000) == 0x9000)
		{
			if((opcodeWord & 0xF130) == 0x9100)
			{
				SEOps::subx(opcodeWord, buf, offset, od);
			}
			else if(((opcodeWord & 0x01C0) == 0x00C0) || ((opcodeWord & 0x01C0) == 0x01C0))
			{
				SEOps::suba(opcodeWord, buf, offset, od);
			}
			else
			{
				SEOps::sub(opcodeWord, buf, offset, od);
			}
		}
		break;
	case 0x0B:
		if((opcodeWord & 0xF100) == 0xB000)
		{
			SEOps::cmp(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xF100) == 0xB100)
		{
			SEOps::eor(opcodeWord, buf, offset, od);
		}
		break;
	case 0x0C:
		
		if((opcodeWord & 0xF1C0) == 0xC0C0)
		{
			SEOps::mulu(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xF1C0) == 0xC1C0)
		{
			SEOps::muls(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xF000) == 0xC000)
		{
			SEOps::and(opcodeWord, buf, offset, od);
		}
		else
		{
			SEOps::add(opcodeWord, buf, offset, od);
		}
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
	case 0x0E:
		if((opcodeWord & 0xFEC0) == 0xE0C0)
		{
			SEOps::asl(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFEC0) == 0xE2C0)
		{
			SEOps::lsl(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFEC0) == 0xE4C0)
		{
			SEOps::roxl(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xFEC0) == 0xE6C0)
		{
			SEOps::rol(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xF018) == 0xE000)
		{
			SEOps::asl(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xF018) == 0xE008)
		{
			SEOps::lsl(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xF018) == 0xE010)
		{
			SEOps::roxl(opcodeWord, buf, offset, od);
		}
		else if((opcodeWord & 0xF018) == 0xE018)
		{
			SEOps::rol(opcodeWord, buf, offset, od);
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

void decodeModeReg(uint8_t mode, uint8_t reg, uint8_t size, struct operand &op)
{
	op.present = true;

	switch(mode)
	{
	case 0x00:
		op.addrMode = DATAREGDIRECT;
		op.opData.op = reg;
		break;
	case 0x01:
		op.addrMode = ADDRREGDIRECT;
		op.opData.op = reg;
		break;
	case 0x02:
		op.addrMode = ADDRINDIRECT;
		op.opData.op = reg;
		break;
	case 0x03:
		op.addrMode = ADDRINDIRECTPOSTINC;
		op.opData.op = reg;
		break;
	case 0x04:
		op.addrMode = ADDRINDIRECTPREDEC;
		op.opData.op = reg;
		break;

	default:

		break;
	}

}

void displacement(uint16_t opcodeWord, uint16_t *buf, opDetails &od)
{
	if((opcodeWord & 0x00FF) == 0x00)
	{
		od.operandSize = "w";
		//.w - 16 bit displacement
		int16_t dispDec = *((buf)+1);
		dispDec = bigToNative(dispDec);
		od.op1.opData.op = dispDec;
		od.size += 1;
	}
	else if((opcodeWord & 0x00FF) == 0xFF)
	{
		od.operandSize = "l";
		// .l - 32 bit displacement
		int16_t dispDec = *((buf)+1);
		int32_t dispDec2 = dispDec;
		dispDec2 <<= 16;
		dispDec = *((buf)+2);
		dispDec2 |= dispDec;
		dispDec2 = bigToNative(dispDec2);
		od.op1.opData.op = dispDec;
		od.size += 2;
	}
	else
	{
		int16_t dispDec = *((int16_t*)buf);
		dispDec = bigToNative(dispDec);
		dispDec ^= 0x0F;
		int8_t dispDec2 = dispDec;
		od.op1.opData.op = dispDec;
	}
	od.op1.present = true;
	od.op1.addrMode = PCRELOFF;
}

namespace SEOps
{
	void addq(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;

		unsigned char dataSize = (opcodeWord & 0x00C0) >>6;
		if(dataSize == 0)
		{
			od.operandSize = "b";
			size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 1);
		}
		if(dataSize == 1)
		{
			od.operandSize = "w";
			size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 2);
		}
		if(dataSize == 2)
		{
			od.operandSize = "l";
			size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 4);
		}
		od.mnemonic = "addq";

		od.size = size;
	}

	void add(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "add";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;
	}

	void addx(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "addx";
		od.size = size;
	}

	void addi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "addi";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;
	}

	void adda(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "adda";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;
	}

	void subq(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 1);
		od.size = size;
		od.mnemonic = "subq";
	}

	void sub(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		unsigned int opmode = ((opcodeWord & 0x91C0) >> 6);
		if((opmode == 0x00) || (opmode == 0x04))
		{
			od.operandSize = "b";
			size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 1);
		}
		else if((opmode == 0x01) || (opmode == 0x05))
		{
			od.operandSize = "w";
			size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 2);
		}
		else if((opmode == 0x02) || (opmode == 0x06))
		{
			od.operandSize = "l";
			size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 4);
		}
		od.size = size;
		od.mnemonic = "sub";
	}

	void suba(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 1);
		od.size = size;
		od.mnemonic = "suba";
	}

	void subi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		unsigned int opSizeField = 0;
		opSizeField = ((opcodeWord & 0x00C0) >> 6);
		if(opSizeField == 0x00)
		{
			od.operandSize = "b";
			size += 1;
			size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 1);
		}
		else if(opSizeField == 0x01)
		{
			od.operandSize = "w";
			size += 1;
			size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 2);
		}
		else if(opSizeField == 0x02)
		{
			od.operandSize = "l";
			size += 2;
			size += addonWords((opcodeWord & 0x0038) >>3, (opcodeWord & 0x0007), 4);
		}
		od.size = size;
		od.mnemonic = "subi";
	}

	void subx(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		od.mnemonic = "subx";
	}

	void move_b(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "move";
		od.operandSize = "b";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		size += addonWords(((opcodeWord & 0x01C0) >> 6), ((opcodeWord & 0x0E00) >> 9), 1);
		od.size = size;
	}

	void move_w(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "move";
		od.operandSize = "w";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 2);
		size += addonWords(((opcodeWord & 0x01C0) >> 6), ((opcodeWord & 0x0E00) >> 9), 2);
		od.size = size;
	}

	void move_l(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "move";
		od.operandSize = "l";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4);
		size += addonWords(((opcodeWord & 0x01C0) >> 6), ((opcodeWord & 0x0E00) >> 9), 4);
		od.size = size;
	}

	void movea_w(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "movea";
		od.operandSize = "w";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;		
	}

	void movea_l(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "movea";
		od.operandSize = "l";
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4);
		od.size = size;		
	}

	void not(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "not";
		if((opcodeWord & 0x00C0) == 0x0000)
		{
			od.operandSize = "b";
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
			od.size = size;		
			decodeModeReg(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1, od.op1);
		}
		else if((opcodeWord & 0x00C0) == 0x0040)
		{
			od.operandSize = "w";
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 2);
			od.size = size;		
			decodeModeReg(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 2, od.op1);
		}
		else if((opcodeWord & 0x00C0) == 0x0080)
		{
			od.operandSize = "l";
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4);
			od.size = size;		
			decodeModeReg(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4, od.op1);
		}
	}

	void or(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "or";
		uint8_t opSize = 0;

		if((opcodeWord & 0x00C0) == 0x0000)
		{
			od.operandSize = "b";
			opSize = 1;
		}
		else if((opcodeWord & 0x00C0) == 0x0040)
		{
			od.operandSize = "w";
			opSize = 2;
		}
		else if((opcodeWord & 0x00C0) == 0x0080)
		{
			od.operandSize = "l";
			opSize = 4;
		}


		if((opcodeWord & 0x0100) == 0x0100)
		{
			// Dn | <ea> -> <ea>

			od.op1.addrMode = DATAREGDIRECT;
			od.op1.present = true;
			od.op1.opData.reg = ((opcodeWord & 0x0E00) >> 9);

			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), opSize);
			od.size = size;		
			decodeModeReg(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), opSize, od.op2);
		}
		else
		{
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), opSize);
			od.size = size;		
			decodeModeReg(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), opSize, od.op1);
		
			od.op2.addrMode = DATAREGDIRECT;
			od.op2.present = true;
			od.op2.opData.reg = ((opcodeWord & 0x0E00) >> 9);
		}

	}

	void trap(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.mnemonic = "trap";
		od.size = size;		
	}

	void bra(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);		

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
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);		

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
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);	
		od.mnemonic = "bhi";
	}

	void bls(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);	
		od.mnemonic = "bls";
	}

	void bcc(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);		

		od.mnemonic = "bcc";
	}

	void bcs(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);	
		od.mnemonic = "bcs";
	}

	void bne(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);	

		od.mnemonic = "bne";


	}

	void beq(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);	
		od.mnemonic = "beq";
	}

	void bvc(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);	
		od.mnemonic = "bvc";
	}

	void bvs(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);	
		od.mnemonic = "bvs";
	}

	void bpl(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);	
		od.mnemonic = "bpl";
	}

	void bmi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);	
		od.mnemonic = "bmi";
	}

	void bge(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;

		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);	
		od.mnemonic = "bge";
	}

	void blt(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);	
		od.mnemonic = "blt";
	}

	void bgt(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);	
		od.mnemonic = "bgt";
	}

	void ble(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		displacement(opcodeWord, (uint16_t*)(((char*)buf)+offset), od);	
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

	void mulu(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;
		od.mnemonic = "mulu";	
		od.operandSize = "w";
	}

	void muls(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		od.size = size;
		od.mnemonic = "muls";
		od.operandSize = "w";
	}

	void ori(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		uint32_t immData = 0;

		if((opcodeWord & 0x00C0) == 0x0000)
		{
			od.operandSize = "b";
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
			size += 1;
			immData = bigToNative(*(uint16_t*)(((char*)buf)+offset+2));
			immData &= 0x000000FF;
			decodeModeReg(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1, od.op2);
		}
		else if((opcodeWord & 0x00C0) == 0x0040)
		{
			od.operandSize = "w";
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 2);
			size += 1;
			immData = bigToNative(*(uint16_t*)(((char*)buf)+offset+2));
			immData &= 0x0000FFFF;
			decodeModeReg(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 2, od.op2);
		}
		else if((opcodeWord & 0x00C0) == 0x0080)
		{
			od.operandSize = "l";
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4);
			size += 2;

			immData = bigToNative(*(uint16_t*)(((char*)buf)+offset+2));
			immData <<= 16;
			immData |= bigToNative(*(uint16_t*)(((char*)buf)+offset+2));
			decodeModeReg(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4, od.op2);
		}
		od.size = size;
		od.mnemonic = "ori";

		od.op1.present = true;
		od.op1.addrMode = IMMEDIATE;
		od.op1.opData.op = immData;

		
	}

	void moveq(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		od.mnemonic = "moveq";
	}

	void move_ccr(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		od.size = size;
		od.mnemonic = "move";
		od.operandSize = "i";
		od.op1.addrMode = CCR;
		od.op1.present = true;
		size += addonWords(((opcodeWord & 0x0038) >> 3), (opcodeWord & 0x0007), 4);
		decodeModeReg(((opcodeWord & 0x0038) >> 3), (opcodeWord & 0x0007), 2, od.op2);
	}

	void clr(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00C0) == 00)
		{
			od.operandSize = "b";
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		}
		else if((opcodeWord & 0x00C0) == 01)
		{
			od.operandSize = "w";
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 2);

		}
		else if((opcodeWord & 0x00C0) == 10)
		{
			od.operandSize = "l";
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4);
		}
		od.size = size;
		od.mnemonic = "clr";
	}

	void cmp(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x00C0) == 00)
		{
			od.operandSize = "b";
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
		}
		else if((opcodeWord & 0x00C0) == 01)
		{
			od.operandSize = "w";
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 2);

		}
		else if((opcodeWord & 0x00C0) == 10)
		{
			od.operandSize = "l";
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4);
		}
		od.size = size;
		od.mnemonic = "cmp";
	}

	void asl(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x0100) == 0x0100)
		{
			od.mnemonic = "asl";
		}
		else
		{
			od.mnemonic = "asr";
		}

		if((opcodeWord & 0x0018) == 0x0000)
		{

			if((opcodeWord & 0x0020) == 0x0020)
			{
				// Data register.

				uint16_t sReg = (opcodeWord & 0x0E00);
				sReg >>= 9;
				if((opcodeWord & 0x00C0) == 0)
				{
					od.operandSize = "b";
				}
				else if((opcodeWord & 0x00C0) == 1)
				{
					od.operandSize = "w";
				}
				else if((opcodeWord & 0x00C0) == 2)
				{
					od.operandSize = "l";
				}

				od.size = size;
				od.op1.present = true;
				od.op1.addrMode = DATAREGDIRECT;
				od.op1.opData.reg = sReg;

				od.op2.addrMode = DATAREGDIRECT;
				od.op2.opData.reg = (opcodeWord & 0x0007);
				od.op2.present = true;
			}
			else
			{
				// Immediate register shift..

				od.op1.present = true;
				od.op1.addrMode = QUICKIMMEDIATE;
				od.op1.opData.op = ((opcodeWord & 0x0E00)>>9);

				if((opcodeWord & 0x00C0) == 0)
				{
					od.operandSize = "b";
				}
				else if((opcodeWord & 0x00C0) == 1)
				{
					od.operandSize = "w";
				}
				else if((opcodeWord & 0x00C0) == 3)
				{
					od.operandSize = "l";
				}
				od.size = size;

				od.op2.addrMode = DATAREGDIRECT;
				od.op2.opData.reg = (opcodeWord & 0x0007);
				od.op2.present = true;
			}
		}
		else if((opcodeWord & 0x00C0) == 0x00C0)
		{
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4);
			od.size = size;
			decodeModeReg(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4, od.op1);

		}



	}

	void and(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		od.mnemonic = "and";
		od.size = 1;

		uint8_t opMode = ((opcodeWord & 0x01C0) >> 6);

		if((opMode & 0x04) == 0x04)
		{
			// Dn && <ea> -> <ea>
			if(opMode == 0x04)
			{
				od.operandSize = "b";
				od.size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
				decodeModeReg(((opcodeWord & 0x0038) >> 3), (opcodeWord & 0x0007), 1, od.op2);
			}
			else if(opMode == 0x05)
			{
				od.operandSize = "w";
				od.size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 2);
				decodeModeReg(((opcodeWord & 0x0038) >> 3), (opcodeWord & 0x0007), 2, od.op2);
			}
			else if(opMode == 0x06)
			{
				od.operandSize = "l";
				od.size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4);
				decodeModeReg(((opcodeWord & 0x0038) >> 3), (opcodeWord & 0x0007), 4, od.op2);
			}

			od.op1.present = true;
			od.op1.addrMode = DATAREGDIRECT;
			od.op1.opData.reg = ((opcodeWord & 0x0E00) >> 9);

		}
		else
		{
			// <ea> && Dn -> Dn
			if(opMode == 0x00)
			{
				od.operandSize = "b";
				od.size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 1);
				decodeModeReg(((opcodeWord & 0x0038) >> 3), (opcodeWord & 0x0007), 1, od.op1);
			}
			else if(opMode == 0x01)
			{
				od.operandSize = "w";
				od.size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 2);
				decodeModeReg(((opcodeWord & 0x0038) >> 3), (opcodeWord & 0x0007), 2, od.op1);
			}
			else if(opMode == 0x02)
			{
				od.operandSize = "l";
				od.size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4);
				decodeModeReg(((opcodeWord & 0x0038) >> 3), (opcodeWord & 0x0007), 4, od.op1);
			}

			od.op2.present = true;
			od.op2.addrMode = DATAREGDIRECT;
			od.op2.opData.reg = ((opcodeWord & 0x0E00) >> 9);
		}

	}

	void andi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		od.mnemonic = "andi";
	}

	void eor(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		od.mnemonic = "eor";

		if((opcodeWord & 0x0100) == 0x0100)
		{
			if((opcodeWord & 0x00C0) == 0x0000)
			{
				od.operandSize = "b";
			}
			else if((opcodeWord & 0x00C0) == 0x001)
			{
				od.operandSize = "b";
			}
			else if((opcodeWord & 0x00C0) == 00)
			{
				od.operandSize = "b";
			}

		
		}

	}

	void lsl(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x0100) == 0x0100)
		{
			od.mnemonic = "lsl";
		}
		else
		{
			od.mnemonic = "lsr";
		}

		if((opcodeWord & 0x0018) == 0x0008)
		{

			if((opcodeWord & 0x0020) == 0x0020)
			{
				// Data register.

				uint16_t sReg = (opcodeWord & 0x0E00);
				sReg >>= 9;
				if((opcodeWord & 0x00C0) == 0)
				{
					od.operandSize = "b";
				}
				else if((opcodeWord & 0x00C0) == 1)
				{
					od.operandSize = "w";
				}
				else if((opcodeWord & 0x00C0) == 2)
				{
					od.operandSize = "l";
				}

				od.size = size;
				od.op1.present = true;
				od.op1.addrMode = DATAREGDIRECT;
				od.op1.opData.reg = sReg;

				od.op2.addrMode = DATAREGDIRECT;
				od.op2.opData.reg = (opcodeWord & 0x0007);
				od.op2.present = true;
			}
			else
			{
				// Immediate register shift..

				od.op1.present = true;
				od.op1.addrMode = QUICKIMMEDIATE;
				od.op1.opData.op = ((opcodeWord & 0x0E00)>>9);

				if((opcodeWord & 0x00C0) == 0)
				{
					od.operandSize = "b";
				}
				else if((opcodeWord & 0x00C0) == 1)
				{
					od.operandSize = "w";
				}
				else if((opcodeWord & 0x00C0) == 3)
				{
					od.operandSize = "l";
				}
				od.size = size;

				od.op2.addrMode = DATAREGDIRECT;
				od.op2.opData.reg = (opcodeWord & 0x0007);
				od.op2.present = true;
			}
		}
		else if((opcodeWord & 0x00C0) == 0x00C0)
		{
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4);
			od.size = size;
			decodeModeReg(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4, od.op1);

		}
	}

	void rol(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x0100) == 0x0100)
		{
			od.mnemonic = "rol";
		}
		else
		{
			od.mnemonic = "ror";
		}

		if((opcodeWord & 0x0018) == 0x0018)
		{

			if((opcodeWord & 0x0020) == 0x0020)
			{
				// Data register.

				uint16_t sReg = (opcodeWord & 0x0E00);
				sReg >>= 9;
				if((opcodeWord & 0x00C0) == 0)
				{
					od.operandSize = "b";
				}
				else if((opcodeWord & 0x00C0) == 1)
				{
					od.operandSize = "w";
				}
				else if((opcodeWord & 0x00C0) == 2)
				{
					od.operandSize = "l";
				}

				od.size = size;
				od.op1.present = true;
				od.op1.addrMode = DATAREGDIRECT;
				od.op1.opData.reg = sReg;

				od.op2.addrMode = DATAREGDIRECT;
				od.op2.opData.reg = (opcodeWord & 0x0007);
				od.op2.present = true;
			}
			else
			{
				// Immediate register shift..

				od.op1.present = true;
				od.op1.addrMode = QUICKIMMEDIATE;
				od.op1.opData.op = ((opcodeWord & 0x0E00)>>9);

				if((opcodeWord & 0x00C0) == 0)
				{
					od.operandSize = "b";
				}
				else if((opcodeWord & 0x00C0) == 1)
				{
					od.operandSize = "w";
				}
				else if((opcodeWord & 0x00C0) == 3)
				{
					od.operandSize = "l";
				}
				od.size = size;

				od.op2.addrMode = DATAREGDIRECT;
				od.op2.opData.reg = (opcodeWord & 0x0007);
				od.op2.present = true;
			}
		}
		else if((opcodeWord & 0x00C0) == 0x00C0)
		{
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4);
			od.size = size;
			decodeModeReg(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4, od.op1);

		}
	}

	void roxl(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od)
	{
		unsigned int size = 1;
		if((opcodeWord & 0x0100) == 0x0100)
		{
			od.mnemonic = "roxl";
		}
		else
		{
			od.mnemonic = "roxr";
		}

		if((opcodeWord & 0x0018) == 0x0010)
		{

			if((opcodeWord & 0x0020) == 0x0020)
			{
				// Data register.

				uint16_t sReg = (opcodeWord & 0x0E00);
				sReg >>= 9;
				if((opcodeWord & 0x00C0) == 0)
				{
					od.operandSize = "b";
				}
				else if((opcodeWord & 0x00C0) == 1)
				{
					od.operandSize = "w";
				}
				else if((opcodeWord & 0x00C0) == 2)
				{
					od.operandSize = "l";
				}

				od.size = size;
				od.op1.present = true;
				od.op1.addrMode = DATAREGDIRECT;
				od.op1.opData.reg = sReg;

				od.op2.addrMode = DATAREGDIRECT;
				od.op2.opData.reg = (opcodeWord & 0x0007);
				od.op2.present = true;
			}
			else
			{
				// Immediate register shift..

				od.op1.present = true;
				od.op1.addrMode = QUICKIMMEDIATE;
				od.op1.opData.op = ((opcodeWord & 0x0E00)>>9);

				if((opcodeWord & 0x00C0) == 0)
				{
					od.operandSize = "b";
				}
				else if((opcodeWord & 0x00C0) == 1)
				{
					od.operandSize = "w";
				}
				else if((opcodeWord & 0x00C0) == 3)
				{
					od.operandSize = "l";
				}
				od.size = size;

				od.op2.addrMode = DATAREGDIRECT;
				od.op2.opData.reg = (opcodeWord & 0x0007);
				od.op2.present = true;
			}
		}
		else if((opcodeWord & 0x00C0) == 0x00C0)
		{
			size += addonWords(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4);
			od.size = size;
			decodeModeReg(((opcodeWord & 0x0038) >>3), (opcodeWord & 0x0007), 4, od.op1);

		}
	}
}