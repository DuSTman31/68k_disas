#ifndef SIXTYEIGHTK_H_
#define SIXTYEIGHTK_H_

#include <cstdint>

enum addressMode {DATAREGDIRECT, ADDRREGDIRECT, ABSSHORT, ABSLONG, PCRELOFF, PCRELINDOFF, ADDRINDIRECT, ADDRINDIRECTPOSTINC, ADDRINDIRECTPREDEC, IMMEDIATE, QUICKIMMEDIATE, CCR, SR}; 

union operandData
{
	int32_t op;
	uint8_t reg;

};

struct operand
{
	bool present;
	int addrMode;
	union operandData opData; 
};

struct opDetails
{
	uint8_t size;
	char *mnemonic;
	char *operandSize;
	struct operand op1;
	struct operand op2;
};

void decode(void *buf, unsigned int offset);

void scanInput(void *buf, unsigned int offset, opDetails &od);

unsigned char addonWords(uint8_t mode, uint8_t reg, uint8_t size);
void decodeModeReg(uint8_t mode, uint8_t reg, uint8_t size, struct operand &op);
void displacement(uint16_t opcodeWord, uint16_t *buf, opDetails &od);

namespace SEOps
{
	void addq(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void add(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void addx(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void addi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void adda(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void subq(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void sub(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void suba(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void subi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void subx(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void move_b(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void move_w(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void move_l(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void movea_l(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void movea_w(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void not(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void or(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void trap(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void bra(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void jmp(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void bsr(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void jsr(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void rtr(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void rts(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void nop(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void bhi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void bls(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void bcc(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void bcs(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void bne(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void beq(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void bvc(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void bvs(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void bpl(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void bmi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void bge(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void blt(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void bgt(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void ble(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void dbhi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void dbls(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void dbcc(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void dbcs(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void dbne(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void dbeq(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void dbvc(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void dbvs(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void dbpl(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void dbmi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void dbge(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void dblt(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void dbgt(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void dble(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void lea(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void mulu(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void muls(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void ori(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void moveq(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void move_to_ccr(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void move_from_sr(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void move_to_sr(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void clr(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void cmp(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void asl(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void and(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void andi(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void eor(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);

	void lsl(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void rol(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
	void roxl(uint16_t opcodeWord, void *buf, unsigned int offset, opDetails &od);
}


#endif //SIXTYEIGHTK_H_