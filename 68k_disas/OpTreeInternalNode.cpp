#include "StdAfx.h"
#include "OpTreeInternalNode.h"


OpTreeInternalNode::OpTreeInternalNode(void)
{
	firstPart = NULL;
	secondPart = NULL;
	firstINodes = 0;
	secondINodes = 0;
}


OpTreeInternalNode::~OpTreeInternalNode(void)
{
	delete firstPart;
	delete secondPart;
}


void 
OpTreeInternalNode::setFirst(OpTreeNode *nn)
{
	firstPart = nn;
}

void 
OpTreeInternalNode::setSecond(OpTreeNode *nn)
{
	secondPart = nn;
}

void 
OpTreeInternalNode::replaceNode(OpTreeNode *orig, OpTreeNode *nw)
{
	if(firstPart == orig)
	{
		firstPart = nw;
	}
	else if(secondPart == orig)
	{
		secondPart = nw;
	}
}
