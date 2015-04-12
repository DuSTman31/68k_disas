#pragma once

class OpTreeInternalNode;

class OpTreeNode
{
public:
	OpTreeNode(void);
	virtual ~OpTreeNode(void);
	void setParent(OpTreeInternalNode *par);
protected:
	OpTreeInternalNode *parent;
};

