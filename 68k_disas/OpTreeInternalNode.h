#pragma once

#include "OpTreeNode.h"

class OpTreeInternalNode : public OpTreeNode
{
public:
	OpTreeInternalNode(void);
	virtual ~OpTreeInternalNode(void);

	void setFirst(OpTreeNode *nn);
	void setSecond(OpTreeNode *nn);
	void replaceNode(OpTreeNode *orig, OpTreeNode *nw);
private:
	OpTreeNode *firstPart;
	OpTreeNode *secondPart;
	unsigned int firstINodes;
	unsigned int secondINodes;
};

