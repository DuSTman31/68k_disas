#include "StdAfx.h"
#include "OpTreeNode.h"


OpTreeNode::OpTreeNode(void)
{
	parent = NULL;
}


OpTreeNode::~OpTreeNode(void)
{
}

void 
OpTreeNode::setParent(OpTreeInternalNode *par)
{
	parent = par;
}