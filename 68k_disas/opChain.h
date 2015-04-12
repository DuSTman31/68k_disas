#pragma once

#include "68k.h"

#include <vector>
using std::vector;

#include "OpTreeNode.h"

class opChain : public OpTreeNode
{
public:
	opChain(void);
	virtual ~opChain(void);
	void addOp(const opDetails &od);
	void split(bool rel, unsigned int size);
private:
	vector<opDetails> opList;
	uint32_t chainSize;
};

