#include "StdAfx.h"
#include "opChain.h"

#include "OpTreeNode.h"
#include "OpTreeInternalNode.h"

opChain::opChain(void)
{
	chainSize = 0;
}


opChain::~opChain(void)
{
}

void 
opChain::addOp(const opDetails &od)
{
	opList.push_back(od);
	chainSize += od.size;
}


void 
opChain::split(bool rel, unsigned int size)
{
	opChain *firstSection = NULL;
	opChain *secondSection = NULL;
	OpTreeInternalNode *nIntNode = NULL;

	firstSection = new opChain();
	secondSection = new opChain();
	nIntNode->setFirst(firstSection);
	nIntNode->setSecond(secondSection);

	if(parent)
	{
		parent->replaceNode(this, nIntNode);
	}
	else
	{
		parent = nIntNode;
	}
}